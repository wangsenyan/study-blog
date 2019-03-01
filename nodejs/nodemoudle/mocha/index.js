var fs = require('fs')
exports.limit = function(num){
    if(num<0){
        return 0;
    }
    return num;
}
exports.async  = function(callback){
    setTimeout(function(){
        callback(10);
    },10);
};
exports.getContent = function(filename,callback){
    fs.readFile(filename,'utf-8',callback);
};
function _adding(num1,num2){
    return num1+num2;
}