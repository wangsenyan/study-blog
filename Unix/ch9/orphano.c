#include "apue.h"
#include <errno.h>

static void sig_hup(int signo)
{
  printf("SIGHUP received, pid = %ld\n", (long)getpid());
}

// void (*signal(int isgno, void (*func)(int)))(int);
int main(void)
{
  char c;
  pid_t pid, sid;
  pr_ids("parent");
  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid > 0)
    sleep(5);
  else
  {
    if ((sid = setsid()) < 0)
      err_sys("setsid error");
    else
      pr_ids("child"); //tpgrp=-1 不再拥有终端
    //signal(SIGHUP, sig_hup); //非阻塞
    //kill(getpid(), SIGTSTP); //使进程暂停,SIGCONT重新激活
    //pr_ids("child");
    // if (read(STDIN_FILENO, &c, 1) != 1)
    //   printf("read error %d on controlling TTY\n", errno);
  }
  exit(0); //父进程终止后，子进程成为孤儿进程组，要求向孤儿进程组每个进程发送SIGHUP,后SIGCONT
}