## DOCKER
### 安装
#### Ubuntu安装
```sh
  curl -fsSL get.docker.com -o get-docker.sh
  sudo sh get-docker.sh --mirror Aliyun
```
#### 启动Docker CE
```sh
  sudo systemctl enable docker
  sudo systemctl start docker
```
  Ubuntu 14.04使用下面命令
```sh
  sudo service docker start
```
#### 建立docker用户组
```sh
  sudo groupadd docker
  sudo usermod -aG docker $USER 
```
#### 测试是否安装正确
```sh
  docker run hello-world

  Unable to find image 'hello-world:latest' locally
  latest: Pulling from library/hello-world
  ca4f61b1923c: Pull complete
  Digest: sha256:be0cd392e45be79ffeffa6b05338b98ebb16c87b255f48e297ec7f98e123905c
  Status: Downloaded newer image for hello-world:latest

  Hello from Docker!
  This message shows that your installation appears to be working correctly.

  To generate this message, Docker took the following steps:
  1. The Docker client contacted the Docker daemon.
  2. The Docker daemon pulled the "hello-world" image from the Docker Hub.
      (amd64)
  3. The Docker daemon created a new container from that image which runs the
      executable that produces the output you are currently reading.
  4. The Docker daemon streamed that output to the Docker client, which sent it
      to your terminal.

  To try something more ambitious, you can run an Ubuntu container with:
  $ docker run -it ubuntu bash

  Share images, automate workflows, and more with a free Docker ID:
  https://cloud.docker.com/

  For more examples and ideas, visit:
  https://docs.docker.com/engine/userguide/
```
### 使用镜像
#### 获取镜像
```sh
 docker pull [选项] [Docker Registry 地址[:端口号]/]仓库名[:标签]
```
具体选项 `docker pull --help` 查看，默认地址Docker Hub.  
* Docker 镜像库地址:地址的格式一般是<域名/IP>[:端口号]。默认地址是Docker Hub
* 仓库名 <用户名>/<软件名> 。默认library
```sh
 docker pull ubuntu:16.04
```
#### 运行
```sh
 docker run -it --rm ubuntu:16.04 bash
```
* `-it`:两个参数，`-i`:交互式操作，`-t` 终端，交互式终端
* `--rm`: 退出后删除容易，或手动`docker rm`
* `bash` 镜像后面的命令，交互式Shell,用bash
* `cat /etc/os-release` 查看当前系统版本
* `exit` 退出容易
#### 列出镜像
```sh
 $ docker image ls #列出镜像，顶层镜像
 $ docker image ls -a #列出所有镜像
 $ docker image ls -q #自动访问的id列表
 $ docker image ls --format "{{.ID}}: {{.Repository}}"
 $ docker image ls --format "table {{.ID}}\t{{.Repository}}\t{{.Tag}}"
 $ docker system df #查看镜像、容器、数据劵占用空间
 $ docker image ls -f dangling=true #列出虚悬镜像(dangling image)
 $ docker image prune #删除虚悬镜像
```
#### 删除
<镜像> 可以是 镜像短 ID、镜像长 ID、镜像名 或者 镜像摘要
```sh
 $ docker image rm [选项] <镜像1> [<镜像2> ...]
 $ docker image rm $(docker image ls -q redis)
```
#### commit
```sh
 $ docker run --name webserver -d -p 80:80 nginx #定制web服务器
 $ docker exec -it webserver bash #进入容器
 $ docker diff webserver #查看具体的改动
 $ docker commit #将容器的存储层保存下来称为镜像，存储层+原来镜像= 新镜像
```
语法  
   `docker commit [选项] <容器ID或容器名> [<仓库名>[:<标签>]]`
```sh
$ docker commit --author "Wang senyan <2633600702@qq.com>" --message "修改了网页" webserver nginx:v2
```
运行
```sh
 docker run --name web2 -d -p 81:80 nginx:v2
```
