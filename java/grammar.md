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
  **使用前必须声明**
  
```java
  type identifier [ = value][, identifier [= value] ...] ;
```
* 类变量 - 独立于方法之外的变量，用static修饰  

  0. 属于类
  1. 无论创建了多少个对象，类只拥有类变量的一份拷贝。
  2. 存储值静态存储期
  3. 程序开始时创建，程序结束时销毁
  4. 通过 `ClassName.VariableName`的方式访问

* 实例变量 - 独立于方法之外的变量，没有static修饰  

  0. 属于某个对象的属性，必须创建了实例对象，其实例变量才会分配空间
  1. 实例变量具有默认值：0、false、null
  2. public:对之类可见，private:仅在该类可见

* 局部变量 - 类的方法中的变量，声明的时候必须初始化

### Java修饰符

* 访问修饰符  

|修饰符|当前类|同一包内|子孙类|其他包|其他包子孙类|对象
|:-:|:-:|:-:|:-:|:-:|:-:|:-:
|default|Y|Y|N|N|N|类、接口、变量、方法
|public|Y|Y|Y|Y|Y|类、接口、变量、方法
|private|Y|N|N|N|N|变量、方法
|protected|Y|Y|Y|N|Y/N|变量、方法

  * 接口里的变量都隐式声明为 `public static final`,而接口里的方法默认访问权限为public
  * 声明为私有类型的变量只能通过类中的公共的getter方法被外部类访问
  * private访问修饰符的使用主要用来隐藏类的实现细节和保护类的数据
  * 继承：public->public,protected->protected/public,private不继承

* 非访问修饰符

|修饰符|修饰对象|作用|
|-|-|-|
|static|类方法、类变量|静态变量|
|final|类、方法和变量||
|abstract||抽象,将来进行扩充|
|synchronized|||
|transient|||

  * final和static一起使用创建类常量
  * 一个类不能同时被abstract和final修饰，抽象类->抽象方法
  * 抽象方法是一种没有任何实现的方法，该方法的具体实现由子类提供
  * 抽象方法不能被声明为final和static
  * synchronized 同一时间只能被一个线程访问
  * 序列化的对象包含被 transient 修饰的实例变量时，java 虚拟机(JVM)跳过该特定的变量。
  * volatile 修饰的成员变量在每次被线程访问时，都强制从共享内存中重新读取该成员变量的值。而且，当成员变量发生变化时，会强制线程将变化值回写到共享内存