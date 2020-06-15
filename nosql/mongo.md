### mongo操作

```sql
db.getCollection().update({},{$set:{}}) //修改或添加
db.getCollection().update({},{$unset:{key:1}}) //删除
db.getCollection().update({},{$inc:{key:50}})
db.getCollection().update({},{$push:{key:{}}})

db.getCollection({"_id":"xxx"},{"$addToSet":{"emails":{"$each":["a","b","c"]}}})
```

### 关键词
```
$inc : 增加已有键值或者不存在的时候创建一个键,只能用来整数长整数或双精度浮点数
$push: 向已经有的数组末尾加入一个元素，没有创建一个
$addToSet: 向集合中添加，避免重复
$pull:将所有匹配的部分删掉
$pop: {$pop:{key:1}} 从数组末尾删除一个元素
$ 定位查询文档已经匹配的元素，并进行更新(数组)

upsert:特殊更新，要是没有文档符合更新条件，就会以这个条件和更新文档为基础创建一个新的文档. 创建+更新
db.getCollection().update({},{},true)
save:不存在插入，存在的时候更新
db.getCollection().update({},{},flase,true) 第四个为true，表示批量更新
```

### [不同服务器复制数据](http://www.pclic.com/article/a120191023173277.html)

```mongo
//复制所有collection
db.copyDatabase('analysis','analysis','39.106.214.176:27018');

//复制某个表，query可选，空为全部
{ cloneCollection: "", from: "", query: { } }
db.runCommand({cloneCollection : "analysis.vehicle_diagnosis", from : "39.106.214.176:27018"})
```
### 备份

```sh
# 备份
mongodump -h 47.104.234.70:27018 -d analysis -o /home/
# 还原
mongorestore -d analysis0 --dir /home/analysis/
```

### roles 详解如下：

* 数据库用户角色（Database User Roles)

  - read : 授权User只读数据的权限，允许用户读取指定的数据库
  - readWrite  授权User读/写数据的权限，允许用户读/写指定的数据库

* 数据库管理角色（Database Admininstration Roles)

  - dbAdmin：在当前的数据库中执行管理操作，如索引的创建、删除、统计、查看等
  - dbOwner：在当前的数据库中执行任意操作，增、删、改、查等
  - userAdmin ：在当前的数据库中管理User，创建、删除和管理用户。
​​​​​​​
* 备份和还原角色（Backup and Restoration Roles)​​​​​​​

  - backup
  - restore

* 跨库角色（All-Database Roles)

  - readAnyDatabase：授权在所有的数据库上读取数据的权限，只在admin 中可用
  - readWriteAnyDatabase：授权在所有的数据库上读写数据的权限，只在admin 中可用
  - userAdminAnyDatabase：授权在所有的数据库上管理User的权限，只在admin中可用
  - dbAdminAnyDatabase： 授权管理所有数据库的权限，只在admin 中可用

* 集群管理角色（Cluster Administration Roles)

  - clusterAdmin：授权管理集群的最高权限，只在admin中可用
  - clusterManager：授权管理和监控集群的权限
  - clusterMonoitor：授权监控集群的权限，对监控工具具有readonly的权限
  - hostManager：管理server

* 超级角色（super master  Roles)

  - root ：超级账户和权限，只在admin中可用le

```mongo
#  在非auth环境下添加用户
use products
db.createUser({"user" : "accountAdmin01",
               "pwd": "cleartext password",
               "customData" : { employeeId: 12345 },
               "roles" : [ { role: "clusterAdmin", db: "admin" },
                           { role: "readAnyDatabase", db: "admin" },
                          "readWrite"] },
               { w: "majority" , wtimeout: 5000 })
use admin;
db.createUser( { user: "user", pwd: "pass", roles: ["readWriteAnyDatabase","dbAdminAnyDatabase","clusterAdmin" ] } )             
```

### 索引

* 查看
```
db.getCollection("collectionName").getIndexes();
```
* 查看索引大小
```
db.getCollection("").totalIndexSize()
```
* 添加
```
db.getCollection("collectionName").ensureIndex({"paramName":1});
```

* 修改
```
db.getCollection().reIndex()

```
* 删除
```m
//删除所有
db.getCollection().dropIndexes()  
//删除指定
db.getCollection().dropIndex("索引名称")
```

### 查询

```c
db.foo.find({"$where":function(){
   for(var current in this){
	   for(var other in this){
		    if(current!=other&&this[current]==this[other]){
				  return true;
				}
		 }
	 }
	 return false;
}})
```

### ubuntu下默认路径
* 默认数据文件  /var/lib/mongodb/
* 默认日志文件路径 /var/log/mongodb/mongodb.log
* 可执行文件路径 /usr/bin/mongo  /usr/bin/mongod

···········

```sh
db.getCollection("").totalIndexSize() #某个表的索引
db.runCommand({"collStats":collection}); #表的信息
```