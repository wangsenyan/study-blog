var connect = require('connect');
var app = connect();
var api = app.use()
             .use()
app.use()
   .use('api',api)
   .use()
function errorHandler(err,req,res,next){
    console.error(err.stack);
    res.setHeader('Content-Type','application/json');
    if(err.notFound){
        res.statusCode = 404;
        res.end(JSON.stringify({error:err.message}));
    }else{
        res.statusCode = 500;
        res.end(JSON.stringify({error:'Internal Server Error'}));
    
}
Promise.reject(msg) //被try{}catch()
```
4XX错误，5xx错误(代码错误、系统错误(网路超时、系统挂了))
-404 PageNotFoundError 页面没找到错误 | next(new PageNotFoundError(404,'Page Not Found'))
-400 ValidationError 表单验证错误 | next(new ValidationError(ValidationError.code.user.usernameWrong,'Field validation error,username length must b 4-30','username'))
-401
-403

5xx 在程序中没有被处理的错误会在最后的errorhandler自动处理成systemError

uncaughtException 错误
程序中没有正常处理到的错误，通过nodejs process监听process.on('uncaughtException')
解决办法 next(err) 
直接使用throw new Error("") 将会导致uncaughtException错误
在errorhandler中发生uncaughtException后应该记录log,然后退出process.exit(1)


unhandledRejection 错误
针对ES6 Promise 中吃掉的错误 reject 未被 catch
如果:Promise.reject(new Error('ress....'))
将会发生unhandledRejection错误, 通过 process.on(‘unhandledRejection’, (reason, p) => {})
异步中的错误无法通过try catch获取
return next(err)  传给errorHandler同时不再执行后续代码
function request(url, callback){
    var err = new Error('网络出错了');
    if(err) return calllback(err)

    var result;
    return callback(null, result)
}
Promise.catch((err)=>{
    next(err)
})或者.catch(next)
try{}catch{}的错误不能被.catch继续捕获