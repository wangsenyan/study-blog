## <center>web环境搭建</center>
### win环境
#### javaEE 
#### jdk
#### tomcat
### linux环境
#### java
#### tomcat
* `tomcat 9`以上搭配`jdk8`以上
* [下载tomcat](https://tomcat.apache.org/)
* 解压缩
* 启动

```sh
wget http://mirrors.shu.edu.cn/apache/tomcat/tomcat-8/v8.5.32/bin/apache-tomcat-8.5.32.tar.gz
tar -zxvf apache-tomcat-8.5.32.tar.gz
# 启动
cd apache-tomcat-8.5.3/bin && ./startup.sh 
# 停止
./shutdown.sh
```
* 更改`/etc/profile`
export 
### linux添加环境变量等
* `/etc/profile`
* 添加path,必须带上`$PATH`,用冒号`:`分割
```sh
  #set node npm path
  NODE_HOME=/usr/local/bin
  xport PATH=$NODE_HOME:$PATH
```
* 添加后运行`source /etc/profile` 实现更改