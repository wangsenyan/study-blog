1. let 和const
   let 代码块，const 常量，地址不变
   变量声明引用用``反引号 
   ```js
    const a = 'foo'
        const b= `foo${a}` =='foofoo'
        const a= {x:null} 提前声明，否则不能更改属性或使用Object.assign(a,{x:3});

   ```
    _var_ 变量提升 暂时性死区
2. 变量的解构赋值
3. 字符串的扩展  
   0x0000-0xFFFF

   ```js
   s.codePointAt().toString(16)  
   ```
   借助for...of正确识别32位的UTF-16字符
   ```js
   String.fromCodePoint(0x20BB7)
   normalize()  /NFC NFD NFKC NFKD
   string.includes('string1',index)/endsWith()/startsWith()
   string.repeat(number)
   ```
   ${变量} 引用模板字符串用反引号，保留所有反引号内的内容

   ```js
    (x) => x + 6
    //相当于
    function(x){
    return x + 6;
    };
   ```
4. class类
  ```js
   class Point{
   constructor(){}
   }
  ```
  添加类

   ```js
    Object.assign(Point.prototype,{
    toString(){},toValue(){}}
    Object.getOwnPropertyNames(Point.prototype)
   ```
    类必须用new调用，不存在变量提升，定义的时候加（"参数"）立即执行class
    使用proxy可以自动绑定this
   ```js
    class Logger {
      constructor() {
          this.printName = (name = 'there') => {
          this.print(`Hello ${name}`);
          };
     }

  // ...
    }  // Bar类继承Foo类
    class Bar extends Foo {
    }  
   ```
   new是从构造函数生成实例对象的命令
   子类必须在constructor方法中调用super()方法，这是因为子类没有自己的this对象，而是继承父类的this对象，然后对其进行加工。如果不调用super方法，子类就得不到this对象。继承静态方法
  Object.getPrototypeOf() 从子类获取父类
  super()在这里相当于A.prototype.constructor.call(this)

   ```js
   class A{
   constructor(){this.p=2;//父类实例上的方法}
   get m(){}//原型上对象
  }
  ```
  ES6 规定，通过super调用父类的方法时，方法内部的this指向子类
  由于this指向子类，所以如果通过super对某个属性赋值，这时super就是this，赋值的属性会变成子类实例的属性。
  super在静态方法之中指向父类，在普通方法之中指向父类的原型对象。static 方法属于父类而非原型对象
  对象才有方法

  ```js
   // B 的实例继承 A 的实例
  Object.setPrototypeOf(B.prototype, A.prototype);

  // B 继承 A 的静态属性
  Object.setPrototypeOf(B, A);
  // 继承函数
  Object.setPrototypeOf = function (obj, proto) {
  obj.__proto__ = proto;
  return obj;
  }
  ```
作为一个对象，子类（B）的原型（__proto__属性）是父类（A）；作为一个构造函数，子类（B）的原型对象（prototype属性）是父类的原型对象（prototype属性）的实例。

5. promise
   Promise新建后会立即执行
6. 对象

  ```js
   {x,y} ==={x:x,y:y}
   [x] ===x.x
   Object.is(+0,-0) //false  Object.is(NaN,NaN) //ture
   Object.assign() // 可产生枚举的实义属性才会被拷贝，只拷贝源对象的自身属性（不拷贝继承属性），也不拷贝不可枚举的属性（enumerable: false）。
   Object.assign //可以处理数组但是会把数组视为对象，位置为属性
   //ource对象的foo属性是一个取值函数，Object.assign不会复制这个取值函数，只会拿到值以后，将这个值复制过去。
   Object.getPrototypeOf() //方法返回指定对象的原型（内部[[Prototype]]属性的值）。
  //遍历对象的属性
   let obj = { one: 1, two: 2 };
   for (let [k, v] of Object.entries(obj)) {
    console.log(
      `${JSON.stringify(k)}: ${JSON.stringify(v)}`
    );
   }
  ```
  for in 遍历key,for...of 遍历value
7. Symbol 新的原型数据类型  
   Symbol.for("key") Symbol()写法没有登记机制，所以每次调用都会返回一个不同的值。
   Symbol.keyFor方法返回一个已登记的 Symbol 类型值的key
   Symbol.for为 Symbol 值登记的名字，是全局环境的，可以在不同的 iframe 或 - service worker 中取到同一个值
   Symbol.hasInstance
   Symbol.isConcatSpreadable属性等于一个布尔值，表示该对象用于- Array.prototype.concat()时，是否可以展开。
8. async  

  ```js
   function*{  =yield }
   async function = { = await} 
  ```
9. 箭头函数绑定this
10. 如果模块默认输出一个对象，对象名 的首字母应该大写
11. prototype只能被实例访问，但是不可以枚举
   每个函数都包含两个非继承而来的方法：apply()和call()。在特定的作用域中调用函数，等于设置函数体内this对象的值
   对象不需要和方法有任何的耦合关系


### 字符串分隔技术
```js
let a='1234567890';
a.split('').map(Number);
[...a].map(Number);
Array.from(a).map(Number)
//[1,2,3,4,5,6,7,8,9,0];
```