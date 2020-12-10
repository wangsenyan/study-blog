#!/bin/sh

umask 0022
unset IFS
unset OFS
unset LD_PRELOAD
unset LD_LIBRARY_PATH
export PATH='/usr/sbin:/sbin:/usr/bin:/bin'


if [ "root" != "`whoami`" ]; then
    echo "Only root can execute this script"
    exit 111 
fi 

if [ -w '/usr' ]; then
    myPath="/usr/local/qcloud/stargate"
else
    myPath="/var/lib/qcloud/stargate"
fi
agent_name="$myPath/sgagent"

if [ -e '/usr/share/coreos/lsb-release' ]; then
    systemctl stop stargate.service
    systemctl disable stargate.service
    rm -f /etc/systemd/system/stargate.*
else
    $myPath/admin/delcrontab.sh
    if [ $? -ne 0 ];then
        line="$myPath/admin/start.sh"
        (crontab -u root -l | grep -v "$line") | crontab -u root -
    fi
fi

$myPath/admin/stop.sh
if [ $? -ne 0 ];then
    kill -9 `ps aux | grep "$agent_name" | grep -v "grep"| awk '{print $2}'`
    killall -9 $agent_name  > /dev/null 2>&1
fi

rm -rf $myPath

exit 0
