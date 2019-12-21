////不会做 只在两个相关的进程间起作用，都需要同步访问
#include "apue.h"
#include <fcntl.h>
#include <sys/mman.h>

#define NLOOPS 1000
#define SIZE sizeof(long)

static int update(long *ptr)
{
  return ((*ptr)++);
}

int main(int argc, char *argv[])
{
  int fd, fdL, i, counter;
  pid_t pid;
  void *area;

  if (argc != 2)
  {
    fprintf(stderr, "usage: %s filename \n", argv[0]);
    exit(1);
  }
  //建议性记录锁
  if ((fdL = open(argv[1], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0)
    err_sys("open error");
  if (write(fdL, "ab", 2) != 2)
    err_sys("write error");
  //共享内存映射
  if ((fd = open("/dev/zero", O_RDWR)) < 0) //接收并忽略所有信息
    err_sys("open error");
  if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, fd, 0)) == MAP_FAILED)
    // if ((area = mmap(0, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0)) == MAP_FAILED)
    err_sys("mmap error");
  close(fd);

  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid > 0)
  {
    for (i = 0; i < NLOOPS; i += 2)
    {
      if (write_lock(fdL, 1, SEEK_SET, 2) < 0)
        err_sys("parent: lock error"); //先锁住子锁
      if (write_lock(fdL, 0, SEEK_SET, 1) != -1)
      {
        if ((counter = update((long *)area)) != i)
          err_quit("parent: expected %d,got %d", i, counter);
        if (un_lock(fdL, 1, SEEK_SET, 2) < 0)
          err_sys("parent: unlock error");
      }
    }
  }
  else
  {
    for (i = 1; i < NLOOPS + 1; i += 2)
    {
      if (write_lock(fdL, 1, SEEK_SET, 2) != -1)
      {
        if ((counter = update((long *)area)) != i)
          err_quit("child: expected %d,got %d", i, counter);
        if (un_lock(fdL, 0, SEEK_SET, 1) < 0)
          err_sys("child: unlock error");
      }
    }
  }
  exit(0);
}