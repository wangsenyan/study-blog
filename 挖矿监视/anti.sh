 #!/bin/bash
SHELL=/bin/bash
PATH=/sbin:/bin:/usr/sbin:/usr/bin

# netstat -antp | grep '23.94.24.12:8080'  | awk '{print $7}' | sed -e 's/\/.*//g' | xargs kill -9
# netstat -antp | grep '134.122.17.13:8080'  | awk '{print $7}' | sed -e 's/\/.*//g' | xargs kill -9
# # 停止java_c
# ps aux | grep -vw /var/tmp/java_c/java_c | grep -v grep | awk '{if($3>80.0) print $2}' | xargs -I % kill -9 % | xargs -I % kill -9 %

#删除注入的文件
# chattr -ia /tmp/.firstrun-update_ivan1.pid
# rm /tmp/.firstrun-update_ivan1.pid
# # 删除 /tmp/dbused

# 替换crontab 
# 直接删除

rm_array[0]=/etc/cron.d/root
rm_array[1]=/etc/cron.d/apache
rm_array[2]=/etc/cron.d/nginx
rm_array[3]=/var/spool/cron/root
rm_array[4]=/var/spool/cron/crontabs
rm_array[5]=/var/spool/cron/crontabs/root
rm_array[6]=/etc/cron.hourly
rm_array[7]=/etc/cron.weekly/pwnrig
rm_array[8]=/etc/cron.daliy/pwnrig
rm_array[9]=/etc/cron.monthly/pwnrig
rm_array[10]=/etc/crontab*
rm_array[11]=/tmp/*.log
rm_array[12]=/tmp/systemd-private*
rm_array[13]=/tmp/dbusex
rm_array[14]=/tmp/tmp.*
rm_array[23]=/tmp/dbused
rm_array[15]=/tmp/.firstrun-update_ivan1.pid
rm_array[16]=/usr/local/lib/libprocesshider.so
rm_array[17]=/var/tmp/java_c
rm_array[18]=/opt/autoupdater
rm_array[19]=/opt/logger
rm_array[20]=/opt/system
rm_array[21]=/opt/sysall
rm_array[22]=/usr/bin/zgrab
rm_array[23]=/bin/crondr
rm_array[24]=/tmp/local
rm_array[25]=/tmp/*.so
rm_array[27]=/etc/init.d/DbSecuritySpt
rm_array[27]=/bin/dbused
rm_array[28]=/lib/systemd/system/pwnrigl.service
rm_array[29]=/bin/initdr
rm_array[30]=/bin/sysdr
rm_array[31]=/bin/bprofr
rm_array[32]=/bin/crondr
rm_array[33]=/var/tmp
#rm_array[26]=/tmp/
# rm_array[15]=
# rm_array[15]=
# rm_array[15]=
# rm_array[15]=
for ele in ${rm_array[@]}
do
 if [ -d "$ele" ] 
 then 
   chattr -ia $ele
   rm -rf $ele
   echo "delete success $ele"
 elif [ -f "$ele" ]
 then
  rm -f $ele
  echo "delete success $ele"
 fi
done

# 重启cron服务
service cron restart
systemctl restart cron

#find -name "db"
# 重启
#find / -name "i686"
find /tmp -name "x64b" | xargs rm -r
find /tmp -name "x86_64" | xargs rm -r
find /tmp -name "x86_643" | xargs rm -r
find /tmp -name "x686" | xargs rm -r
docker stop `docker ps | awk '{print $3}'`
docker rmi `docker images | grep none | awk '{print $1}'`
docker rmi `docker images | grep none | awk '{print $3}'`
#rm -rf /etc/cron.hourly/oanacroner1
# 临时开启防火墙
#setenforce 1
kill -9 $(pidof dbused)
kill -9 $(pidof dbusex)
# 删除用户
chattr -ia /etc/passwd
chattr -ia /etc/shadow
chattr -ia /etc/sudoers
chmod +w /etc/sudoers

userdel -rf autoupdater
userdel -rf system
userdel -rf logger
userdel -rf sysall
# 删除用户组
groupdel sysall
groupdel system
groupdel logger
groupdel autoupdater

sed -i '/sysall/d' /etc/sudoers
sed -i '/system/d' /etc/sudoers
sed -i '/logger/d' /etc/sudoers
sed -i '/sysall/d' /etc/sudoers
sed -i '/autoupdater/d' /etc/sudoers
chattr +ia /etc/passwd
chattr +ia /etc/shadow
chmod -w /etc/sudoers
chattr +ia /etc/sudoers
# 删除authorized_keys
# rm -rf /opt/autoupdater
# rm -rf /opt/logger
# rm -rf /opt/system
# rm -rf /opt/sysall
# rm /usr/bin/zgrab
# crontab停止

# 停止定时任务
# 删除其他定时任务
# 停用kinsing

# 卸载相应软件
# scandel(){
#   which masscan >/dev/null
#   if [ $? -eq 0 ]; then
# }

stopscan() {
	sudo killall screen
	ps aux | grep -v grep | grep 'docker' | awk '{print $2}' | xargs -I % kill -9 %
	ps aux | grep -v grep | grep 'screen' | awk '{print $2}' | xargs -I % kill -9 %
	ps aux | grep -v grep | grep 'curl' | awk '{print $2}' | xargs -I % kill -9 %
}
#根据对方的脚本发现问题
localgo() {
	echo "own localgo start"
	myhostip=$(curl -sL icanhazip.com)
	KEYS=$(find ~/ /root /home -maxdepth 3 -name 'id_rsa*' | grep -vw pub)
	KEYS2=$(cat ~/.ssh/config /home/*/.ssh/config /root/.ssh/config | grep IdentityFile | awk -F "IdentityFile" '{print $2 }')
	KEYS3=$(cat ~/.bash_history /home/*/.bash_history /root/.bash_history | grep -E "(ssh|scp)" | awk -F ' -i ' '{print $2}' | awk '{print $1'})
	KEYS4=$(find ~/ /root /home -maxdepth 3 -name '*.pem' | uniq)
	HOSTS=$(cat ~/.ssh/config /home/*/.ssh/config /root/.ssh/config | grep HostName | awk -F "HostName" '{print $2}')
	HOSTS2=$(cat ~/.bash_history /home/*/.bash_history /root/.bash_history | grep -E "(ssh|scp)" | grep -oP "([0-9]{1,3}\.){3}[0-9]{1,3}")
	HOSTS3=$(cat ~/.bash_history /home/*/.bash_history /root/.bash_history | grep -E "(ssh|scp)" | tr ':' ' ' | awk -F '@' '{print $2}' | awk -F '{print $1}')
	HOSTS4=$(cat /etc/hosts | grep -vw "0.0.0.0" | grep -vw "127.0.1.1" | grep -vw "127.0.0.1" | grep -vw $myhostip | sed -r '/\n/!s/[0-9.]+/\n&\n/;/^([0-9]{1,3}\.){3}[0-9]{1,3}\n/P;D' | awk '{print $1}')
	HOSTS5=$(cat ~/*/.ssh/known_hosts /home/*/.ssh/known_hosts /root/.ssh/known_hosts | grep -oP "([0-9]{1,3}\.){3}[0-9]{1,3}" | uniq)
	HOSTS6=$(ps auxw | grep -oP "([0-9]{1,3}\.){3}[0-9]{1,3}" | grep ":22" | uniq)
	USERZ=$(
		echo "root"
		find ~/ /root /home -maxdepth 2 -name '\.ssh' | uniq | xargs find | awk '/id_rsa/' | awk -F'/' '{print $3}' | uniq | grep -wv ".ssh"
	)
	USERZ2=$(cat ~/.bash_history /home/*/.bash_history /root/.bash_history | grep -vw "cp" | grep -vw "mv" | grep -vw "cd " | grep -vw "nano" | grep -v grep | grep -E "(ssh|scp)" | tr ':' ' ' | awk -F '@' '{print $1}' | awk '{print $4}' | uniq)
	sshports=$(cat ~/.bash_history /home/*/.bash_history /root/.bash_history | grep -vw "cp" | grep -vw "mv" | grep -vw "cd " | grep -vw "nano" | grep -v grep | grep -E "(ssh|scp)" | tr ':' ' ' | awk -F '-p' '{print $2}' | awk '{print $1}' | sed 's/[^0-9]*//g' | tr ' ' '\n' | nl | sort -u -k2 | sort -n | cut -f2- | sed -e "\$a22")
	userlist=$(echo "$USERZ $USERZ2" | tr ' ' '\n' | nl | sort -u -k2 | sort -n | cut -f2- | grep -vw "." | grep -vw "ssh" | sed '/\./d')
	hostlist=$(echo "$HOSTS $HOSTS2 $HOSTS3 $HOSTS4 $HOSTS5 $HOSTS6" | grep -vw 127.0.0.1 | tr ' ' '\n' | nl | sort -u -k2 | sort -n | cut -f2-)
	keylist=$(echo "$KEYS $KEYS2 $KEYS3 $KEYS4" | tr ' ' '\n' | nl | sort -u -k2 | sort -n | cut -f2-)
	i=0
	for user in $userlist; do
    echo "---user----$user"
		for host in $hostlist; do
    echo "---host----$host"
			for key in $keylist; do
      echo "---key----$key"
				for sshp in $sshports; do
        echo "---sshp----$sshp"
				done
			done
		done
	done
	# scangogo
	echo "my  local done"
}

