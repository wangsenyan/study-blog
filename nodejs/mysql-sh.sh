#!/bin/sh
INTERVAL=5
PERFIX=$INTERVAL-sec-status
RUNFILE=/home/benchmarks/running
mysql -e 'SHOW GLOBAL VARIABLES' >>mysql-variables
whlie test -e $RUNFILE;do
   file=$(data +%F %I)
   sleep=$(data +%s.%N | awk "{print $INTERVAL -(\$1 $INTERVAL)}")
   sleep $sleepts="$(date + "TS %s.%N %F %T")"
   loadavg="$(uptime)"
   echo "$ts $loadavg">>$PERFIX-$(file)-status
   mysql -e 'SHOW GLOBAL STATUS' >>$PERFIX-${file}-status &
   echo "$ts $loadavg">>$PERFIX-$(file)-innodbstatus
   mysql -e 'SHOW ENGINE INNODB STATUS\G' >>$PERFIX-${file}-innodbstatus &
   echo "$ts $loadavg">>$PERFIX-$(file)-processlist
    mysql -e 'SHOW ENGINE INNODB STATUS\G' >>$PERFIX-${file}-processlist &
   echo $ts
done
echo Exiting because $RUNFILE does not exist.