var connect = require('connect');
//var url = require('connect');
var logger2 = require('./logger_test.js')
//var path = url.parse(req.url).pathname;
var app = connect();

app.use(logger2(':method :url'))
   .use('/admin',restrict)
   .use(function hello(req,res){
    foo();
    res.setHeader('Content-Type','text/plain');
    res.end('hello world');
   })
   .use(errorHandler())
   .listen(3000);

function logger(req,res,next){
    console.log('%s%s',req.method,req.url);
    next();
}
function logger1(req,res,next){
    console.log('%s%s',req.method,req.url);
    console.log('this is admin')
    next();
}
function hello(req,res){
    res.setHeader('Content-Type','text/plain');
    res.end('Hello world');
}
/**authorization:<type><credentials>
 *type验证类型，常见的是"基本验证(Basic)"
 *<credentials>基本验证方案
 */
function restrict(req,res,next){
    var authorization = req.headers.authorization;
    if(!authorization) return next(new Error('Unauthorized'));
    var parts = authorization.split(' ');
    var schema = parts[0]
    var auth  =new Buffer(parts[1],'base64').toString().split(':');
    var user = auth[0]
    var pass = auth[1];

    authenticateWithDatebase(user,pass,function(err){
        if(err) return next(err);
        next();
    })
}
function admin(req,res,next){
    switch(req.url){
        case '/':
          res.end('try/users');
        case '/users':
          res.setHeader('Content-Type','application/json');
          res.end(JSON.stringify(['tobi','lokj','jane']));
          break;
    }
}
function rewrite(req,res,next){
    var match = path.match(/^\/blog\/post\/(.+)/)
    if(match){
        findPostIdBySlug(match[1],function(err,id){
            if(err) return next(err);
            if(!id)return next(new Error('User not found'));
            req.url = '/blog/posts/'+id;
            next();
        });   
    }else{
        next();
    }
}
function errorHandler(){
    var env = process.env.NODE_EVN || 'development';
    return function(err,req,res,next){
        res.statusCode = 500;
        switch(env){
            case 'development':
               res.setHeader('Content-Type','application/json');
               res.end(JSON.stringify(err));
               break;
            default:
               res.end('Server error')
        }
    }
}