//gcc -pthread pthreado.c apue.c -o pthreado #pthread_t是结构
//gcc  pthreado.c apue.c -o pthreado -lpthread    #pthread_t是长整型
#include "apue.h"
#include <pthread.h>
pthread_t ntid;

void printids(const char *s)
{
  pid_t pid;
  pthread_t tid;
  pid = getpid();
  tid = pthread_self();
  printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *thr_fn(void *arg)
{
  printids("new thread: ");
  return ((void *)0);
}

void *thr_fn1(void *arg)
{
  printf("thread 1 returning\n");
  return ((void *)1);
}

void *thr_fn2(void *arg)
{
  printf("thread 2 returning\n");
  return ((void *)2);
}

// int main(void)
// {
//   int err;
//   err = pthread_create(&ntid, NULL, thr_fn, NULL);
//   if (err != 0)
//     err_exit(err, "cant create thread");
//   printids("main thread: ");
//   sleep(1);
//   exit(0);
// }

int main(void)
{
  int err;
  pthread_t tid1, tid2;
  void *tret;
  err = pthread_create(&tid1, NULL, thr_fn1, NULL);
  if (err != 0)
    err_exit(err, "can't create thread 1");
  err = pthread_create(&tid2, NULL, thr_fn2, NULL);
  if (err != 0)
    err_exit(err, "cant create thread 2");
  err = pthread_join(tid1, &tret);
  if (err != 0)
    err_exit(err, "cant join with thread 1");
  printf("thread 1 exit code %ld\n", (long)tret);
  err = pthread_join(tid2, &tret);
  if (err != 0)
    err_exit(err, "cant join with thread 1");
  printf("thread 2 exit code %ld\n", (long)tret);
  exit(0);
}