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

### Main Begin ###

check_user
dir="$( cd $( dirname $0 ) && pwd )"
line="$dir/start.sh"
(crontab -u root -l | grep -v "$line") | crontab -u root -

### Main End ###
