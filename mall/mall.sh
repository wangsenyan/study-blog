#!/bin/bash

# 安装必要软件docker
# 安装必要软件docker-compose
dk=$(which docker)
if [[ -z ${dk} ]]; then
   echo "docker is uninstall..."
fi
dc=$(which docker-compose)
if [[ -z ${dk} ]]; then
   echo "docker-compose is uninstall..."
   #apt install docker-compose
   exit 0
fi

echo "可配置docker加速,参考https://www.jianshu.com/p/5e71e6572e71"
echo "注意空格"


# 准备文件
# 涉及nacos,seata,sentinel,kafka,elasticsearch,logstash,kibana,redis,mongo,mysql

# nacos
# mysql根据容器名称访问,不用宿主映射的端口
# 修改env/nacos-hostname.env,更改数据库和jvm参数
# JVM_XMS=128m
# JVM_XMX=128m
# JVM_XMN=64m

git clone https://github.com/nacos-group/nacos-docker.git
cd nacos-docker
# 追加jvm限制,防止内存占用过多
echo "JVM_XMS=128m" >>env/nacos-hostname.env
echo "JVM_XMX=128m" >>env/nacos-hostname.env
echo "JVM_XMN=64m" >>env/nacos-hostname.env
docker-compose -f example/cluster-hostname.yaml up -d

# 启动sentinal
cd ..
wget https://github.com/alibaba/Sentinel/releases/download/v1.8.0/sentinel-dashboard-1.8.0.jar
touch Dockerfile
echo "FROM openjdk:8">>Dockerfile
echo "ADD sentinel-dashboard-1.8.0.jar sentinel-dashboard-1.8.0.jar">>Dockerfile
echo "EXPOSE 8080">>Dockerfile
echo 'ENTRYPOINT ["java","-jar","sentinel-dashboard-1.8.0.jar"]'>>Dockerfile
docker build -t sentinel-dashboard:1.8.0 .


#nginx密码登录
htpasswd -c /etc/nginx/htpasswd admin

#docker build -t sentinel-dashboard:1.8.0 /home/sentinel
docker pull mysql:5.7
docker pull redis:5
docker pull nginx:1.10
docker pull rabbitmq:3.7.15-management
docker pull elasticsearch:7.6.2
docker pull kibana:7.6.2
docker pull logstash:7.6.2
docker pull mongo:4.2.5

sysctl -w vm.max_map_count=262144
sysctl -p

mkdir -p /mydata/elasticsearch/data/
chmod 777 /mydata/elasticsearch/data


# 创建目录之后将nginx.conf文件上传到该目录下面
mkdir -p /mydata/nginx/
cp conf/nginx.conf /mydata/nginx/


mkdir /mydata/logstash
cp conf/logstash.conf /mydata/logstash/
