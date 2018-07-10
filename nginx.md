##
  sudo apt-get install nginx
  /etc/nginx 配置文件
  /etc/nginx/sites-available 虚拟主机
  /usr/sbin/nginx 程序文件
  /var/log/nginx 日志文件
  /etc/init.d 创建了启动脚本nginx
  /var/www/nginx-default 默认虚拟主机目录(/var/www)请参考 /etc/nginx/sites-available
## 
  sudo /etc/init.d/nginx start
## 
  sudo /etc/init.d/nginx stop
  sudo /etc/init.d/nginx start
  重启nginx
### 安装
```sh
sudo apt-get update
sudo apt-get install nginx
```
### 管理nginx进程
```sh

## 停止nginx
sudo systemctl stop nginx

## 启动nginx
sudo systemctl start nginx

## 重启nginx
sudo systemctl restart nginx

## 修改配置后，平滑的加载配置命令
sudo systemctl reload nginx

## 禁止nginx开机启动
sudo systemctl disable nginx

## 重新配置nginx开机自动启动
sudo systemctl enable nginx

```

### 服务器配置
* `/etc/nginx` : nginx 配置文件目录，所有的nginx配置文件都在这里
* `/etc/nginx/nginx.conf` :nginx 主配置文件
* `/etc/nginx/sites-available/`: 这个目录存储每一个网站的"server blocks"。nginx通常不会使用这些配置，除非它们陪连接到  sites-enabled 目录 (see below)。一般所有的server block 配置都在这个目录中设置，然后软连接到别的目录 。
* `/etc/nginx/sites-enabled/`: 这个目录存储生效的 "server blocks" 配置. 通常,这个配置都是链接到 sites-available目录中的配置文件
* `/etc/nginx/snippets`: 这个目录主要可以包含在其它nginx配置文件中的配置片段。重复的配置都可以重构为配置片段。

### 日志文件
* `/var/log/nginx/access.log`: 每一个访问请求都会记录在这个文件中，除非你做了其它设置。
* `/var/log/nginx/error.log`: 任何Nginx的错误信息都会记录到这个文件中。

### 常用变量

|变量名称|作用
|-|-
$uri|请求中的当前URI(不带请求参数)，它可以通过内部重定向，或者使用index指令进行修改，$uri不包含主机名,如 /foo/bar.html。
$arg_name| 请求中的的参数名，即“?”后面的arg_name=arg_value形式的arg_name
$hostname| 主机名
$args |请求中的参数值
$query_string| 同 $args
$request | 代表客户端的请求地址
$request_uri | 这个变量等于包含一些客户端请求参数的原始URI，它无法修改，不包含主机名，如：/cnphp/test.php?arg=freemouse。

### 彻底卸载
```sh
sudo apt-get autoremove nginx       # 移除没用的包
sudo apt-get --purge remove nginx   # 移除应用及配置
sudo apt-get autoremove && sudo apt-get autoclean

dpkg --get-selections | grep nginx  # 罗列出与nginx相关的软件，nginx-common deinstall 然后
sudo apt-get --purge remove nginx-common
```

### 修复
```sh
sudo apt-get install/delete package
sudo apt-get -f install                                   #修复安装
sudo apt-get dist-upgrade                                 #升级系统
sudo apt-get upgrade                                      #更新已安装的包
apt-get source package                                    #下载该包的源代码
sudo apt-get build-dep package                            #安装相关的编译环境
sudo apt-get clean && sudo apt-get autoclean              #清理无用的包
```