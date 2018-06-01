1. npm install superagent cheerio --save
2. 右键源码，Ctrl+F查找
3. JSON.stringify({}) 从一个对象解析出字符串
 ```js
  var a={a:1,b:2}
  JSON.stringify(a[,replacer[,space]])
  "{"a":1,"b":2}"
 ```
4. JSON.parse(str)从一个字符串中解析出json对象
 ```js
    var str='{"name":"hhh","age":"22"}'
    JSON.parse(str)
    Object
    1.age:"22"
    2.name: "hhh"
 ```
