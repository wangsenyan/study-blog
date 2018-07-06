## <center>web环境搭建</center>
### win环境
#### javaEE 
#### jdk
#### tomcat
### linux环境
#### java
* 下载java jdk  
可以下载后上传或直接wget,注意添加选项
```sh
wget --no-check-certificate --no-cookies --header "Cookie:oraclelicense=accept-securebackup-cookie" http://download.oracle.com/otn-pub/java/jdk/10.0.1+10/fb4372174a714e6b8c52526dc134031e/jdk-10.0.1_linux-x64_bin.tar.gz
# 检查文件是否为gzip
file jdk-10.0.1_linux-x64_bin.tar.gz
# 解压
tar -zxvf jdk-10.0.1_linux-x64_bin.tar.gz
```
* 添加到`/etc/profile`

```
export JAVA_HOME=/usr/local/lib/jdk-10.0.1
export JRE_HOME=$JAVA_HOME/jre
export CLASSPATH=.:$JAVA_HOME/lib:$JAVA_HOME/lib
```
* 然后执行 `source /etc/profile` 使配置生效
* 如果没有权限，`chmod -R 755 jdk-10.0.1`
* 测试是否成功

```sh
java --version
javac --version
```

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
  export PATH=$NODE_HOME:$PATH
```
* 添加后运行`source /etc/profile` 实现更改