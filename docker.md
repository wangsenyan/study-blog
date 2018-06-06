## <center>DOCKER</center>
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
  $ docker run hello-world

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
### Dockerfile
```txt
FROM nginx
RUN echo '<h1>Hello,Docker</h1>' > /user/share/nginx/html/index.html
```
#### FROM 指定基础镜像
好的服务类镜像有`nginx`, `redis`, `mongo`, `mysql`, `httpd`, `php`, `tomcat`, `node`, `openjdk`, `python`, `ruby`, `golang`等  
操作系统类镜像 `ubuntu`, `debian`, `centos`, `fedora`, `alpine`  
空白镜像 `FROM scratch`
#### RUN 执行命令
* shell格式，上面的例子
* exec格式 `RUN ["可执行文件", "参数1", "参数2"]`
* RUN 多行表示多次commit，多层镜像
```txt
FROM debian:jessie

RUN buildDeps='gcc libc6-dev make' \
    && apt-get update \
    && apt-get install -y $buildDeps \
    && wget -O redis.tar.gz "http://download.redis.io/releases/redis-3.2.5.tar.gz" \
    && mkdir -p /usr/src/redis \
    && tar -xzf redis.tar.gz -C /usr/src/redis --strip-components=1 \
    && make -C /usr/src/redis \
    && make -C /usr/src/redis install \
    && rm -rf /var/lib/apt/lists/* \
    && rm redis.tar.gz \
    && rm -r /usr/src/redis \
    && apt-get purge -y --auto-remove $buildDeps
```
Dockerfile 支持Shell类的行尾添加`\`的命令换行方式以及首行`#`注释的格式  
镜像是多层存储，每一层的东西并不会在下一层被删除，会一直跟随着镜像。因此镜像构建时，一定要确保每一层只添加真正需要添加的东西，任何无关的东西都应该清理掉。  
`docker build [选项]<上下文路径/url/->`
```sh
 docker build -t nginx:v3 .
```
#### [上下文](https://yeasy.gitbooks.io/docker_practice/content/image/build.html)
客户端/服务端(C/S)设计，需要本地和服务端配合， `COPY`, `ADD` 指令客户端，`docker build`在服务端
```txt
COPY ./package.json /app/
```
指的是复制上下文目录下的`package.json`
#### 其他docker build 的用法
* GIT repo 源
```sh
$ docker build https://github.com/twang2218/gitlab-ce-zh.git#:8.14
docker build https://github.com/twang2218/gitlab-ce-zh.git\#:8.14
Sending build context to Docker daemon 2.048 kB
Step 1 : FROM gitlab/gitlab-ce:8.14.0-ce.0
8.14.0-ce.0: Pulling from gitlab/gitlab-ce
aed15891ba52: Already exists
773ae8583d14: Already exists
...
```
* tar 压缩包构建
```sh
$ docker build http://server/context.tar.gz
```
* 从标准输入中读取Dockerfile进行构建
```sh
$ docker build - < Dockerfile

$ cat Dockerfile | docker build -

$ docker build - < context.tar.gz
```
如果发现标准输入的文件格式是 gzip、bzip2 以及 xz 的话，将会使其为上下文压缩包，直接将其展开，将里面视为上下文，并开始构建
### Dockerfile指令详解
#### COPY 复制文件
* COPY <源路径>...<目标路径>
* COPY ["<源路径1>",..."<目标路径>"]  
`COPY`指令将从构建上下文目录中`<源路径>`的文件/目录复制到新的一层的镜像内的`<目标路径>`位置。
#### ADD 更高级的复制
格式同`COPY`，但源路径为tar压缩文件的话，压缩格式为`gzip`, `bzip2`, `xz`的情况下，`ADD` 会自动解压缩这个压缩文件到`<目标路径>`去
```txt
  FROM scratch
  ADD ubuntu-xenial-core-cloudimg-amd64-root.tar.gz /
...
```
#### CMD 容器启动命令
* `shell`格式:`CMD<命令>`
* `exec`格式:`CMD["可执行文件","参数1","参数2"...]`，解析为JSON数组
* 参数列表格式:`CMD ["参数1", "参数2"...]`。在指定了 `ENTRYPOINT` 指令后，用 `CMD`指定具体的参数。  
Docker 不是虚拟机，容器就是进程
#### ENTRYPOINT 入口点
```txt
  FROM ubuntu:16.04
  RUN apt-get update \
      && apt-get install -y curl \
      && rm -rf /var/lib/apt/lists/*
  ENTRYPOINT [ "curl", "-s", "http://ip.cn" ]
```
```sh
 $ docker build -t myip .
 $ docker run myip
```
#### ENV 设置环境变量

* `ENV <key> <value>`

* `ENV <key1>=<vulue1> <key2>=<value2>...`
* 下列指令可以支持环境变量展开:  

  `ADD`、`COPY`、`ENV`、`EXPOSE`、`LABEL`、`USER`、`WORKDIR`、`VOLUME`、`STOPSIGNAL`、`ONBUILD`。
  
