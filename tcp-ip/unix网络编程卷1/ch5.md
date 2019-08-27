## <center>TCP客户/服务器程序示例</center>

### 代码

[server.c](../server.c)

[client.c](../client.c)

### POSIX信号处理
* sigaction函数
* SIGCHLD 信号就是由内核在任何一个进程终止时发送给它的父进程的一个信号
* SIGKILL,SIGSTOP 不能被捕获,也不能被忽略-SIG_IGN
* 信号捕获函数
  - 单一整数调用
  - 没有返回值
  - 原型 `void handler(int signo)`
* POSIX保证被捕获的信号在其信号处理函数运行期间总是阻塞的

### wait 与 waitpid 函数