#sshd_config
sshd_rm() {
  chattr -ia /etc/ssh/sshd_config
  echo "run delete sshd_config"
  cat /etc/ssh/sshd_config | grep -iw "Port 22" | grep -v grep >/dev/null
  if [ $? -eq 0 ]; then
    needreset=1
    sed -i '/Port 22/d' /etc/ssh/sshd_config
    sed -i '/Port 33768/d' /etc/ssh/sshd_config
    sed -i '/PasswordAuthentication/d' /etc/ssh/sshd_config
    sed -i '/GSSAPIAuthentication/d' /etc/ssh/sshd_config
    sed -i '/GSSAPICleanupCredentials/d' /etc/ssh/sshd_config
  fi
  chattr +ia /etc/ssh/sshd_config
  echo "delete sshd_config success"
}

resetssh() {
  if [ "$needreset" -eq "0" ]; then
		echo "no need"
	else
		sleep 10
		/etc/init.d/ssh restart
		/etc/init.d/sshd restart
		/etc/rc.d/sshd restart
		service ssh restart
		service sshd restart
		systemctl start ssh
		systemctl restart ssh
		scw-fetch-ssh-keys --upgrade
	fi
}

# 删除dns解析
delete_resolv() {
  sed -i '/1.1.1.1/d' /etc/resolv.conf
  sed -i '/8.8.8.8/d' /etc/resolv.conf
}

# cron和crond区别
# crontab
# anacron
#安装监控软件
initf() {
  sed -i '/kernel.nmi_watchdog=0/d' /etc/sysctl.conf
  sysctl -p #使生效
  # 有问题
  echo '1' > /proc/sys/kernel/nmi_watchdog > /dev/null 2>&1
# syslog
# hostguard
# cloudResetPwdUpdateAgent
#
}
#S.0表示screen
stopscan
sshd_rm

# 查询最近更改过的文件
# find / -mmin -12 | egerp -s -v 'proc|module' >>  film.txt