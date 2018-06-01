/**
 *callback <function> 只在有值的索引上执行
 *currentValue <element> 正在处理的当前元素
 *index <number> 当前元素的索引
 *array <Array> map方法被调用的数组
 *thisArg this值
 */
let new_array=arr.map(function callback(currentValue,index,array){
    //return element for new_array
})[,thisArg]

var elems = document.querySelectorAll('select option:checked');
var values = Array.prototype.map.call(elems,function(obj){
    return obj.value;
})
//FUnction.prototype.call()
//function.call(thisArg,arg1,arg2,...) 返回值:用指定的this值和参数调用函数的结果