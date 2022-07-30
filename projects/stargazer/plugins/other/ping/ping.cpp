#include "ping.h"

#include "stg/user.h"
#include "stg/locker.h"
#include "stg/user_property.h"

#include <cstdio>
#include <cassert>
#include <csignal>
#include <ctime>
#include <algorithm>

namespace
{
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename varType>
class HAS_USER: public std::binary_function<varType, UserPtr, bool>
{
public:
    explicit HAS_USER(const UserPtr & u) : user(u) {}
    bool operator()(varType notifier) const
        {
        return notifier.GetUser() == user;
        }
private:
    const UserPtr & user;
};
}

extern "C" STG::Plugin* GetPlugin()
{
    static PING plugin;
    return &plugin;
}
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int PING_SETTINGS::ParseSettings(const STG::ModuleSettings & s)
{
STG::ParamValue pv;
std::vector<STG::ParamValue>::const_iterator pvi;

pv.param = "PingDelay";
pvi = std::find(s.moduleParams.begin(), s.moduleParams.end(), pv);
if (pvi == s.moduleParams.end() || pvi->value.empty())
    {
    errorStr = "Parameter \'PingDelay\' not found.";
    printfd(__FILE__, "Parameter 'PingDelay' not found\n");
    return -1;
    }
if (ParseIntInRange(pvi->value[0], 5, 3600, &pingDelay) != 0)
    {
    errorStr = "Cannot parse parameter \'PingDelay\': " + errorStr;
    printfd(__FILE__, "Canot parse parameter 'PingDelay'\n");
    return -1;
    }

return 0;
}
//-----------------------------------------------------------------------------
PING::PING()
    : users(nullptr),
      isRunning(false),
      onAddUserNotifier(*this),
      onDelUserNotifier(*this),
      logger(STG::PluginLogger::get("ping"))
{
}
//-----------------------------------------------------------------------------
int PING::ParseSettings()
{
auto ret = pingSettings.ParseSettings(settings);
if (ret != 0)
    errorStr = pingSettings.GetStrError();
return ret;
}
//-----------------------------------------------------------------------------
int PING::Start()
{
GetUsers();

users->AddNotifierUserAdd(&onAddUserNotifier);
users->AddNotifierUserDel(&onDelUserNotifier);

pinger.SetDelayTime(pingSettings.GetPingDelay());
pinger.Start();

m_thread = std::jthread([this](auto token){ Run(std::move(token)); });

return 0;
}
//-----------------------------------------------------------------------------
int PING::Stop()
{
std::lock_guard lock(m_mutex);

if (!m_thread.joinable())
    return 0;

pinger.Stop();
m_thread.request_stop();
//5 seconds to thread stops itself
struct timespec ts = {0, 200000000};
for (int i = 0; i < 25; i++)
    {
    if (!isRunning)
        break;

    nanosleep(&ts, nullptr);
    }

users->DelNotifierUserAdd(&onAddUserNotifier);
users->DelNotifierUserDel(&onDelUserNotifier);

std::list<UserPtr>::iterator users_iter;
users_iter = usersList.begin();
while (users_iter != usersList.end())
    {
    UnSetUserNotifiers(*users_iter);
    ++users_iter;
    }

if (isRunning)
    m_thread.detach();
else
    m_thread.join();

return 0;
}
//-----------------------------------------------------------------------------
bool PING::IsRunning()
{
return isRunning;
}
//-----------------------------------------------------------------------------
void PING::Run(std::stop_token token)
{
sigset_t signalSet;
sigfillset(&signalSet);
pthread_sigmask(SIG_BLOCK, &signalSet, nullptr);

isRunning = true;

long delay = (10000000 * pingSettings.GetPingDelay()) / 3 + 50000000;

while (!token.stop_requested())
    {
    auto iter = usersList.begin();
        {
        std::lock_guard lock(m_mutex);
        while (iter != usersList.end())
            {
            if ((*iter)->GetProperties().ips.ConstData().onlyOneIP())
                {
                uint32_t ip = (*iter)->GetProperties().ips.ConstData()[0].ip;
                time_t t;
                if (pinger.GetIPTime(ip, &t) == 0)
                    {
                    if (t != 0)
                        (*iter)->UpdatePingTime(t);
                    }
                }
            else
                {
                uint32_t ip = (*iter)->GetCurrIP();
                if (ip != 0)
                    {
                    time_t t;
                    if (pinger.GetIPTime(ip, &t) == 0)
                        {
                        if (t != 0)
                            (*iter)->UpdatePingTime(t);
                        }
                    }
                }
            ++iter;
            }
        }
    struct timespec ts = {delay / 1000000000, delay % 1000000000};
    for (int i = 0; i < 100; i++)
        {
        if (!token.stop_requested())
            {
            nanosleep(&ts, nullptr);
            }
        }
    }

isRunning = false;
}
//-----------------------------------------------------------------------------
void PING::SetUserNotifiers(UserPtr u)
{
CHG_CURRIP_NOTIFIER_PING ChgCurrIPNotifier(*this, u);
CHG_IPS_NOTIFIER_PING ChgIPNotifier(*this, u);

ChgCurrIPNotifierList.push_front(ChgCurrIPNotifier);
ChgIPNotifierList.push_front(ChgIPNotifier);

u->AddCurrIPAfterNotifier(&(*ChgCurrIPNotifierList.begin()));
u->GetProperties().ips.AddAfterNotifier(&(*ChgIPNotifierList.begin()));
}
//-----------------------------------------------------------------------------
void PING::UnSetUserNotifiers(UserPtr u)
{
// ---          CurrIP              ---
HAS_USER<CHG_CURRIP_NOTIFIER_PING> IsContainsUserCurrIP(u);
HAS_USER<CHG_IPS_NOTIFIER_PING> IsContainsUserIP(u);

std::list<CHG_CURRIP_NOTIFIER_PING>::iterator currIPter;
std::list<CHG_IPS_NOTIFIER_PING>::iterator IPIter;

currIPter = find_if(ChgCurrIPNotifierList.begin(),
                    ChgCurrIPNotifierList.end(),
                    IsContainsUserCurrIP);

if (currIPter != ChgCurrIPNotifierList.end())
    {
    currIPter->GetUser()->DelCurrIPAfterNotifier(&(*currIPter));
    ChgCurrIPNotifierList.erase(currIPter);
    }
// ---         CurrIP end          ---

// ---          IP              ---
IPIter = find_if(ChgIPNotifierList.begin(),
                 ChgIPNotifierList.end(),
                 IsContainsUserIP);

if (IPIter != ChgIPNotifierList.end())
    {
    IPIter->GetUser()->GetProperties().ips.DelAfterNotifier(&(*IPIter));
    ChgIPNotifierList.erase(IPIter);
    }
// ---          IP end          ---
}
//-----------------------------------------------------------------------------
void PING::GetUsers()
{
std::lock_guard lock(m_mutex);

UserPtr u;
int h = users->OpenSearch();
assert(h && "USERS::OpenSearch is always correct");

while (users->SearchNext(h, &u) == 0)
    {
    usersList.push_back(u);
    SetUserNotifiers(u);
    if (u->GetProperties().ips.ConstData().onlyOneIP())
        {
        pinger.AddIP(u->GetProperties().ips.ConstData()[0].ip);
        }
    else
        {
        uint32_t ip = u->GetCurrIP();
        if (ip != 0)
            pinger.AddIP(ip);
        }
    }

users->CloseSearch(h);
}
//-----------------------------------------------------------------------------
void PING::AddUser(UserPtr u)
{
std::lock_guard lock(m_mutex);

SetUserNotifiers(u);
usersList.push_back(u);
}
//-----------------------------------------------------------------------------
void PING::DelUser(UserPtr u)
{
std::lock_guard lock(m_mutex);

UnSetUserNotifiers(u);

std::list<UserPtr>::iterator users_iter;
users_iter = usersList.begin();

while (users_iter != usersList.end())
    {
    if (u == *users_iter)
        {
        usersList.erase(users_iter);
        break;
        }
    ++users_iter;
    }
}
//-----------------------------------------------------------------------------
void CHG_CURRIP_NOTIFIER_PING::Notify(const uint32_t & oldIP, const uint32_t & newIP)
{
ping.pinger.DelIP(oldIP);
if (newIP != 0)
    ping.pinger.AddIP(newIP);
}
//-----------------------------------------------------------------------------
void CHG_IPS_NOTIFIER_PING::Notify(const STG::UserIPs & oldIPS, const STG::UserIPs & newIPS)
{
if (oldIPS.onlyOneIP())
    ping.pinger.DelIP(oldIPS[0].ip);

if (newIPS.onlyOneIP())
    ping.pinger.AddIP(newIPS[0].ip);
}
//-----------------------------------------------------------------------------
void ADD_USER_NONIFIER_PING::Notify(const UserPtr & user)
{
ping.AddUser(user);
}
//-----------------------------------------------------------------------------
void DEL_USER_NONIFIER_PING::Notify(const UserPtr & user)
{
ping.DelUser(user);
}
//-----------------------------------------------------------------------------