```txt
  ENV NODE_VERSION 7.2.0

  RUN curl -SLO "https://nodejs.org/dist/v$NODE_VERSION/node-v$NODE_VERSION-linux-x64.tar.xz" \
    && curl -SLO "https://nodejs.org/dist/v$NODE_VERSION/SHASUMS256.txt.asc" \
    && gpg --batch --decrypt --output SHASUMS256.txt SHASUMS256.txt.asc \
    && grep " node-v$NODE_VERSION-linux-x64.tar.xz\$" SHASUMS256.txt | sha256sum -c - \
    && tar -xJf "node-v$NODE_VERSION-linux-x64.tar.xz" -C /usr/local --strip-components=1 \
    && rm "node-v$NODE_VERSION-linux-x64.tar.xz" SHASUMS256.txt.asc SHASUMS256.txt \
    && ln -s /usr/local/bin/node /usr/local/bin/nodejs
```
#### ARG构建参数
* 格式: `ARG <参数名>[=<默认值>]`
#### VOLUME定义匿名卷
* `VOLUME ["<路径1>", "<路径2>"...]`
* `VOLUME <路径>`
```txt
 VOLUMN /data
```
被取代
```sh
 docker run -d -v mydata:/data xxxx
```
#### EXPOSE 声明端口
* `EXPOSE <端口1> [<端口2>...]`
* 只是声明，随机映射时，`docker run -P`时，会自动随机映射`EXPOSE`端口
#### WORKDIR 指定工作目录
* `WORKDIR <工作目录路径>`
#### USER 指定当前用户
* `USER <用户名>`
* 切换到指定用户
```txt
  RUN groupadd -r redis && useradd -r -g redis redis
  USER redis
  RUN [ "redis-server" ]
```
使用gosu,相当于sudo
```txt
  # 建立 redis 用户，并使用 gosu 换另一个用户执行命令
  RUN groupadd -r redis && useradd -r -g redis redis
  # 下载 gosu
  RUN wget -O /usr/local/bin/gosu "https://github.com/tianon/gosu/releases/download/1.7/gosu-amd64" \
      && chmod +x /usr/local/bin/gosu \
      && gosu nobody true
  # 设置 CMD，并以另外的用户执行
  CMD [ "exec", "gosu", "redis", "redis-server" ]
```
#### HEALTHCHECK 健康检查
* `HEALTHCHECK [选项] CMD <命令>`:设置检查容器健康状况的命令
* `HEALTHCHECK NONE`:如果基础镜像有健康检查指令，使用这行可以屏蔽掉其健康检查指令
* 选项 
  1.  `--interval=<间隔>`:两次健康检查的间隔，默认30s
  2.  `--timeout=<时长>`:健康检查命令运行超时时间，默认30s
  3. `--retries=<次数>`:连续失败指定次数，视为`unhealthy`,默认3次
  4. exit 返回值 0:成功 1:失败 2:保留
```
  FROM nginx
  RUN apt-get update && apt-get install -y curl && rm -rf /var/lib/apt/lists/*
  HEALTHCHECK --interval=5s --timeout=3s \
    CMD curl -fs http://localhost/ || exit 1
```
* `docker container ls` 查看状态
#### ONBUILD 
* `ONBUILD <其他指令>`
* `ONBUILD`是一个特殊的指令，它后面跟的是其它指令，比如 `RUN`, `COPY` 等，而这些指令，在当前镜像构建时并不会被执行。只有当以当前镜像为基础镜像，去构建下一级镜像的时候才会被执行。
```txt
  FROM node:slim
  RUN mkdir /app
  WORKDIR /app
  ONBUILD COPY ./package.json /app
  ONBUILD RUN [ "npm", "install" ]
  ONBUILD COPY . /app/
  CMD [ "npm", "start" ]
```
#### 参考文档
* Dockerfile官方文档:(https://docs.docker.com/engine/reference/builder/)
* Dockerfile最佳实践文档:(https://docs.docker.com/engine/userguide/eng-image/dockerfile_best-practices/)
*  Docker官方镜像 Dockerfile:(https://github.com/docker-library/docs)
#### Dockerfile多阶段构建
* Dockerfile
```txt
  FROM golang:1.9-alpine as builder

  RUN apk --no-cache add git

  WORKDIR /go/src/github.com/go/helloworld/

  RUN go get -d -v github.com/go-sql-driver/mysql

  COPY app.go .

  RUN CGO_ENABLED=0 GOOS=linux go build -a -installsuffix cgo -o app .

  FROM alpine:latest as prod

  RUN apk --no-cache add ca-certificates

  WORKDIR /root/

  COPY --from=0 /go/src/github.com/go/helloworld/app .

  CMD ["./app"]
```
* 构建镜像
```sh
 $ docker build -t go/helloworld:3
```
* 只构建某一阶段
```sh
 $ docker build --target builder -t username/imagename:tag .
```
* 从其他镜像复制文件
```txt
 COPY --from=nginx:latest /etc/nginx/nginx.conf /nginx.conf
```
