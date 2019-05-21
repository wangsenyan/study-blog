## Pthreads同步

```c
#include <pthread.h>
pthread_mutex_t mutex;

pthread_mutex_init(&mutex,NULL);

//acquire return 0 while true
pthread_mutex_lock(&mutex);
//release return 0 while true
pthread_mutex_unlock(&mutex);

```

* 无名信号量
```c
#include <semaphore.h>
sem_t sem;
//信号量的指针   表示共享级别的标志   信号量的初始值
//              0 仅由属于创建信号量的进程线程共享
sem_init(&sem,0,1);

//acquire 
sem_wait(&sem);
//release
sem_post(&sem);
```

* OpenMP
```c
#include <omp.h>
#pragma omp critical //指定后面的代码为临界区
```

