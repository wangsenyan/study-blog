## 基础类型
 
  ### 元祖Tuple
  ```ts
  e.g let x:[string,number]
  ```
  ### 联合类型
  ### 枚举 enum
  ```ts
  enum Clolor {Red=1,Green,Blue}
  ```
  ### any
  ### void
    无任何类型，比如函数没返回值
    声明一个void六类型变量只能为它赋予undifined和null，**默认情况下null和undefined是所有类型的子类型。 就是说你可以把 null和undefined赋值给number类型的变量，当你指定了--strictNullChecks标记，null和undefined只能赋值给void和它们各自。**
  ```ts
  function warnUser():void{
    alert("This is my warning message")
  }
  let nuusable:void = undefined
  ```
   ### never
   用不存在的值的类型，总会抛出错误或根本不会有返回值，是任何类型的子类型
   ```ts
    function error(message: string): never {
        throw new Error(message);
    }
   ```
  ### 类型断言
   * 尖括号法
   ```ts
   let strLength: number = (<string>someValue).length;
   ```
   * as语法
   ```ts
   let strLength: number = (someValue as string).length;
   ```
## 接口
  **TypeScript核心原则之一，对值所具有的结构进行类型检查**  __鸭式辨型法__ 或 __结构性子类型化__
  接口的作用就是为这些类型命名和为你的代码或第三方代码定义契约
  ```ts
  interface LabelledValue{
    lebel:string;
  }

  function printLabel(labelledObj:LabelledValue){
    console.log(labelledObj.label)
  }

  let myObj = {size:10,label:"Size 10 Object"};
  printLabel(myObj);
  ```
  ### 可选属性
   ```ts
   interface SquareConfig{
     color?:string;
     width?:number;
   }
   function cS(config:SquareConfig):{c:string;a:number}{
     return {c:' is string ';a:12}
   }
   //捕获未定义属性变量错误更方便
   ```
  ### 只读属性
   赋值好后不能更改
   readonly 只作为属性
   const 只作为变量
   对象字面量存在任何“目标类型”不包含的属性时，会得到一个错误
   ```ts
   interface Point{
     readonly x:number;
     readonly y:number;
     let ro: ReadonlyArray<number> = [1,3,4,5]
   }
   ```
  ### 索引签名
   ```ts
   interface SC {
     color?:string;
     width:?number;
     [propName:string]:any;
   }
   ```
   绕过检查的方法
     * { colour: "red", width: 100 } as S -  用as
     * let other = { colour: "red", width: 100 } - 赋值后使用
     * 字符索引签名 【propName:string】:any
  ### 函数类型
   ```ts
   interface SF{
     (source:string,subString:string):boolean;
   }
   let mS:SF;
   mS = function(src:string,sub:string):boolean{
     //
   }
   
   let mF:SF;
   mF = function(arc,sub){
     //自动检查类型，且变量名可以不与定义一致
   }
   ```
  ### 可索引的类型
   类似函数类型，可描述能够"通过索引得到的类型"
   两种索引签名：字符串和数字
   可以同时使用两种类型的索引，但是数字索引的返回值必须是字符串索引返回值类型的子类型
   这是因为当使用 number来索引时，JavaScript会将它转换成string然后再去索引对象。
  ```ts
   interface SA{
     [index:number]:string;
   }
   let mArray:SA;
   mArray = ["Bob","Fred"];
   let myStr:string = mArray[0];
   interface ReadonlyStringArray {
    readonly [index: number]: string;
    }
   let myArray: ReadonlyStringArray = ["Alice", "Bob"];
   myArray[2] = "Mallory"; // error!
    //很奇怪
    interface StringArray {
      [index:number]:string;
      [propName:string]:string;
    }
    let myArray :StringArray ={"name":"big"} 
   ```
  ### 强制类型 `implements`
  ### 类类型
   * 接口描述公共部分，不会帮你检查类是否具有某些私有成员
   ```ts
    interface CInterface{
      currentTime:Date;
      setTime(d:Date);
    }
    class Clock implements CInterface{
      currentTime:Date;
      setTime(d:Date){
        this.currentTime = d;
      }
      constructor(h: number, m: number) { }
    }
   ```
   * 类静态部分与实例部分的区别
   ```ts
    interface ClockConstructor {
    new (hour: number, minute: number): ClockInterface;
    }
    interface ClockInterface {
        tick();
    }

    function createClock(ctor: ClockConstructor, hour: number, minute: number): ClockInterface {
        return new ctor(hour, minute);
    }

    class DigitalClock implements ClockInterface {
        constructor(h: number, m: number) { }
        tick() {
            console.log("beep beep");
        }
    }
    class AnalogClock implements ClockInterface {
        constructor(h: number, m: number) { }
        tick() {
            console.log("tick tock");
        }
    }

    let digital = createClock(DigitalClock, 12, 17);
    let analog = createClock(AnalogClock, 7, 32);
   ```
  ### 继承接口
   ```ts
   interface P{}
   interface S extends P{}
   ```
  ### 混合类型
   ```ts
    interface Counter {
    (start: number): string;
    interval: number;
    reset(): void;
    }

    function getCounter(): Counter {
        let counter = <Counter>function (start: number) { };
        counter.interval = 123;
        counter.reset = function () { };
        return counter;
    }

    let c = getCounter();
    c(10);
    c.reset();
    c.interval = 5.0;
   ```
   ### 接口继承类
    ```ts
     class Control {
    private state: any;
    }

    interface SelectableControl extends Control {
        select(): void;
    }

    class Button extends Control implements SelectableControl {
        select() { }
    }

    class TextBox extends Control {
        select() { }
    }

    // 错误：“Image”类型缺少“state”属性。
    class Image implements SelectableControl {
        select() { }
    }

    class Location {

    }
    ```
    当接口继承了一个类类型时，它会继承类的成员但不包括其实现。 就好像接口声明了所有类中存在的成员，但并没有提供具体实现一样。 接口同样会继承到类的private和protected成员。 这意味着当你创建了一个接口继承了一个拥有私有或受保护的成员的类时，这个接口类型只能被这个类或其子类所实现（implement）
