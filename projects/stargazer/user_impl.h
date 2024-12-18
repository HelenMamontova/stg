/*
 *    This program is free software; you can redistribute it and/or modify
 *    it under the terms of the GNU General Public License as published by
 *    the Free Software Foundation; either version 2 of the License, or
 *    (at your option) any later version.
 *
 *    This program is distributed in the hope that it will be useful,
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *    GNU General Public License for more details.
 *
 *    You should have received a copy of the GNU General Public License
 *    along with this program; if not, write to the Free Software
 *    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

/*
 *    Author : Boris Mikhailenko <stg34@stargazer.dp.ua>
 */

#pragma once

#include "stg/user.h"
#include "stg/user_stat.h"
#include "stg/user_conf.h"
#include "stg/user_ips.h"
#include "stg/user_property.h"
#include "stg/auth.h"
#include "stg/message.h"
#include "stg/noncopyable.h"
#include "stg/const.h"

#include <vector>
#include <string>
#include <set>
#include <mutex>

#include <ctime>
#include <cstdint>

namespace STG
{

//-----------------------------------------------------------------------------
struct Tariff;
class Tariffs;
class Admin;
class UserImpl;
#ifdef USE_ABSTRACT_SETTINGS
struct Settings;
#else
class SettingsImpl;
#endif
//-----------------------------------------------------------------------------
class UserImpl : public User
{
    public:
#ifdef USE_ABSTRACT_SETTINGS
        using Settings = STG::Settings;
#else
        using Settings = STG::SettingsImpl;
#endif
        UserImpl(const Settings * settings,
                  const Store * store,
                  const Tariffs * tariffs,
                  const Admin * sysAdmin,
                  const Users * u,
                  const Services & svcs);
        UserImpl(const UserImpl & u);

        int             ReadConf();
        int             ReadStat();
        int             WriteConf() override;
        int             WriteStat() override;
        int             WriteMonthStat();

        const std::string & GetLogin() const override { return login; }
        void            SetLogin(std::string const & l);

        int             GetID() const override { return id; }

        double          GetPassiveTimePart() const override;
        void            ResetPassiveTime() { passiveTime = 0; }
        void            SetPassiveTimeAsNewUser();

        int             WriteDetailStat(bool hard = false);

        const Tariff *  GetTariff() const override { return tariff; }
        void            ResetNextTariff() override { nextTariff = ""; }

        #ifdef TRAFF_STAT_WITH_PORTS
        void            AddTraffStatU(int dir, uint32_t ip, uint16_t port, uint32_t len);
        void            AddTraffStatD(int dir, uint32_t ip, uint16_t port, uint32_t len);
        #else
        void            AddTraffStatU(int dir, uint32_t ip, uint32_t len);
        void            AddTraffStatD(int dir, uint32_t ip, uint32_t len);
        #endif

        const DirTraff & GetSessionUpload() const override { return sessionUpload; }
        const DirTraff & GetSessionDownload() const override { return sessionDownload; }
        time_t GetSessionUploadModificationTime() const override { return sessionUploadModTime; }
        time_t GetSessionDownloadModificationTime() const override { return sessionDownloadModTime; }

        const std::string & GetLastDisconnectReason() const override { return lastDisconnectReason; }
        int             GetAuthorized() const override { return static_cast<int>(authorizedBy.size()); }
        time_t          GetAuthorizedModificationTime() const override { return authorizedModificationTime; }
        int             Authorize(uint32_t ip, uint32_t enabledDirs, const Auth * auth);
        void            Unauthorize(const Auth * auth,
                                    const std::string & reason = std::string());
        bool            IsAuthorizedBy(const Auth * auth) const override;
        std::vector<std::string> GetAuthorizers() const override;

        int             AddMessage(Message * msg) override;

        void            UpdatePingTime(time_t t = 0) override;
        time_t          GetPingTime() const override { return pingTime; }

        void            Run() override;

        const std::string & GetStrError() const override { return errorStr; }

        UserProperties & GetProperties() override { return properties; }
        const UserProperties & GetProperties() const override { return properties; }

        void            SetDeleted() override { deleted = true; }
        bool            GetDeleted() const override { return deleted; }

