### 调试三部曲

* jps java线程启动信息 

```sh
>java -l  #输出全类名
>java -v  #输出启动时jvm参数
>java -m  #输出传递给java进程main()函数的参数
```

* jstat:虚拟机各种运行状态信息

类信息、内存、垃圾收集、JIT 编译等运行数据

```sh
#jstat -<option> [-t] [-h<lines>]  <vmid>  [<interval> [<count>]]
#        选项        每几行打印标头 进程id    打印间隔    打印次数
# -class 显示ClassLoader相关信息
# -compailer 显示JIT编译的相关信息
# -gc GC相关信息
# -gccapacity 各个代的容量及使用情况
# -gcnew 新生代信息
# -gcnewcapacity 新生代大小与使用情况
# -gcold 老年代和永久代
# -gcoldcapacity 显示老年代的大小
# -gcutil 垃圾收集信息
# -t 程序运行时间
>jstat -gc -h3 31736 1000 10
#https://docs.oracle.com/javase/8/docs/technotes/tools/unix/jstat.html
 S0C    S1C    S0U    S1U      EC       EU        OC         OU       MC     MU    CCSC   CCSU   YGC     YGCT    FGC    FGCT    CGC    CGCT     GCT
19456.0 25088.0 19442.2  0.0   620544.0 364887.6  94208.0    44695.3   69976.0 66183.8 9600.0 8901.3     16    0.170   3      0.239   -          -    0.409
19456.0 25088.0 19442.2  0.0   620544.0 364887.6  94208.0    44695.3   69976.0 66183.8 9600.0 8901.3     16    0.170   3      0.239   -          -    0.409
19456.0 25088.0 19442.2  0.0   620544.0 364887.6  94208.0    44695.3   69976.0 66183.8 9600.0 8901.3     16    0.170   3      0.239   -          -    0.409
```

* jinfo:实时查看和调整虚拟机各项参数
```sh
>jinfo vmid
>jinfo -flag [+|-]name vmid
```

* jmap 

```sh
# XX:+HeapDumpOnOutOfMemoryError 让虚拟机在OOM异常出现之后生成dump文件 kill -3


```

* jhat: 分析dumpheap文件

```sh
#jdk9以后删除
>"C:\Program Files\Java\jdk1.8.0_271\bin\jhat.exe" heap.hprof
```

* jstack: 多有的线程输出

* jconsole:可视化工具

需要添加vm参数

```vm
-Dcom.sun.management.jmxremote
-Dcom.sun.management.jmxremote.port=8011
-Dcom.sun.management.jmxremote.ssl=false
-Dcom.sun.management.jmxremote.authenticate=false
```
```sh

```