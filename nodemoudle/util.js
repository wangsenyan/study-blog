const util = require('util'); //引入util

//util.callbackify(original); //original<funtion>async 异步函数;return 传统回调函数
//将async异步函数转换成遵循Node.js回调分格的函数
async function fn(){
    //return await Promise.resolve('hello world');
    return await Promise.reject(null)
}
const callbackFunction = util.callbackify(fn);
callbackFunction((err,ret)=>{
    //if(err) throw err;
    err&&err.hasOwnProperty('reason')&&err.reason === null;//true
})
//异步，异常堆栈错误追踪，如果回调异常，进程会触发'uncaughtException'异常，如果没被捕获，进程会退出
//const NODE_DEBUG=foo;
const debuglog = util.debuglog('foo');
debuglog('hello from foo [%d]',123);
//util.format(format[,...args]) // format <string> 一个类似printf的格式[字符串]
/**
 * %s
 * %d
 * %i
 * %f
 * %j
 * %o
 * %O
 * %%
 */
/**
 * util.inspect(object[,options])
 * options <object>
 *  showHidden:true/false 是否显示可枚举
 *  depth <number> 格式化object递归的次数
 *  coloers <boolean>
 *  customInspect <boolean> 
 *  sowProxy <boolean> Proxy对象和函数会展示他们的target和handler对象
 *  maxArrayLength <number> 
 */