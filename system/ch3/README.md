### ...
```c
kill(pit_t pid,int signal)
pthread_kill(pthread_t tid,int signal);

//线程撤销
pthread_cancel(tid)
//建立撤销点
pthread_testcancel();
```

### 基本概念
* 线程本地存储(Thread-Local Storage,TLS)   
  类似静态数据但是线程独特的

* 轻量级进程(LightWeight Process,LWP)  
  用户和内核线程之间

* window thread

[pthread](../../image/pthread_w.png)

* linux thread
```c  
clone(CLONE_FS|CLONE_VM|CLONE_SIGHAND|CLONE_FILES) //创建线程
clone()//相当于fork
```

[pthread](../../image/pthread_l.png)

* fork()和clone()区别
  - fork()是父进程的copy
  - clone()根据标志组，指向某些父进程的数据结构