## <center>进程间通信</center>

![ipc](../../image/ipc.png)

### 管道
* 管道只能在具有公共祖先的两个进程之间使用
* pathconf 或 fpathconf 函数可以确定PIPE_BUF的值