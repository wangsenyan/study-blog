
### 游标

```js
var cursor = db.c.find();
while(cursor.hasNext()){
  obj = cursor.next();
	print(obj.x)
}

cursor.forEach(function(item){
	print(item.username)
})
```

* find - 当sort,skip,limit一起使用时，无论其位置变化，总是先sort再skip，最后limit。
* aggregate 有管道流的性质，$skip,$limit,$sort执行顺序跟位置一致。
* 顺序 由小到大
  1. 最小值
  2. null
  3. 数字(整型，长整型，双精度)
  4. 字符串
  5. 对象/文档
  6. 数组
  7. 二进制数据
  8. 对象ID
  9. 布尔型
  10. 日期型
  11. 时间戳
  12. 正则表达式
  13. 最大值

* 选项
  - $query
  - $maxscan：integer 指定查询做多扫描的文档数量
  - $min:document 查询的开始条件
  - $max:document 查询的结束条件
  - $hint:document 指定服务器使用哪个索引进程查询
  - $explain:boolean 获取查询执行的细节(索引 结果数量 耗时等)
    ```m
    db.logger.find({"api":"getCollections"}).explain();
    ```
  - $snapshot:boolean 确保查询的结果是在查询执行那一刻的一致快照

* mongo会移动不能放在原处的新文档


