1.apt-get install git
2.git config --global user.name "wangsenyan"
  git config --global user.email "2633600702@qq.com"
  git init ÏîÄ¿Ãû³Æ
  gedit README
  gedit sample
  git add sample
  git commit -m "create a git project" //commitµ½»º´æÇø£¬²¢Ìí¼Ó¼ò½é
  git remote add origin https://github.com/wangsenyan/myGitTest.git
  git push origin master //ÉÏ´«
  git clone ¿ËÂ¡
  git pull origin master
3.ssh-keygen -C "2633600702@qq.com" -t ras
  passphrase -wsy12140322150232
4.¸´ÖÆ.pubÏÂµÄ¹«Ô¿µ½githubÖÐ£¬setting-ssh and  gpg keys-new ssh key
5.ssh -T git@github.com ²âÊÔÅäÖÃ

6.add-apt-repository ppa:webupd8team/sublime-text-3 Ìí¼ÓppaÂ·¾¶
  tar -xjvf name.tar.bz2
7.sudo apt-get upgrade ¸üÐÂÒÑ°²×°µÄ°ü
  sudo apt-get install pkgname ¸üÐÂÌØ¶¨Èí¼þ
  dpkg -L xxxx²é¿´Èí¼þ°²×°Î»ÖÃ
  dpkg -l |grep filename ²é¿´Èí¼þÊÇ·ñ°²×°
8.pscp -i alpahcoding-test.ppk third-party-login.js root@192.168.5.3:/root/alphacoding/config

9.git clone -b <分支名字> <地址>
10.创建自己的项目
   切换到自己的项目目录，切记.gitignore 添加node_modules等
   git add . 
     //fatal: Not a git repository (or any of the parent directories): .git
   git init
   git commit -m '描述'
   git remote add origin https://git.coding.net/wangsenyan/stormshop.git
   git push -u origin master  
11.git checkout -- <filename> 取消该文件的本地修改
