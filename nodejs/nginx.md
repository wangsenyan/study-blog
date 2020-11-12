## 安装
```sh
  sudo apt-get install nginx
  /etc/nginx 配置文件
  /etc/nginx/sites-available #虚拟主机
  /usr/sbin/nginx #程序文件
  /var/log/nginx #日志文件
  /etc/init.d #创建了启动脚本nginx
  /var/www/nginx-default #默认虚拟主机目录(/var/www)请参考 /etc/nginx/sites-available
```
## 启动
```sh
  sudo /etc/init.d/nginx -s start
  sudo /etc/init.d/nginx -s stop
  sudo /etc/init.d/nginx -s reload #  重启nginx
```
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
* [nginx.conf](nginx.conf)
* [nginx.used.conf](nginx.used.conf)
* `/etc/nginx` : nginx 配置文件目录，所有的nginx配置文件都在这里
* `/etc/nginx/nginx.conf` :nginx 主配置文件
* `/etc/nginx/sites-available/`: 这个目录存储每一个网站的"server blocks"。nginx通常不会使用这些配置，除非它们陪连接到  sites-enabled 目录 (see below)。一般所有的server block 配置都在这个目录中设置，然后软连接到别的目录 。
* `/etc/nginx/sites-enabled/`: 这个目录存储生效的 "server blocks" 配置. 通常,这个配置都是链接到 sites-available目录中的配置文件
* `/etc/nginx/snippets`: 这个目录主要可以包含在其它nginx配置文件中的配置片段。重复的配置都可以重构为配置片段。

### 负载均衡
* 策略
 - 轮询（默认）
 - weight(权重)
 - ip_hash
 - fair 按服务器的响应时间来分配请求,响应时间短的优先分配
```conf
upstream dynamic {
    
    zone upstream_dynamic 64k;

    server backend1.example.com      weight=5;
    server backend2.example.com:8080 fail_timeout=5s slow_start=30s;
    server 192.0.2.1                 max_fails=3;
    server backend3.example.com      resolve;
    server backend4.example.com      service=http resolve;

    server backup1.example.com:8080  backup;
    server backup2.example.com:8080  backup;
    #weight;
    #ip_hash; #表示开启ip_hash
    #fair; #按服务器的响应时间来分配请求,响应时间短的优先分配
}

server {
    location / {
        proxy_pass http://dynamic;
        health_check;
    }
}
```
### 动静分离
* 可以理解为使用nginx处理静态页面,Tomcat处理动态页面
* 缓冲或直接分离? expires
```conf
location /image/ {
            root /data/; #访问 /image/会 返回 /data/image/下的文件
            autoindex on; # 能列出文件的目录
            #expires 3d; #缓冲三天失效
           }

```
### 高可用
* nginx 宕机,任然可以
* keepalived
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

### 准备
* 配置DNS和ip映射 
  - C:\Windows\System32\drivers\etc\hosts
* 配置nginx.conf
* 语法规则
  - = 表示精确匹配
  - ~ 正则,区分大小写
  - ~* 正则,不区分大小写
  - ^~ 如果该符号后面的字符是最佳匹配,采用该规则,不进行后续的查找
```conf
location [ = | ~ | ~* | ^~] uri {...}

# 设置变量,都是全局可见的
set $变量名 变量值
```

* 内置预定义变量

|变量名|定义
--------------|-------------------------------
$arg_PARAMETER|	GET请求中变量名PARAMETER参数的值。
$args|	这个变量等于GET请求中的参数。例如，foo=123&bar=blahblah;这个变量只可以被修改
$binary_remote_addr|	二进制码形式的客户端地址。
$body_bytes_sent|	传送页面的字节数
$content_length|请求头中的Content-length字段。
$content_type|请求头中的Content-Type字段。
$cookie_COOKIE|cookie COOKIE的值。
$document_root|当前请求在root指令中指定的值。
$document_uri|与$uri相同。
$host|请求中的主机头(Host)字段，如果请求中的主机头不可用或者空，则为处理请求的server名称(处理请求的server的server_name指令的值)。值为小写，不包含端口。
$hostname|机器名使用 gethostname系统调用的值
$http_HEADER|HTTP请求头中的内容，HEADER为HTTP请求中的内容转为小写，-变为_(破折号变为下划线)，例如：$http_user_agent(Uaer-Agent的值);
$sent_http_HEADER|HTTP响应头中的内容，HEADER为HTTP响应中的内容转为小写，-变为_(破折号变为下划线)，例如： $sent_http_cache_control, $sent_http_content_type…;
$is_args|如果$args设置，值为"?"，否则为""。
$limit_rate|这个变量可以限制连接速率。
$nginx_version|当前运行的nginx版本号。
$query_string|与$args相同。
$remote_addr|客户端的IP地址。
$remote_port|客户端的端口。
$remote_user|已经经过Auth Basic Module验证的用户名。
$request_filename|当前连接请求的文件路径，由root或alias指令与URI请求生成。
$request_body|这个变量（0.7.58+）包含请求的主要信息。在使用proxy_pass或fastcgi_pass指令的location中比较有意义。
$request_body_file|客户端请求主体信息的临时文件名。
$request_completion|如果请求成功，设为"OK"；如果请求未完成或者不是一系列请求中最后一部分则设为空。
$request_method|这个变量是客户端请求的动作，通常为GET或POST。包括0.8.20及之前的版本中，这个变量总为main request中的动作，如果当前请求是一个子请求，并不使用这个当前请求的动作。
$request_uri|这个变量等于包含一些客户端请求参数的原始URI，它无法修改，请查看$uri更改或重写URI。
$scheme|所用的协议，比如http或者是https，比如rewrite ^(.+)$ $scheme://example.com$1 redirect;
$server_addr|服务器地址，在完成一次系统调用后可以确定这个值，如果要绕开系统调用，则必须在listen中指定地址并且使用bind参数。
$server_name|服务器名称。
$server_port|请求到达服务器的端口号。
$server_protocol|请求使用的协议，通常是HTTP/1.0或HTTP/1.1。
$uri|请求中的当前URI(不带请求参数，参数位于a r g s ) ， 不 同 于 浏 览 器 传 递 的 args)，不同于浏览器传递的args)，不同于浏览器传递的request_uri的值，它可以通过内部重定向，或者使用index指令进行修改。不包括协议和主机名，例如/foo/bar.html


### 原理
* 多个worker 争抢 master 与 client  的连接
* 利于nginx进行热部署
* 每个worker独立运行,不会造成服务的中断
* linux下io多路复用功能
* worker 一个请求2到4个连接数