        time_t          GetLastWriteStatTime() const override { return lastWriteStat; }

        void            MidnightResetSessionStat();
        void            ProcessDayFee();
        void            ProcessDayFeeSpread();
        void            ProcessNewMonth();
        void            ProcessDailyFee();
        void            ProcessServices();

        bool            IsInetable() override;
        std::string     GetEnabledDirs() const override;

        void            OnAdd() override;
        void            OnDelete() override;

        virtual std::string GetParamValue(const std::string & name) const override;

    private:
        UserImpl & operator=(const UserImpl & rvalue);

        void            Init();

        const Users*   users;
        UserProperties properties;
        STG::Logger&   WriteServLog;

        void            Connect(bool fakeConnect = false);
        void            Disconnect(bool fakeDisconnect, const std::string & reason);
        int             SaveMonthStat(int month, int year);

        void            SetPrepaidTraff();

        int             SendMessage(Message & msg) const;
        void            ScanMessage();

        time_t          lastScanMessages;

        std::string     login;
        int             id;

        bool            enabledDirs[DIR_NUM];

        uint32_t        lastIPForDisconnect; // User's ip after unauth but before disconnect
        std::string     lastDisconnectReason;

        time_t          pingTime;

        const Admin *   sysAdmin;
        const Store *   store;

        const Tariffs * tariffs;
        const Tariff *  tariff;

        const Services & m_services;

        TraffStat      traffStat;
        std::pair<time_t, TraffStat> traffStatSaved;

        const Settings * settings;

        std::set<const Auth *> authorizedBy;
        time_t          authorizedModificationTime;

        std::vector<Message> messages;

        bool            deleted;

        time_t          lastWriteStat;
        time_t          lastWriteDetailedStat;

        // Properties
        UserProperty<double>         & cash;
        UserProperty<DirTraff>      & up;
        UserProperty<DirTraff>      & down;
        UserProperty<double>         & lastCashAdd;
        UserProperty<time_t>         & passiveTime;
        UserProperty<time_t>         & lastCashAddTime;
        UserProperty<double>         & freeMb;
        UserProperty<time_t>         & lastActivityTime;
        UserProperty<std::string>    & password;
        UserProperty<int>            & passive;
        UserProperty<int>            & disabled;
        UserProperty<int>            & disabledDetailStat;
        UserProperty<int>            & alwaysOnline;
        UserProperty<std::string>    & tariffName;
        UserProperty<std::string>    & nextTariff;
        UserProperty<std::string>    & address;
        UserProperty<std::string>    & note;
        UserProperty<std::string>    & group;
        UserProperty<std::string>    & email;
        UserProperty<std::string>    & phone;
        UserProperty<std::string>    & realName;
        UserProperty<double>         & credit;
        UserProperty<time_t>         & creditExpire;
        UserProperty<UserIPs>       & ips;
        UserProperty<std::string>    & userdata0;
        UserProperty<std::string>    & userdata1;
        UserProperty<std::string>    & userdata2;
        UserProperty<std::string>    & userdata3;
        UserProperty<std::string>    & userdata4;
        UserProperty<std::string>    & userdata5;
        UserProperty<std::string>    & userdata6;
        UserProperty<std::string>    & userdata7;
        UserProperty<std::string>    & userdata8;
        UserProperty<std::string>    & userdata9;

        // End properties

        DirTraff                sessionUpload;
        DirTraff                sessionDownload;
        time_t                   sessionUploadModTime;
        time_t                   sessionDownloadModTime;

        ScopedConnection m_beforePassiveConn;
        void onPassiveChange(int oldVal, int newVal);

        ScopedConnection m_afterDisabledConn;
        void onDisabledChange(int oldVal, int newVal);

        ScopedConnection m_beforeTariffConn;
        void onTariffChange(const std::string& oldVal, const std::string& newVal);

        ScopedConnection m_beforeCashConn;
        void onCashChange(double oldVal, double newVal);

        ScopedConnection m_afterIPConn;
        void onIPChange(const UserIPs& oldVal, const UserIPs& newVal);

        mutable std::mutex  m_mutex;

        std::string              errorStr;

        double getPassiveTimePart() const;
};
//-----------------------------------------------------------------------------

}
