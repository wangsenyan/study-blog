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