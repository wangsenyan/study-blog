```
var request = require('superagent');
request.post(url)
       .send({key:value})
       .set('X-API-Key','footer')
       .set('Accept','application/json')
       .end(function(res){
        //逻辑
       })
```
```
request('GET',url).end(cb);
```
```
request.get('http://example.com/search')
       .end(function(res){
        //...
       })
```
```
request.head('/favicon.ico')
       .end(function(res){})
```
```
request.del(url).end(cb);
```
默认方法是get
设置头字段 set()
```
request.get(url)
       .set('API-Key','footer')
       .set('User-agent','')
       .end(cb)
||
request.get(url)
       .set({'API-Key':'footer',Accept:'application/json'})
       .end(cb)
```
Get请求 相当于"/search?query=Manny&range=1..5&order=desc"
```
request
   .get('/search')
   .query({ query: 'Manny' })
   .query({ range: '1..5' })
   .query({ order: 'desc' })
   .end(function(res){
   });
OR
request
  .get('/search')
  .query({ query: 'Manny', range: '1..5', order: 'desc' })
  .end(function(res){
  });
OR 
request
    .get('/querystring')
    .query('search=Manny&range=1..5')
    .end(function(res){
    });
OR 
request
    .get('/querystring')
    .query('search=Manny')
    .query('range=1..5')
    .end(function(res){
    });
```
POST/PUT请求
```
request.post('/user')
    .set('Content-Type', 'application/json')
    .send('{"name":"tj","pet":"tobi"}')
    .end(callback)
OR 
request.post('/user')
    .send({ name: 'tj', pet: 'tobi' })
    .end(callback)
OR
request.post('/user')
    .send({ name: 'tj' })
    .send({ pet: 'tobi' })
    .end(callback)

```
默认发送字符串，则Content-Type为application/x-www-form-urlencoded,多次调用江永&链接
name=tj&pet=tobi
```
request.post('/user')
    .send('name=tj')
    .send('pet=tobi')
    .end(callback);

request.post('/user')
    .type('form') //form-data+urlencoded
    .send({ name: 'tj' })
    .send({ pet: 'tobi' })
    .end(callback)
```
设置Content-Type用 \.type()
设置接受类型 \.accept
查询字符串 \.query
```?format=json&dest=/login
request
  .post('/')
  .query({ format: 'json' })
  .query({ dest: '/login' })
  .send({ post: 'data', here: 'wahoo' })
  .end(callback);
```
res.body |res.params |res.query |res.text

Response text
#res.text包含未解析前的响应内容，一般只在mime类型能够匹配text/,json,x-www-form-urlencoding的情况下，默认为nodejs客户端提供,这是为了节省内存\.因为当响应以文件或者图片大内容的情况下影响性能.
Response body
#响应数据也会自动的解析，当为一个Content-Type定义一个解析器后，就能自动解析，默认解析包含application/json和application/x-www-form-urlencoded,可以通过访问res\.body来访问解析对象.
Response header fields
Response Content-Type
Response status
req.abort() //中止请求
req.timeout() //定义超时时间

.auth()

```
request
  .get('/some.png')
  .redirects(2)
  .end(callback);
```
请求流来输送数据
```
var request = require('superagent')
  , fs = require('fs');

var stream = fs.createReadStream('path/to/my.json');
var req = request.post('/somewhere');
req.type('json');
stream.pipe(req);
```
```
var request = require('superagent')
  , fs = require('fs');

var stream = fs.createWriteStream('path/to/my.json');
var req = request.get('/some.json');
req.pipe(stream);
```
复合请求 .part()

```
var req = request.post('/upload');

 req.part()
   .set('Content-Type', 'image/png')
   .set('Content-Disposition', 'attachment; filename="myimage.png"')
   .write('some image data')
   .write('some more image data');

 req.part()
   .set('Content-Disposition', 'form-data; name="name"')
   .set('Content-Type', 'text/plain')
   .write('tobi');

 req.end(callback);
```
附加文件 .attach(name,[path],[filename]) 和 .field(name,value)

```
request
  .post('/upload')
  .attach('avatar', 'path/to/tobi.png', 'user.png')
  .attach('image', 'path/to/loki.png')
  .attach('file', 'path/to/jane.png')
  .end(callback);
```
字段值,上传图片同时添加自己的名字邮箱
```
request
   .post('/upload')
   .field('user[name]', 'Tobi')
   .field('user[email]', 'tobi[@learnboost](/user/learnboost).com')
   .attach('image', 'path/to/tobi.png')
   .end(callback);
```
缓存响应 req.buffer(false)
异常处理,当err参数提供的话
```
request.post('/upload')
       .attach('image','path/to/tobi.png')
       .end(function(err,res){
        //
       })
OR 
request.post('/upload')
       .attach('image','')
       .on('error',handle)
       .end(function(res){
        //
       })
```
res.error 检查4xx和5xx的http错误响应

