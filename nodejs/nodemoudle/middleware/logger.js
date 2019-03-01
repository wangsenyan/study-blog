var connect = require('connect');
var logger  = require('morgan');
var favicon = require('serve-favicon');
var fs = require('fs');
var log = fs.createWriteStream('./myapp.log',{flags:'a'})


var app = connect()
          .use(favicon(__dirname+'/favicon.ico'))
          .use(logger({format:':method :url :response-time ms',stream:log}))
          .use(hello)
          .listen(3000);
function hello(req,res,next){
    res.setHeader('Content-Type','text/plain');
    res.end('hello world');
    next();
}
/**
 * :req[头名称]
 * :res[]
 * :http-version
 * :response-time
 * :remote-addr
 * :data
 * :method
 * :url
 * :referrer
 * :user-agent
 * :status
 */
 /**
  * connect.logger.token('query-string',function(req,res){
  * return url.parse[req.url].query;
  * })
  */
/**
 * STREAM 、IMMEDIATE BUFFER
 * immedate:true 收到请求就写日志
 * 
 */
 //如何把loggger用在文件中

 /**
  * favicon.ico
  * maxAge:在内存中的最长时间
  */
/**
 * methodOverride()
 * connect,methodOverride('_method_')
 */