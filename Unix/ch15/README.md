## <center>进程间通信</center>

![ipc](../../image/ipc.png)

### 管道
* 管道只能在具有公共祖先的两个进程之间使用
* pathconf 或 fpathconf 函数可以确定PIPE_BUF的值
* 若pclose的调用者已经为信号SIGCHLD设置了一个信号处理程序，则pclose中的watipid调用将返回一个EINTR
* popen决不应由设置用户ID或设置组ID程序调用，防止越权

![popen](../../image/popen.png)

### 协同进程
* 当一个过滤程序即产生某个过滤程序的输入，又读取该过滤程序的输出时，它就变成了协同进程
[example](xietong.c)

### FIFO
* 命名管道
* 不相关的进程也能交换数据
* [mode](../ch3/README.md#open)
* 当open一个FIFO时，非阻塞标志(O_NONBLOCK)会有：
  - 没指定O_NONBLOCK，只读open要阻塞到某个其他进程为写而打开这个FIFO为止，只写open要阻塞到某个其他进程为读而打开这个FIFO为止
  - 指定了O_NONBLOCK，只读open立即返回，只写可能会返回-1，errno=ENXIO
* write一个尚无进程为读而打开的FIFO，产生信号SIGPIPE
* 用途：
  - shell命令使用FIFO将数据从一条管道传送到另一条，无需创建临时文件
  - 客户-服务进程应用程序中FIFO用作汇聚点
```c
#include <sys/stat.h>
int mkfifo(const char *path,mode_t mode);
int mkfifoat(int fd,const char *path,mode_t make);
//返回：成功，0 失败 -1
```

```sh

```