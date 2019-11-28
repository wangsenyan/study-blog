## <center>线程属性</center>

### 线程属性
* detachstate
  -  PTHREAD_CREATE_DETACHED 以分离状态启动线程
  -  PTHREAD_CREATE_JOINABLE 正常启动线程

* 线程栈 getstack setstack
- 编译阶段 _POSIX_THREAD_ATTR_STACKADDR 和 _POSIX_THREAD_ATTR_STACKSIZE 
- 运行阶段 _SC_THREAD_ATTR_STACKADDR 和  _SC_THREAD_ATTR_STACKSIZE  ->sysconf
- stackaddr线程属性被定义为栈的最低内存空间，通过malloc或mmap分配的地址
- setstacksize 选择的stacksize不能小于 PTHREAD_STACK_MIN
- guardsize控制线程栈末尾之后用以避免溢出的扩展内存大小，如果设置stackaddr则guardsize默认为0
```c
#include<pthread.h>
int pthread_attr_init(pthread_attr_t *attr);
int pthread_attr_destroy(pthread_attr_t *attr);

int pthread_attr_getdetachstate(const pthread_attr_t *restrict attr,int *detachstate);
int pthread_attr_setdetachstate(pthread_attr_t *attr,int *detachstate);

//设置线程栈地址
int pthread_attr_getstack(const pthread_attr_t *restrict attr,void **restrict stackaddr,size_t *restrict stacksize);
int pthread_attr_setstack(pthread_attr_t *attr,void *stackaddr,size_t stacksize);

//设置线程属性stacksize,希望改变栈的默认大小但又不想自己处理线程栈的分配问题
int pthread_attr_getstacksize(const pthread_attr_t *restrict attr,size_t *restrict stacksize);
int pthread_attr_setstacksize(pthread_attr_t *attr,size_t stacksize);

//设置线程栈
int pthread_attr_getguardsize(const pthread_attr_t *restrict attr,size_t *restrict guardsize);
int pthread_attr_setguardsize(pthread_attr_t *attr,size_t guardsize);
//返回：成功 0 ，否则 错误编号
```
### 同步属性
* 互斥量属性 pthread_mutexattr_t 
* 3个属性
  - 进程共享属性 PTHREAD_PROCESS_PRIVATE  PTHREAD_PROCESS_SHARED
  - 健壮属性 PTHREAD_MUTEX_STALLED PTHREAD_MUTEX_ROBUST
  - 类型属性
```c
#include <pthread.h>

//默认
pthread_mutex_t lock =PTHREAD_MUETX_INITIALIZER;
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
//非默认属性
int pthread_mutexattr_init(pthread_mutexattr_t *attr);
int pthread_mutexattr_destroy(pthread_mutexattr_t *attr);

//返回：成功 0 失败 错误编号
```