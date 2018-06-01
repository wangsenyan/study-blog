var async = require('async');
//series 的task参数可以是数组和对象
async.series({
    one:function(callback){
        callback(null,1);
    },
    two:function(callback){
        callback(null,2);
    }
},function(err,results){
    console.log(results);
})
//waterfall 每个waterfall函数产生的值都将传给下一个函数
async.waterfall([
    function(callback){
        callback(null,'one','two');
    },
    function(arg1,arg2,callback){
        // arg1 now equals 'one' and arg2 now equals 'two'
        callback(null,'three');
    },
    function(arg1,callback){
        // arg1 now equals 'three'
        callback(null,'done');
    }
],function(err,results){
    // result now equals 'done'
    console.log(results)
})
//
//async.parallel(tasks,[callback])
//并行执行，传给callback中的数组，按照tasks中声明的顺序而不是执行完成的顺序
//tasks为数组，则返回数组，对象即对象
async.parallel([
    function(callback){
        callback(null,'one');
    },
    function(callback){
        callback(null,'two');
    }
],function(err,results){

});
//parallelLimit(tasks,limit,[callback])
//limit限制同时并发的数量