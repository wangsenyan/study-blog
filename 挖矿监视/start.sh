#! /bin/sh

# create by hetiulin

umask 0022
unset IFS
unset OFS
unset LD_PRELOAD
unset LD_LIBRARY_PATH
export PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin'

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
        exit 2
    fi    
}

check_alive()
{
    status=`ps ax | grep "$agent_name" | grep -v "grep" |wc -l`

    if [ $status -ne 0 ]; then
        # process exist
        echo "stargate agent already exist"
        exit 1
    fi        
}

### Main Begin ###

check_user
check_alive
cd $(dirname $0)
$agent_name -d

ret=$?
if [ $ret -eq 0 ]
then
    echo "stargate agent run succ"
else
    echo "stargate agent run failed, errcode: $ret"
fi
exit $ret

### Main End ###
