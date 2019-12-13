#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <sys/select.h>
void sigint(int signo)
{
  //err_sys("pid=: %ld\n", (long)getpid());
}
// void sigcld(int signo)
// {
//   err_sys("sigcld pid=: %ld\n", (long)getpid());
// }
int main(int argc, char *argv[])
{
  pid_t pid1, pid2, pid3;
  int fd;
  setbuf(stdout, NULL);
  signal_intr(SIGINT, sigint);
  signal(SIGCLD, SIG_IGN);
  if ((fd = open("lockfile", O_RDWR | O_CREAT, 0666)) < 0)
    err_sys("can't open/create lockfile");

  if ((pid1 = fork()) < 0)
    err_sys("fork failed");
  else if (pid1 == 0)
  {
    if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
      err_sys("child 1: can't read-lock file");
    printf("child 1:obtained read lock on file\n");
    pause();
    printf("child 1:exit after pause\n");
    exit(0);
  }
  else
  {
    sleep(2);
  }

  if ((pid2 = fork()) < 0)
    err_sys("fork failed");
  else if (pid2 == 0)
  {
    if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
      err_sys("child 2: can't read-lock file");
    printf("child 2:obtained read lock on file\n");
    pause();
    printf("child 2:exit after pause\n");
    exit(0);
  }
  else
  {
    sleep(2);
  }

  if ((pid3 = fork()) < 0)
    err_sys("fork failed");
  else if (pid3 == 0)
  {
    if (lock_reg(fd, F_SETLK, F_WRLCK, 0, SEEK_SET, 0) < 0)
      //err_sys("child 3: can't set write-lock:%s\n", strerror(errno));
      printf("child 3: can't set write-lock %ld\n", (long)getpid());
    printf("child 3 about to block in write-lock file...\n");
    if (lock_reg(fd, F_SETLKW, F_WRLCK, 0, SEEK_SET, 0) < 0) //阻塞版本加锁
      printf("child 3: can't  write-lock file\n");
    printf("child 3 returned and got write lock????\n");
    pause();
    printf("child 3:exit after pause\n");
    exit(0);
  }
  else
  {
    // signal(SIGCLD, SIG_IGN);
    sleep(2);
  }

  if (lock_reg(fd, F_SETLK, F_RDLCK, 0, SEEK_SET, 0) < 0)
    printf("parent: can't set read lock:%s\n", strerror(errno));
  else
    printf("parent: obtained additional read lock while write lock is pending\n");

  printf("killing child 1...\n");
  kill(pid1, SIGINT);
  printf("killing child 2...\n");
  kill(pid2, SIGINT);
  printf("killing child 3...\n");
  kill(pid3, SIGINT);
  exit(0);
}
