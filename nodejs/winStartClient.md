### redis添加服务
   redis-server.exe --service-install redis.windows.conf --loglevel verbose
### redis服务启动
   redis-server  --service-uninstall
### 启动客户端
   redis-cli.exe -h 127.0.0.1 -p 6379
### mongod加入到Windows本地服务中,win +a+x
  mongod.exe --logpath "e:/mongodb/data/log/mongodb.log" --  logappend --dbpath "e:/mongodb/data/db"
  --serviceDisplayName MongoDB --install
   
### mongod 启动服务
   net start MongoDB
