//作为对象调用方法，绑定到改对象上
```
var point = { 
x : 0, 
y : 0, 
moveTo : function(x, y) { 
    this.x = this.x + x; 
    this.y = this.y + y; 
    } 
}; 
```
//作为函数调用，this绑定的全局对象
```
function makeNoSense(x) { 
this.x = x; 
} 
 
makeNoSense(5); 
x;// x 已经成为一个值为 5 的全局变量
```
//作为构造函数调用,绑定到新创建的对象上
```
function Point(x, y){ 
   this.x = x; 
   this.y = y; 
   this.moveTo =function(x,y){
    this.x=x;
    this.y=y;
   }
}
var p1 = new Point(0,0)继承moveTo(),如果this.moveTo去掉this,不会继
p1.moveTo.apply(p3,[10,10]) 将p1的moveTo()应用到p3
```