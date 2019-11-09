## <center>聚合</center>

### 基本操作
* count
* distinct
* group 每组有一个独立的累加器
  - doc 当前文档
  - prev 累加器文档(本组当前的结果)
* MapReduce
  - 映射(map) 操作
  - 洗牌(shuffle) 分组
  - 化简(reduce) 列表->单值
  - key 是分类标准？

  - finalize reduce得到输出后执行，然后将结果存到临时集合中
  - keeptemp:true 保存保存的临时集合，out自动保存
  - query,limit,skip 过滤，和其他字段顺序有关
  - scope 作用域,在客户端使用客户端的值
  - verbose：获取更多的输出

```js
>db.runCommand({"distinct":"people","key":"age"});


>db.runCommand({"group":{
"ns":"logger",
"key":"api",
"initial":{"createdAt":0},
"$reduce":function(doc,prev){
   print(doc)
   if(doc.createdAt>prev.createdAt){
	    prev.model = doc.model;
	 }
},
"condition":{"createdAt":{"$gt":"2018/09/09"}}
}})




>map = function(){
  for(var key in this)
	  emit(key,{count:1});
}

reduce = function(key,emits){
  total =0;
	for(var i in emits){
	  total+=emits[i].count;
	}
	return {"count":total};
}

mr = db.runCommand({"mapreduce":"vehicle","map":map,"reduce":reduce,"out":"sss"});
db[mr.result].find()

{
	"result":"sss", //临时表名
	"timeMillis":12,//运行时间,毫秒
	"counts":{
		"input":12, //发送到map函数的文档个数
		"emit":14,  //在map函数中emit被调用的次数
		"output":5  //结果集合中创建的文档数量
	},
	"ok":true
}


map = function(){
  for(var i in this.dataArr){
	  emit(this.dataArr[i].vin,{count:1});
	}
}

reduce = function(key,emits){
  var total = 0;
	for(var i in emits)
	  total+=emits[i].count;
	return {"count":total};
}

mr = db.runCommand({"mapreduce":"information_classify","map":map,"reduce":reduce,"out":"sss"});
db[mr.result].find().sort({count:1});




>reduce = function(key,emits){
  var total = 0;
	var time = new Date();
	for(var i in emits){
	  total+=emits[i].count;
		time = emits[i].time;
	}
	return {"count":total,time:time};
}

mr = db.runCommand({"mapreduce":"information_classify","map":map,"reduce":reduce,"query":{"status":{"$gt":"0"}},"scope":{now:new Date()},"out":"sss"});
db[mr.result].find().sort({count:1});
```