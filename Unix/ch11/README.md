## <center>线程</center>

### 线程函数
* 返回
  - 从例程中返回，返回值是线程的退出码
  - pthread_exit
  - 被同进程其他线程取消

* pthread_cancel并不等待线程终止，它仅仅提出请求
* 线程清理处理程序，记录在栈中，执行顺序和注册时相反
  - 调用pthread_exit
  - 相应取消请求时
  - 用非零execute 参数调用pthread_cleanup_pop

* 线程分离 pthread_detach
  - 线程已经被分离，线程的底层存储资源可以在线程终止时立即被收回
  - 不能用pthread_join函数等待它的终止状态
* 顺序一致：把数据修改操作解释为运行线程的顺序操作步骤
```c
#include <pthread.h>
int pthread_equal(pthread_t tid1,pthread_t tid2);
//返回：相等 非0数值，否则 0
pthread_t pthread_self(void);
//返回：调用线程的线程ID
int pthread_create(pthread_t &tidp,const pthread_attr_t *restrict attr,
                  void *(*start_rtn)(void *),void *restrict arg);
//返回：成功 0 ，失败 错误码                  
void pthread_exit(void *rval_ptr);
int pthread_join(pthread_t thread,void **rval_ptr);//阻塞
//返回：成功，0，否则返回错误编号

void *thr_fn(void *arg)
{
  printids("new thread: ");
  return ((void *)0);
}


int pthread_cancel(pthread_t tid);// pthread_exit(PTHREAD_CANCELED)
//返回：成功 0 否则 错误编码
int pthread_cleanup_push(void (*rtn)(void *),void *arg);
void pthread_cleanup_pop(int execute);

int pthread_detach(pthread_t tid);
//返回：成功，0，失败 错误编码
```

![pthread](../../image/pthread_func.png)

### 互斥量
* 初始化 PTHREAD_MUTEX_INITIALIZER(适用于静态分配的互斥量)
* pthread_mutex_init attr =NULL 初始化默认值
* pthread_mutex_lock 阻塞直到获得锁
* pthread_mutex_trylock 成功 0 ，失败返回 EBUSY
* 死锁必要条件
  - 互斥条件
  - 不剥夺条件 已获得的资源不可被强占
  - 请求和保持条件 至少保持一个资源又提出新的资源请求
  - 循环等待条件
```c
#include <pthread.h>
int pthread_mutex_init(pthread_mutex_t *restrict mutex,const pthread_mutexattr_t *restrict attr);
int pthread_mutex_destroy(pthread_mutex_t *mutex);//删除malloc分配的互斥量
//返回：成功 0 否则 错误编码
int pthread_mutex_lock(pthread_mutex_t *mutex);
int pthread_mutex_trylock(pthread_mutex_t *mutex);
int pthread_mutex_unlock(pthread_mutex_t *mutex);
//返回：成功 0 否则 错误编码
```