#!/bin/sh

BASEPATH=$1

SGCONFPATH="$BASEPATH/stg/projects/sgconf"

RES=`"$SGCONFPATH/sgconf" -s localhost -p 5555 -u admin -w 123456 --get-services`

if [ "$?" != "0" ]
then
    printf "Failed to get services list. Result:\n$RES\n"
    exit 0
fi

printf "Got services list:\n"

NAMES=""
OLDIFS=$IFS
IFS=$(printf "\n")
for LINE in $RES
do
    printf -- "$LINE\n"
    NAME=`printf "$LINE" | grep name`
    if [ "$?" == "0" ]
    then
        NAMES="$NAMES\n"`printf "$NAME" | cut -d: -f2 | sed -e 's/^ *//' -e 's/ *$//'`
    fi
done
IFS=$OLDIFS

printf "Names:\n$NAMES\n"

NUM=`printf "$NAMES" | wc -l`

printf -- "--------\n$NUM\n\n"

if [ "$NUM" != "0" ]
then
    printf "Services list should be empty.\n"
    exit 0
fi

RES=`"$SGCONFPATH/sgconf" -s localhost -p 5555 -u admin -w 123456 --add-service test`

if [ "$?" != "0" ]
then
    printf "Failed to add new service. Result:\n$RES\n"
    exit 0
fi

RES=`"$SGCONFPATH/sgconf" -s localhost -p 5555 -u admin -w 123456 --get-services`

if [ "$?" != "0" ]
then
    printf "Failed to get services list. Result:\n$RES\n"
    exit 0
fi

printf "Got services list:\n"

NAMES=""
OLDIFS=$IFS
IFS=$(printf "\n")
for LINE in $RES
do
    printf -- "$LINE\n"
    NAME=`printf "$LINE" | grep name`
    if [ "$?" == "0" ]
    then
        NAMES="$NAMES\n"`printf "$NAME" | cut -d: -f2 | sed -e 's/^ *//' -e 's/ *$//'`
    fi
done
IFS=$OLDIFS

printf "Names:\n$NAMES\n"

NUM=`printf "$NAMES" | wc -l`

printf -- "--------\n$NUM\n\n"

if [ "$NUM" != "1" ]
then
    printf "Services list should have exactly one entry.\n"
    exit 0
fi

RES=`"$SGCONFPATH/sgconf" -s localhost -p 5555 -u admin -w 123456 --del-service test`

if [ "$?" != "0" ]
then
    printf "Failed to delete a service. Result:\n$RES\n"
    exit 0
fi

RES=`"$SGCONFPATH/sgconf" -s localhost -p 5555 -u admin -w 123456 --get-services`

if [ "$?" != "0" ]
then
    printf "Failed to get services list. Result:\n$RES\n"
    exit 0
fi

printf "Got services list:\n"

NAMES=""
OLDIFS=$IFS
IFS=$(printf "\n")
for LINE in $RES
do
    printf -- "$LINE\n"
    NAME=`printf "$LINE" | grep name`
    if [ "$?" == "0" ]
    then
        NAMES="$NAMES\n"`printf "$NAME" | cut -d: -f2 | sed -e 's/^ *//' -e 's/ *$//'`
    fi
done
IFS=$OLDIFS

printf "Names:\n$NAMES\n"

NUM=`printf "$NAMES" | wc -l`

printf -- "--------\n$NUM\n\n"

if [ "$NUM" != "1" ]
then
    printf "Services list should be empty.\n"
    exit 0
fi