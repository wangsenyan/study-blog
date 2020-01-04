## <center>高级进程间通信</center>

* unix域套接字
 - 仅仅复制数据
 - 并不执行协议处理
 - 不需要添加或删除网络报头
 - 无需计算校验和
 - 不要产生顺序号
 - 无需发送确认报文

![socketpair](../../image/socketpair.png)

```c
#define offsetof(TYPE,MEMBER)((int)&((TYPE *)0)->MEMBER)

#include <unistd.h>
int getopt(int argc,char *const argv[],const char *options);
extern int optind,opterr,optopt;
extern char *optarg;
```
### 习题
* 17.6 问题
  - 调用stat和调用unlink之间存在竞争
  - 如果名字是一个指向unix域套接字文件的符号链接，那么stat会报告名字是一个套接字,可以用lstat
* 17.7 

```c
//方法一：每一个文件描述符存储在相邻的内存位置
struct msghdr msg;
struct cmshdr *cmptr;
int *ip;
if((cmptr=calloc(1,CMSG_LEN(2*sizeof(int))))==NULL)
  err_sys("calloc error");
msg.msg_control = cmptr;
msg.msg_controllen = CMSG_LEN(2*sizeof(int));
cmptr->cmsg_len = CMSG_LEN(2*sizeof(int));
cmptr->cmsg_level = SOL_SOCKET;
cmptr->cmsg_type = SCM_RIGHTS;
ip = (int *)CMSG_DATA(cmptr);
*ip++=fd1;
ip=fd2;

//方法二
struct msghdr msg;
struct cmsghdr *cmptr;
if((cmptr=calloc(1,2*CMSG_LEN(sizeof(int))))==NULL)
  err_sys("calloc error);
msg.msg_control = cmptr;
msg.msg_controllen = CMSG_LEN(2*sizeof(int));

cmptr->cmsg_len = CMSG_LEN(sizeof(int));
cmptr->cmsg_level = SOL_SOCKET;
cmptr->cmsg_type = SCM_RIGHTS;
*(int *)CMSG_DATA(cmptr) = fd1;
cmptr=CMPTR_NXTHDR(&msg,cmptr);
cmptr->cmsg_len = CMSG_LEN(sizeof(int));
cmptr->cmsg_level = SOL_SOCKET;
cmptr->cmsg_type = SCM_RIGHTS;
*(int *)CMSG_DATA(cmptr) = fd2;
```