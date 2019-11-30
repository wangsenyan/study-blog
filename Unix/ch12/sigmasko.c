#include "apue.h"
#include <pthread.h>

int quitflag;
sigset_t mask;

pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t waitlock = PTHREAD_COND_INITIALIZER;

void *thr_fn(void *arg)
{
  int err, signo;
  for (;;)
  {
    //printf("before sigwait ? %lu\n", (unsigned long)pthread_self());
    err = sigwait(&mask, &signo);
    if (err != 0)
      err_exit(err, "signal failed");
    switch (signo)
    {
    case SIGINT:
      printf("\ninterrupt\n");
      break;
    case SIGQUIT:
      pthread_mutex_lock(&lock);
      quitflag = 1;
      pthread_mutex_unlock(&lock);
      //printf("before ? %lu\n", (unsigned long)pthread_self());
      pthread_cond_signal(&waitlock);
      //printf("end ? %lu\n", (unsigned long)pthread_self());
      return (0);
    default:
      printf("unexpected signal %d\n", signo);
      exit(1);
    }
  }
}

int main(void)
{
  int err;
  sigset_t oldmask;
  pthread_t tid;
  sigemptyset(&mask);
  sigaddset(&mask, SIGINT);
  sigaddset(&mask, SIGQUIT);
  if ((err = pthread_sigmask(SIG_BLOCK, &mask, &oldmask)) != 0)
    err_exit(err, "SIG_BLOCK error");

  err = pthread_create(&tid, NULL, thr_fn, 0);
  if (err != 0)
    err_exit(err, "can't create thread");

  pthread_mutex_lock(&lock);
  while (quitflag == 0)
  {
    pthread_cond_wait(&waitlock, &lock);
    //printf("father ? %lu\n", (unsigned long)pthread_self());
  }
  pthread_mutex_unlock(&lock);

  quitflag = 0;
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
  sleep(1);
  exit(0);
}