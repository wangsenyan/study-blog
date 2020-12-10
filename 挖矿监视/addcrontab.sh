#! /bin/sh

# created by hetiulin

umask 0022
unset IFS
unset OFS
unset LD_PRELOAD
unset LD_LIBRARY_PATH
export PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin'

check_user()
{
    if [ "root" != "`whoami`" ]; then
        echo "Only root can execute this script"
        exit 1
    fi    
}

check_exist()
{
   str="$(crontab -u root -l | grep "$1")"
   if [ -n "$str" ]; then
       echo "crontab item existed"
       exit 1
   fi  
}

### Main Begin ###

check_user
dir="$( cd "$( dirname $0 )" && pwd )"
bin="$dir/start.sh"
check_exist $bin
#line="*/1 * * * * $bin > /dev/null 2>&1 &"
line="*/1 * * * * flock -xn /tmp/stargate.lock -c '$bin > /dev/null 2>&1 &'"
(crontab -u root -l; echo "$line") | crontab -u root -

if [ $? -eq 0 ]
then
	exit 0
else
	exit 1
fi	

### Main End ###
