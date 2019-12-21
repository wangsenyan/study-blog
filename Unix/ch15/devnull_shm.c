//只在两个相关的进程间起作用，都需要同步访问
#include "apue.h"
#include <fcntl.h>
#include <sys/shm.h>

#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(long *ptr)
{
  return ((*ptr)++);
}

int main(void)
{
  int i, counter;
  pid_t pid;
  int shmid;
  //if ((shmid = shmget(888, sizeof(long), IPC_CREAT | IPC_EXCL)) < 0)
  if ((shmid = shmget(888, sizeof(long), IPC_CREAT)) < 0)
    err_sys("shmget error");
  TELL_WAIT();
  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid > 0)
  {
    char *pptr;
    pptr = shmat(shmid, 0, 0);
    for (i = 0; i < NLOOPS; i += 2)
    {
      if ((counter = update((long *)pptr)) != i)
        err_quit("parent: expected %d,got %d", i, counter);
      printf("parent: %d %d\n", i, counter);
      TELL_CHILD(pid);
      WAIT_CHILD();
    }
  }
  else
  {
    char *cptr;
    cptr = shmat(shmid, 0, 0);
    for (i = 1; i < NLOOPS + 1; i += 2)
    {
      WAIT_PARENT();
      if ((counter = update((long *)cptr)) != i)
        err_quit("child:expected %d,got %d", i, counter);
      printf("child: %d %d\n", i, counter);
      TELL_PARENT(getppid());
    }
  }
  exit(0);
}