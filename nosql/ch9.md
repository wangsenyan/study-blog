## <center>复制</center>

### 主从复制

* 启动主从服务器
```s
mongod --dbpath dbs/master --port 10000 --master #开启主服务器
mongod --dbpath dbs/slave --port 10001 --slave --source localhost:10000

# --only 在从节点上指定只复制特定某个数据库(默认复制所有数据库)
# --slavedelay 用在从节点上，应用主节点的操作时增加延时(s)
# --fastsync 以主节点的数据快照为基础启动从结点
# --autoresync 如果从结点和主节点不同步了，自动重新同步
# --oplogSize 主节点oplog的大小(MB)
```
* 如果主节点绑定了 localhost:27017，启动时可以不添加源，随后添加
```s
>use local
>db.sources.insert({"host":"localhost:27017"})
>rs.slaveOk() #在从服务器，可读
```

### 副本集
* 有自动故障恢复功能的主从集群
* 没有固定的 "主节点"：选举一个"主节点"，当期不能工作时变更到其他节点
* 总有一个活跃点(primary) 和一个或多个备份节点(secondary) 
* 优先级最高的活跃结点，优先级相同则数据较新的节点获胜
* 活跃结点使用心跳来跟踪集群中有多少节点对其可见，如果不够半数，活跃结点自动降为备份节点
* 新活跃节点的数据被假定为系统的最新数据
* 读扩展
```s
#获取主机地址
cat /etc/hostname 

#启动服务器
mongod --dbpath {dbpath} --port {port1} --replSet {setname}/{hostname}:{port2}
mongod --dbpath {dbpath} --port {port2} --replSet {setname}/{hostname}:{port3}
...
mongod --dbpath {dbpath} --port {portn} --replSet {setname}/{hostname}:{portn-1}

#初始化，只一次 
>db.runCommand({
  "replSetInitiate": {
    "_id": {setname},
    "members": [
      {
        "_id": 1,
        "host": "{hostname}:{port1}"
      },
      {
        "_id": 2,
        "host": "{hostname}:{port2}"
      },
      {
        "_id": n,
        "host": "{hostname}:{portn}"
      }
    ]
  }
})

#设置优先级
> members.push({
  "_id":3,
  "host":"{hostname}:{port}",
  "priority":40
})
#指定仲裁节点
>members.push({
  "_id":3,
  "host":"{hostname}:{port}",
  "arbiterOnly":true
})


#执行初始化脚本
var config = {
  "_id": {setname},
  "members": [
    {
      "_id": 1,
      "host": "{hostname}:{port1}"
    },
    {
      "_id": 2,
      "host": "{hostname}:{port2}"
    },
    {
      "_id": n,
      "host": "{hostname}:{portn}"
    }
  ]
}
>rs.initiate(config)
#设置优先级
cfg = rs.conf()
cfg.members[0].priority = 1
cfg.members[1].priority = 1
cfg.members[2].priority = 5
rs.reconfig(cfg)
#增加一个成员，用于存储数据
>rs.add("host:port")
#增加一个arbiter,用于选举
>rs.add("host:port",true)
#查看信息
>rs.status()
```

* 副本中的节点
 - standard 常规节点
 - passive 不能成为活跃结点
 - arbiter 仲裁者，只参与投票，不接收复制的数据，也不能成为活跃节点

* 每个参与接待(非仲裁者)都有个优先权，按优先权大到小选出活跃结点，0 不能成为活跃节点


### 工作原理
* oplog 主节点的操作记录，存储在local中
* mongod --oplogSize 指定oplog大小，单位MB
* 复制状态和本地数据库
 - 用来存放所有内部复制状态，local,其内容不会被复制 
 - db.slaves.find()
 - syncedTo 确定哪些操作需要执行

* db.runCommand({getLastError:1,w:N}) 阻塞复制
  - 复制到N个节点超时时返回错误

* 诊断