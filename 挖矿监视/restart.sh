#! /bin/sh

# created by hetiulin

umask 0022
export PATH='/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin'

### Main Begin ###

cd $(dirname $0)
./stop.sh
sleep 2
./start.sh

### Main End ###
