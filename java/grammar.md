## <center>Grammar</center>
### java对象和类
* 一个源文件只能有一个public类
* 一个源文件可以有多个非public类
* 源文件名和public类名保持一致
* 如果一个类定义在某个包，那么package语句应该放在源文件的首行  
  eg: `package cn.com.xiaoyaoji.controller`
* 有import语句，放在package和类定义之间
* import和package语句对源文件中定义的所有类都有效。在同一源文件中国，不能给不同类不同的包声明
* 程序都是从main方法开始执行的，必须包含main方法并且创建一个实例对象
* 下面的命令将会命令编译器载入java_installation/java/io路径下的所有类

```java
import java.io.*;
```
### java数据类型
* 内置数据类型(SIZE,MIN_VALUE,MAX_VALUE) -java.lang.*

|类型|范围|默认值
|-|-|-
|byte|-128~127|0
|short|-2^31~2^31-1|0
|long|-2^63~2^63-1|0L
|float|32位|0.0f
|double|64位|0.0d
|boolean|true/false|false
|char|\u0000~\uffff|

* 引用数据类型 
   1. 类似于指针，引用类型指向一个对象，指向对象的变量时引用变量。一旦声明不能改变
   2. 对象、数组都是引用数据类型
   3. 所有引用类型的默认值都是null
   4. 一个引用变量可以用来引用任何与之兼容的类型
   5. `Site site = new Site("Runnob")`

* java 常量  
  常量在程序运行时不能被修改
  `final double PI = 3.1415926`

* 自动类型转换

  ```
  低 --- > 高
  byte,short,char -> int -> long -> float -> double
  ```

   1. 不能对boolean类型进行类型转换。

   2. 不能把对象类型转换成不相关类的对象。

   3. 在把容量大的类型转换为容量小的类型时必须使用强制类型转换。

   4. 转换过程中可能导致溢出或损失精度

   5. 浮点数到整数的转换是通过舍弃小数得到，而不是四舍五入

### java 变量类型
