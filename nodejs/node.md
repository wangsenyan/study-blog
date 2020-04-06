### node安装
#### linux
* 下载源代码 -[nodejs](https://nodejs.org/dist/v10.6.0/node-v10.6.0.tar.gz)
* 源代码安装
```sh
wget https://nodejs.org/dist/v10.6.0/node-v10.6.0.tar.gz
tar -zxvf node-v10.6.0.tar.gz
#更改权限
sudo chmod -R 755 node-v10.6.0.tar.gz
cd node-v10.6.0.tar.gz
sudo ./configure
sudo make
sudo make install
```
* Ubuntu apt-get
```sh
sudo apt-get install nodejs
sudo apt-get install npm 
```
### node后台运行
  nohup node /xx/xx/app.js &(nohup command &)后台进程容易挂掉
  pm2  npm install -g pm2    ->pm2 start app.js ->pm2 stop ->pm2 list
  pm2 restart 重启医用  pm2 describe id|all   程序信息

### mongodb后台运行
  ```sh
   mongod -fork --dbpath=/root/mongo/mongodb/data/db/ --logpath=/root/mongo/mongodb/log/mongodb.log --logappend
   echo $LANG
   pm2 web(端口9615)
  ```
  ```
  npm cache clean -f 清除npm cache
  npm install -g n 安装n模块
  n stable 安装稳定版本
  ```
### __filename 当前正在执行的脚本文件名

### setTimeout(cb,ms)
  clearTimeout(t)停止之前通过setTimeout()创建 定时器
  setInterval(cb,ms)/clearInterval(t)
### field():用于 定义 要查询的字段（支持字段排除）
  field($field,$except=false)返回当前模型实例,如果true是排除
  显式传入所有字段，可以$model->field(true)->select()
  getField()用于查询某个字段的值
  getFiled($field,$sepa=null),如果null返回数组
 alias()别名
 IN 如SELECT * FROM user WHERE uid IN(2,3,4)
 group_concat( ) group by ;将分类后的打印在一行separator “”用空格分格同行的
### 
 .mysqldump -uwangsenyan -p  myshop --add-drop-table >e:\new\myshop.sql 导出数据库myshop
### 
 escape()对字符串编码可以在所有的计算机上读取该字符串，不会对ASC||字母和数字进行编码，也不会对* @ - _ + . / 。编码
### 
 split()从指定字符分割为数组
###
  http://momentjs.cn/
  moment().format()日期格式化
  moment("20171224","YYYYMMDD").fromNow()相对时间
###
  Promise.resolve(value);提供自定义promise值
  Promise.resolve(promise);创建promise副本的能力
  Promise.resolve(theanablel)；类似Promise转换真正Promis对象
  执行resolve方法，then方法会被调用
###
   assign()加载一个新的文档

###
   thinkjs   ipm install -g thinkjs
   thinkjs new demo 创建新的demo

### path方法
   `normalize()非标准转换成标准路径字符串，解析"."和"..",返回标准路径，..删除前面字符，.删除后面斜杠，将多个斜杠转换成一个斜杠，将win反斜杠转换成正斜杠，路径以斜杠结尾则保留，var myPath = path.normalize(".//a//b//d//..//c/e//..//");
    console.log(myPath);    //    a\b\c\
    path.join(_dirname,'a','b','c');  _dirname\a\b\c
    resolve()以应用程序根目录为起点，根据所有的参数字符串解析出一个绝对路径
                 var resolve = path.resolve('a', 'b', 'c'); _dirname\a\b\c
    relative()获取两个路径之间的相对 关系，path.relative(from,to),从from跳到to的路径
    dirname()当参数值为目录路径时，该方法返回该目录的上层目录；当参数值为文件路径时，该方法返回该文件所在的目录。
    basename(p,[ext]) p完整路径，ext去掉文件的扩展名
    extname()获取一个路径中的扩展名
    path.sep()操作系统指定的文件分隔符
    path.delimiter()操作系统指定的路径分隔符
    / 绝对路径， ./ 相对路径``

### 核心模块在lib/目录下，优先加载 
    require(example/path/to/file) path/to/file解析成相对于example-module的位置  
    module.exports= 相当于函数
    require.cache 被引入的模块将被存入这个对象中
    对module.exports的赋值必须立即完成，不能在任何回调中完成

### 同步和异步，消息通信机制
    同步---没返回就等待  异步---马上有状态 的结果
    阻塞非阻塞 与对方处理状态无关，与自己有关

### express建立在nodejs内的http模块上
    

### web开发 express+ejs/jade/html+mongoose/mysql
    rest开发 ：restify  
    web聊天室 Express+socket.io  
    web 爬虫 cheerio/request  
    web博客：hexo  
    web论坛 nodeclub  
    web幻灯片 cleaver  
    前端包管理平台 bower.js  
    Oauth认证 passport  
    定时任务工具: later  
    浏览器环境工具: browserify  
    命令行编程工具：Commander  
    Web控制台工具: tty.js  
    客户端应用工具: node-webkit  
    操作系统node-os  

### unescape()可以对通过escape编码的字符串进行解码
  可以用decodeURL()和decodeURLComponent()

### 搭建node服务器
  ```js
  var http = require("http");
  //设置主机名
  var hostName = '127.0.0.1';
  //设置端口
  var port = 8080;
  //创建服务
  var server = http.createServer(function(req,res){
      res.setHeader('Content-Type','text/plain');
    //res.setHeader('Access-Control-Allow-Origin',"*")
      //res.setHeader("Access-Control-Allow-Headers", "Origin, X-Requested-     With, Content-Type, Accept"); 
      res.end("hello nodejs");

  });
  server.listen(port,hostName,function(){
      console.log(`服务器运行在http://${hostName}:${port}`);
  });
  ```
### async 或者setTimeout()实现sleep
  ```js
    async function test() {
    console.log('Hello')
    await sleep(1000)
        console.log('world!')
    }

    function sleep(ms) {
      return new Promise(resolve => setTimeout(resolve, ms))
    }
    test()
  ```
---------------------
### 其他
  Node 里有readFile和对应的同步方法readFileSync，但http.get() 却没有 http.getSync()，如果要实现一个http.getSync()，怎么做？  

  readFile异步，readFileSync同步异步读取不能读取文件大小，分片读取，每次异步读取8k内容到buffer，并将buffer的内容存储到数组，然后合并如果能正确读取文件大小，则直接生成与文件大小相同，并将内容读取到buffer里面readFileSync不带回调函数，结果是直接返回libuv的文件操作方法跟socket的实现方式原理不一样，对于socket处理，libuv是调用系统本身的非阻塞特性，而fs模块，则是通过线程池 模拟getSync 这种方法，在libuv框架下是无法实现的，libuv从底层调用开始就是非阻塞的，是操作系统提供，所以你无论用什么黑魔法实际效果都是异步，但对于fs模块来说，仅仅是利用线程池模拟出异步的效果，所以能，非系统自带的特性，所以能写出同步的api。

### 内存
* process.memUsage()  
* os.totalmem()
* os.freemem()

```js
var showMem = function() {
   var mem = process.memoryUsage();
   var format = function(bytes)
   {
     return ((bytes/(1024*1024)).toFixed(2) + ' MB');
   }
   console.log('process:rss ' + format(mem.rss) + 'process:heapTotal'+format(mem.heapTotal) + 'process:heapUsed'+format(mem.heapUsed));
   console.log('---------------------------------------------------------------------');
}
var useMem = function()
{
  var size = 200*1024*1024;
  //var buf = new Buffer(size);
  var buf = new Array(size);
  for(var i=0;i<size;i++)
    buf[i]=0;
  return buf;
}
var total = []
for(var i=0;i<15;i++)
{
   showMem();
   total.push(useMem());
}
showMem();
```

* 内存泄漏
```js
var leekList = [];
var leek = function()
{
  leekList.push("leek  "+ Math.random());
}
http.createServer(function(req,res){
   leek();
   res.writeHead(200,{'Content-Type':"text/plain"});
   res.end('Hello world');
}).listen(12345);
console.log('server on 12345');
```