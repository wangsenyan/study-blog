var _ = require('underscore')
//_.each({a:5,z:2,t:3},console.log) //数组(element,index,list) 对象(value,key,list)
var a = _.map({one:1,two:3,three:5} , function(num,key){ //_.map()对象(value,key,list)
   return num*3// console.log(num*3)
})
console.log(a) //返回的是数组