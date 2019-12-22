//只在两个相关的进程间起作用，都需要同步访问
//gcc devnull_posix_sem.c apue.c -o devnull_posix_sem -lpthread
#include "apue.h"
#include <fcntl.h>
#include <semaphore.h>
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
  sem_t *semidp, *semidc;
  void *area;
  //if ((semid = shmget(888, sizeof(long), IPC_CREAT | IPC_EXCL)) < 0)
  if ((fd = open("/dev/zero", O_RDWR)) < 0) //接收并忽略所有信息
     err_sys("open error");
  if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, fd, 0)) == MAP_FAILED)
    err_sys("mmap error");
  close(fd);

  if ((semidp = sem_open("parent", O_CREAT | O_EXCL, 0400, 0)) < 0)
    err_sys("sem_open parent error");
  if ((semidc = sem_open("child", O_CREAT | O_EXCL, 0400, 0)) < 0)
    err_sys("sem_open child error");

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid > 0)
  {
    for (i = 0; i < NLOOPS; i += 2)
    {
      if ((counter = update((long *)area)) != i)
        err_quit("parent: expected %d,got %d", i, counter);
      printf("parent: %d %d\n", i, counter);
      sem_post(semidc); //传给子进程;
      sem_wait(semidp); //等待子进程;
    }
    sem_destroy(semidp);
  }
  else
  {
    for (i = 1; i < NLOOPS + 1; i += 2)
    {
      sem_wait(semidc); //等待父进程
      if ((counter = update((long *)area)) != i)
        err_quit("child: expected %d,got %d", i, counter);
      printf("child: %d %d\n", i, counter);
      sem_post(semidp); //传给父进程
    }
    sem_destroy(semidc);
  }
  exit(0);
}