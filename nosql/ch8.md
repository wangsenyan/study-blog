## <center>管理</center>

### 启动mongod服务
* --dbpath
  - 指定数据目录,默认是 /data/db
  - 每个mongod进程都需要独立的数据目录
  - 启动，会在数据目录中创建 mongod.lock 防止其他MongoDB进程使用该数据目录
* --port
  - 监听端口，默认 27017
  - 不同的mongod进程使用不同的监听端口
* --fork
  - 以守护进程的方式运行mongodb,创建服务器进程
* --logpath
  - 指定日志输出路径，而不是输出到命令行
  - --logappend保留原理的日志
* --config/-f
  - 指定配置文件
* --nohttpinter-face 关闭管理接口
* --bindip ip 只有ip可以连接
* --noscripting 完全禁止服务端JavaScript执行
### 停止mongodb
* ps -ef |grep  mongod
* kill pid  
* db.shutdownServer();

```sh
>mongod --port 27018 --dbpath /var/lib/mongodb2 --logpath /var/log/mongodb2/mongodb.log --fork

>service mongod start 
#使用配置文件
#可实现自动重启
#可使用OS级别设置mongod进程
```

### 监控
* db.runCommand({"serverStatus":1})
* 所有计数都是在服务器启动时开始计算的，如果过大，会复位，asserts中rollovers值会增加

[监控字段](serverStatus.json)

* globalLock ： 全局写入锁占用了服务器多少时间(微秒)
* mem ：服务器内存映射了多少数据，服务器进程的虚拟内存和常驻内存的占用情况(MB)
* indexCounters : B树在磁盘检索("misses")和内存检索("hits")的次数，如果比值上升，内存不足
* backgroudFlushing ：后台做了多少次fsync以及用了多少时间
* opcounters ：每种主要操作的次数
* asserts ：断言的次数

```sh
mongostat  #监控

sudo lsof | grep mongod | grep TCP #所有连接
```

* 工具：Magios,Munin,Ganglia,Cacti

### 安全和认证
* 创建然后重启 --auth
* system.users
* roles
  - readWrite 读及修改非系统集合和system.js集合上的数据能力
    -  collStats
    -  convertToCapped
    -  createCollection
    -  dbHash
    -  dbStats
    -  dropCollection
    -  createIndex
    -  dropIndex
    -  find
    -  insert
    -  killCursors
    -  listIndexes
    -  listCollections
    -  remove
    -  renameCollectionSameDB
    -  update
  - read
  - write
  - dbAdmin 提供system.indexes,system.namespace,system.profile集合
  - dbOwner 数据库所有者可以对数据库执行任何管理操作，包括readWrite,dbAdmin和userAdmin
  - userAdmin 提供在当前数据库上创建和修改角色和用户的功能
  - clusterAdmin 最大的集群管理访问
  - clusterManager 提供对集群的管理和监视操作
```sh

use database
db.createUser({user:'root',pwd:'wsy',roles:['readWrite','dbAdmin']})

mongod --port 27018 --dbpath /var/lib/mongodb2 --logpath /var/log/mongodb2/mongodb.log --fork --auth

db.auth("username","password")
```

### 备份和修复
* /data/db 中所有数据
* mongodump 热备份
 - mongodump -h dbhost --port port  -d dbname -o dbdirectory
 - 将所有查到的文档写入磁盘
* mongorestore
 - mongorestore -h <hostname><:port> -d dbname <path>
 - 数据恢复
 - -d 制定了要恢复的数据库
 - --drop 恢复前删除集合，否则与现有集合数据合并
```sh
mongorestore -d immoc --drop backup/immoc/
```

* fsync 
  - 能在MongoDB运行时复制数据目录还不会损毁数据
  - 强制服务器将所有缓冲区写入磁盘，还可以选择上锁阻止对数据库的进一步写入，直到释放锁为止
```sh
db.runCommand({"fsync":1,"lock":1});
db.$cmd.sys.unlock.findOne();解锁
db.currentOp()
```