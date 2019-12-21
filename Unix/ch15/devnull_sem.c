//只在两个相关的进程间起作用，都需要同步访问
#include "apue.h"
#include <fcntl.h>
#include <sys/sem.h>
#include <sys/mman.h>
#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(long *ptr)
{
  return ((*ptr)++);
}
union semun {
  int fd, val;
  struct semid_ds *buf;
  unsigned short *array;
};

int main(void)
{
  int fd, i, counter;
  pid_t pid;
  int semid;
  void *area;
  //if ((semid = shmget(888, sizeof(long), IPC_CREAT | IPC_EXCL)) < 0)
  if ((fd = open("/dev/zero", O_RDWR)) < 0) //接收并忽略所有信息
    err_sys("open error");
  if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, fd, 0)) == MAP_FAILED)
    // if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    err_sys("mmap error");
  close(fd);

  if ((semid = semget(888, 1, IPC_CREAT | IPC_EXCL)) < 0)
    err_sys("semget error");

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid > 0)
  {
    union semun smum;
    smum.val = 1;
    for (i = 0; i < NLOOPS;)
    {
      if (semctl(semid, 0, GETVAL) != 0)
        continue;
      if ((counter = update((long *)area)) != i)
        err_quit("parent: expected %d,got %d", i, counter);
      printf("parent: %d %d\n", i, counter);
      if (semctl(semid, 0, SETVAL, smum) < 0)
        err_quit("parent: semctl error");
      i += 2;
    }
  }
  else
  {
    union semun smum;
    smum.val = 0;
    for (i = 1; i < NLOOPS + 1;)
    {
      if (semctl(semid, 0, GETVAL) != 1)
        continue;
      if ((counter = update((long *)area)) != i)
        err_quit("child: expected %d,got %d", i, counter);
      printf("child: %d %d\n", i, counter);
      if (semctl(semid, 0, SETVAL, smum) < 0)
        err_quit("child: semctl error");
      i += 2;
    }
    semctl(semid, 0, IPC_RMID);
  }
  exit(0);
}