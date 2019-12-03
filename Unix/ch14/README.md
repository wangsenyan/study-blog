## <center>高级I/O</center>

### 非阻塞I/O
* open O_NONBLOCK
* fcntl O_NONBLOCK

* 终端驱动程序一次能接受的数据量随系统而变

### 记录锁

```c
#include<fcntl.h>
struct flock {
  short l_type;   /* F_RDLCK, F_WRLCK, F_UNLCK */
  short l_whence; /* SEEK_SET, SEEK_CUR, SEEK_END */
  off_t l_start;  /* offset in bytes,relation to l_whence * /
  off_t l_len;    /* length,in bytes;0 means lock to EOF */
  pid_t pid;      /* returned with F_GETLK */
}
int fcntl(int fd,int cmd,.../* struct flock *flockptr */);
//返回值：成功 依赖cmd，否则 -1
```
* 如果一个进程对同一个文件区已经有了一把锁，后来该进程又企图在同一文件区间再加一把锁，那么新锁会替换已有锁
* 加读锁，必须读打开；加写锁，必须写打开
* F_GETLK 判断由flockptr所描述的锁是否被另一把锁排斥(阻塞)。如果存在一把锁，阻止创建由flockptr所描述的锁，现有锁的信息重写flockptr指向的信息

* 锁的作用是阻止多个进程同时写同一个文件

* 锁的隐含继承和释放
  1. 锁与进程和文件两者关联
    - 当一个进程终止时，它所建立的锁全部释放
    - 描述符关闭，该进程通过这一描述符引用的文件上的任何一把锁都会释放(该进程的锁)
  
  2. 由fork产生的子进程不继承父进程设置的锁
  3. 在执行exec后，新程序可以继承原执行程序的锁

>FreeBSD实现
```c
fd1 = open(pathname,...);
write_lock(fd1,0,SEEK_SET,1);
if((pid=fork())>0)
{
   fd2=dup(fd1);
   fd3=open(pathname,...);
}else if(pid==0)
{
  read_lock(fd1,1,SEEK_SET,1);
}
pause();
```
![lockf](../../image/lockf.png)

* 建议性锁和强制性锁
 - 强制性锁：打开其设置组ID位，关闭其组执行位便开启 对该文件的强制性锁机制  
   `chmod(filename,(stat.st_mode & ~S_IXGRP | S_ISGID))`
 - 强制性锁会让内核检查每一个open,read和write,验证调用过程是否违背了正在访问的文件上的某一把锁

![enforce_lock](../../image/enforce_lock.png)

[example](enforcelocko.c)

### I/O多路转接(多路复用) 
[网络编程](../../tcp-ip/unix网络编程卷1/ch6.md)
[example](../../tcp-ip/server1.c)

* poll pselect select
* 如果碰到文件尾端，则select会认为该描述符是可读的，然后调用read，它返回0
* pselect 与select 区别
  1. 超时值 
    - select 用  timeval 秒和微秒 
    - pselect 用 timespec 秒和纳秒
  2. 超时值
    - pselect const 保证不会改变此值
  3. pselect 可选信号屏蔽值，sigmask==NULL ，同select同，在调用pselect时，以原子操作安装信号屏蔽字，返回时，恢复以前的信号屏蔽字
* poll 
  - nfds指定fdarray数组中的元素数
  - events成员我们设置
  - revents成员由内核设置
  - POLLHUP挂断后，就不能再写该描述符，但有可能仍可读取到数据
  - timeout
    - -1 永远等待 INFTIM,或捕捉到信号返回 -1 EINTY
    - 0 不等待
    - ＞0 等待timeout毫秒
  - 一个描述符是否阻塞不会影响poll是否阻塞
```c
#include<sys/select.h>
int select(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds, struct timeval *restrict tvptr);
//返回：准备就绪的描述符数目，超时，返回0 出错 -1

int pselect(int maxfdp1,fd_set *restrict readfds,fd_set *restrict writefds,fd_set *restrict exceptfds,const struct timespec *restrict tsptr,const sigset_t *restrict sigmask);
//返回：准备就绪的描述符数目，超时，返回0 出错 -1

#include <poll.h>
struct pollfd {
  int fd;
  short events;
  short revents;
}
int poll(struct pollfd fdarray[],nfds_t nfds,int timeout);
//返回：准备就绪的描述符数目，超时，返回0，出错 -1
```

![poolfd](../../image/pollfd.png)

### 异步I/O

* sigevent
  - sigev_notify
    - SIGEV_NONE  异步完成后不通知进程
    - SIGEV_SIGNAL 异步完成后，产生由sigev_signo字段指定的信号
    - SIGEV_TRHEAD 当异步I/O请求完成时，该结构的sigev_notify_function字段指定的函数被调用，sigev_value为参数

* aio_fsync
  - op 
    - O_DSYNC  fdatasync [ch3](../ch3/README.md)
    - O_SYNC   fsync
* aio_return 每个异步操作只调用一次aio_return,一旦调用，可以释放掉包含I/O操作返回值的记录
```c
#include<aio.h>
struct aiocb{
  int                  aio_fildes;          /* file descriptor */
  off_t                aio_offset;          /* file offset for I/O */
  volatile    void     *aio_buf;            /* buffer for I/O */
  size_t               aio_nbytes;          /* number of bytes to transfer */
  int                  aio_reqprio;         /* priority */
  struct sigevent      aio_sigevent;        /* signal information */
  int                  aio_lio_opcode;      /* operation for list I/O */
};

struct sigevent {
  int                  sigev_notify;            /* notify type */
  int                  sigev_signo;             /* signal number */
  union sigval         sigev_value;             /* notify argument */
  void (*sigev_notify_function)(union sigval);  /* notify function */
  pthread_attr_t       *sigev_notify_attributes;/* notify attrs */
}

int aio_read(struct aiocb *aiocb); //进行异步读操作
int aio_write(struct aiocb *aiocb);//进行异步写操作
int aio_fsync(int op,struct aiocb *aiocb); //强制所有等待中的异步操作不等待而写入持久化的存储中
//返回：成功 0 出错 -1 或其他errno
int aio_error(const struct aiocb *aiocb);
//返回：0 成功，-1 或其他errno 失败 EINPROGRESS 异步读写或同步操作仍在等待

ssize_t aio_return(const struct aiocb *aiocb);
//返回：本身失败 -1 其他 read write fsync可能返回的值
int aio_suspend(const struct aiocb *const list[],int nent,const struct timespec *timeout);
//返回：成功0 出错 -1
int aio_cancel(int fd,struct aiocb *aiocb);
//返回：失败 -1   
// AIO_ALLDONE 所有操作在尝试取消前已经完成
// AIO_CANCELED 所有的操作已取消
// AIO_NOTCANCELED 至少一个要求的操作没有被取消

int lio_listio(int mode,struct aiocb *restrict const list[restrict],int nent,struct sigevent *restrict sigev);
//返回：成功 0 出错 -1
```

![aio](../../image/aio.png)
[example](rot13o.c)