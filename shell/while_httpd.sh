#!/bin/bash
while true
do
  HTTPD_STATUS=`service httpd status | grep running`
  if [ -z "$HTTPD_STATUS" ]; then
     echo "HTTPD is stopped,try to restart"
     #service httpd restart
  else 
     echo "HTTPD is running,wait 5 sec until next check"
  fi
  sleep 5
done