## 类
  ### 基本概念
   * 子类 - 派生类
   * 超类 - 基类
   * 派生类包含一个构造函数，必须调用super()
   * public 指定成员是可见的，默认
   * private 不能在声明它的类的外部访问
   * 类似于private,但是改成员在派生类中任然可以访问
  ### 成员类型
   如果其中一个类型里包含一个private成员，那么只有当另外一个类型中也存在这样一个 private成员， 并且它们都是来自同一处声明时，我们才认为这两个类型是兼容的
   ```ts 
   class Animal {
    private name: string;
    constructor(theName: string) { this.name = theName; }
   }
    
    class Rhino extends Animal {
    constructor() { super("Rhino"); }
    } 
    
    class Employee {
    private name: string;
    constructor(theName: string) { this.name = theName; }
    }
    let animal = new Animal("Goat");
    let rhino = new Rhino();
    let employee = new Employee("Bob");

    animal = rhino ; //可以
    animal = employee; //错误: Animal 与 Employee 不兼容.
   ```
## 装饰器
  ###
    启用必须在tsconfig.json里启用experimentalDecorators
    ```sh
      tsc --target ES5 --experimentalDecorators
    ```
    ```json tsconfig.json
      {
        "compilerOptions": {
          "target": "ES5",
          "experimentalDecorators": true
        }
      }
    ```
  ### 装饰器
   * 是一种特殊类型的声明，它能够被附加到类声明。方法，访问符，属性或参数上
   * @expression
  ### 装饰器工厂
   ```ts
    function color(value:string){
      return function (target){
        //do something with "target" and "value"...
      }
    }
   ```
  ### 装饰器组合
   * 书写在一行
    ```ts
     @f @g x
    ```
   * 书写在多行
    ```ts
    @f
    @g
    x
    ```
   * 符合函数
    (f。g)(x) 等同 f(g(x))
   * 声明文件(.d.ts)
   * 类装饰器在类声明之前被声明。类装饰器应用于类构造函数，可以用来监视，修改或替换类定义。 类装饰器不能用在声明文件中( .d.ts)，也不能用在任何外部上下文中（比如declare的类）
   * 类装饰器表达式在运行时当做函数被调用，类的构造函数作为其唯一的参数
