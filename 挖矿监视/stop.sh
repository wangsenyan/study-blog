#! /bin/sh

# create by hetiulin

umask 0022
unset IFS
unset OFS
unset LD_PRELOAD
unset LD_LIBRARY_PATH
export PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin'

PID="/var/run/stargat.tencentyun.pid"
if [ -w '/usr' ]; then
    myPath="/usr/local/qcloud/stargate"
else
    myPath="/var/lib/qcloud/stargate"
fi
agent_name="$myPath/sgagent"

check_user()
{
    if [ "root" != "`whoami`" ]; then
        echo "Only root can execute this script"
        exit 1
    fi    
}

### Main Begin ###

check_user
cd $(dirname $0)

kill -9 `ps aux | grep "$agent_name" | grep -v "grep"| awk '{print $2}'`
killall -9 $agent_name  > /dev/null 2>&1
rm -f $PID
exit 0

### Main End ###
