## \u0000-\uffff unicode编码 两个字节表示一个汉字
## '\u{1F680}' === '\uD83D\uDE80'
## javascript内部，字符以UTF-16的格式存储，每个字符固定为2个字节
## codePointAt()返回正确的32位UTF-16字符的码点
## ``` for...of...循环正确识别32位的UTF-8字符
 ```js
    let s = '𠮷a';
    for (let ch of s) {
      console.log(ch.codePointAt(0).toString(16));
    }
 ```
## string.formCodePoint()
## '\u01D1'.normalize() === '\u004F\u030C'.normalize()
## indexOf(),includes(),startsWith(),endsWith()--->number,boolean,boolean,boolean
## string.repeat() 元字符串重复n次
## ``` append()元素末尾添加 `模板`,html转换成可见视图，${变量}内部任意表达式
 还可以是函数${fn()}
 ```js
$('## result').append(`
    There are <b>${basket.count}</b> items
     in your basket, <em>${basket.onSale}</em>
    are on sale!
  `);
 ```

## String.raw({ raw: ['t','e','s','t'] }, 0, 1, 2);
## ...扩展运算符，将数组转为用逗号分隔的参数序列，主要用于函数调用
 ```js
 [...document.querySelectorAll('div')]
 ```
## Array.from()将类数组转换成数组
 ```js
 Array.from([a,b,c],x=>x+x) ===Array.from().map(x=>x+x)
 ```
## Array.prototype.copyWithin(target, start = 0, end = this.length)
## find
```js
  [1, 5, 10, 15].find(function(value, index, arr) {
    return value > 9;
  }) //(当前值，位置，数组)，找出第一个为true的
```
## findIndex
```js
[1, 5, 10, 15].findIndex(function(value, index, arr) {
  return value > 9;
})
function f(v){
  return v > this.age;
}
let person = {name: 'John', age: 20};
[10, 12, 26, 15].find(f, person); 
```
## ['a', 'b', 'c'].fill(value, start, end)
## keys() 对键名遍历
 * values 对键值的遍历
 * entries()对键值对的遍历
```js
for (let [index, elem] of ['a', 'b'].entries()) {
  console.log(index, elem);
}
```
## includes和indexOf()
```js
 (NaN).includes(NaN)  //true
 (NaN).indexOf(NaN)   //false
```txt
Map 结构的has方法，是用来查找键名的，比如Map.prototype.has(key)、WeakMap.prototype.has(key)、Reflect.has(target, propertyKey)。
Set 结构的has方法，是用来查找值的，比如Set.prototype.has(value)、WeakSet.prototype.has(value)
```
## forEach(), filter(), reduce(), every() 和some()都会跳过空位。
 map()会跳过空位，但会保留这个值
 join()和toString()会将空位视为undefined，而undefined和null会被处理成空字符串。
 array.filter(f(x))过滤===filter(f(x),array)
 every()方法用于检测数组所有元素是否都符合条件
## ## ## object
```js
 const obj = {
   get foo(){},
   set foo(x){}
 }
```
## Object.is('object1','object2')  
```js
 Object.is(+0, -0) // false 
 Object.is(NaN, NaN) // true
```
## Object.assign(a,b,c)合并可枚举属性，覆盖重复，浅拷贝
 会将字符串转换成数组拷贝人目标对象,string->array 
## Object('abc') // {0: "a", 1: "b", 2: "c", length: 3, [[PrimitiveValue]]: "abc"}      有length就可以遍历 
 Object.assign只能进行值的复制，如果要复制的值是一个取值函数，那么将求值后再复制
## 用Object.assign()克隆
```
function clone(origin) {
  let originProto = Object.getPrototypeOf(origin);
  return Object.assign(Object.create(originProto), origin);
}
```
## 枚举
 * for...in循环：只遍历对象自身的和继承的可枚举的属性。
 * Object.keys()：返回对象自身的所有可枚举的属性的键名。
 * JSON.stringify()：只串行化对象自身的可枚举的属性。
 * Object.getOwnPropertyNames(obj) 数组，对象自身所有属性，有不可枚举，无symbol
 * Object.getOwnPropertySymbols(obj)
 * Reflect.ownKeys(obj) 键名+不可枚举+Symbol
 * Object.assign()： 忽略enumerable为false的属性，只拷贝对象自身的可枚举的属性。
 * Object.getOwnPropertyDescriptors() 自身属性非继承属性
## 对象转二维数组
```js
const a = new Array();const b = Reflect.ownKeys(msg);for(let i = 0;i<b.length;i++){const c=new Array();c[0]=b[i];c[1]=msg[b[i]];a.push(c)}
var obj2arr=funtion(obj){
  const a = new Array();
  const b = Reflect.ownKeys(obj);
  for(let i = 0;i<b.length;i++){
    const c=new Array();
    c[0]=b[i];
    c[1]=obj[b[i]];
    a.push(c)
  }
  return a
}
```

```js
function entries(obj) {
  let arr = [];
  for (let key of Object.keys(obj)) {
    arr.push([key, obj[key]]);
  }
  return arr;
}
```
##  上面一行代码相当于  Object.entries(msg),忽略Symbol
* Object.keys(msg)
* Object.values()
```js
let obj = { one: 1, two: 2 };
for (let [k, v] of Object.entries(obj)) {
  console.log(
    `${JSON.stringify(k)}: ${JSON.stringify(v)}`
  );
}
```
```js
const map = new Map(Object.entries(obj));
```
```js 数组变对象

function* entries(obj) {
  for (let key of Object.keys(obj)) {
    yield [key, obj[key]];
  }
}
```
## JSON函数
 * JSON.stringify()
 * JSON.parse()
 * json的key必须是有 _""_
