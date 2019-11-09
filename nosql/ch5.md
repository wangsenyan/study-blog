## <center> 索引 </center>

* 原则
  - 做什么查询，哪些键值需要索引
  - 每个键的索引方向是怎么样的，保证常用在内存中
  - 如何应对扩展

* 无索引排序上限：不能在内存里面做T级别数据的排序
* 唯一键的键值为空，存为null
* 符合唯一索引
* 集合名和索引名加起来不能超过127字节

* $within 在形状内部
  - $center 圆
  - $box  矩形

```c
>db.collection.ensureIndex({"a":1,"b":1,"c":1},{"name":"myname"});
>db.runCommand("getLastError");
>db.collection.ensureIndex({"a":1,"b":1,"c":1},{"unique":true});
>db.collection.ensureIndex({"a":1,"b":1,"c":1},{"unique":true,"dropDups":true});//同时删除重复项，mongo3.0不支持了
>db.collection.ensureIndex({"a":1,"b":1,"c":1},{"background":true});
//后台添加索引

db.system.indexes.find({name:"api_1"}) //查看索引

db.logger.find({"model":"TimedTask"}).sort({"api":1}).hint({"_id":1}).explain()
//hint严格使用某个索引


>db.collection.dropIndexes("");
>db.runCommand({"dropIndexes":"collection_name","index":"index_name" });
>db.runCommand({"dropIndexes":"collection_name","index":"*" }); 
//删除索引


>db.map.ensureIndex({"gps":"2d"});//地理索引
 {"gps":[0,100]}
 {"gps":{"x":-30,"y":30}}
 {"gps":{"latitude":-180,"longitude":180}}

>db.map.ensureIndex({"gps":"2d"},{"min":-1000,"max":1000})
//指定最大最小值，默认 -180 ~180

>db.map.find({"gps":{"$near":[40,-73]}});
>db.runCommand({geoNear:"map",near:[40,-73],num:10});

>db.map.find({"gps":{"$within":{"$box":[[0,150],[90,80]]}}});
>db.map.find({"gps":{"$within":{"$center":[[0,150],40]}}})
```

