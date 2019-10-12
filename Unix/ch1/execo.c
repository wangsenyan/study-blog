#include "apue.h"
#include <sys/wait.h>

static void sig_int(int);
int main(void)
{
  char buf[MAXLINE];
  pid_t pid;
  int status;
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal error");
  printf("%% ");
  while (fgets(buf, MAXLINE, stdin) != NULL)
  {
    if (buf[strlen(buf) - 1] == '\n')
      buf[strlen(buf) - 1] = 0;
    if ((pid = fork()) < 0)
    {
      err_sys("fork error");
    }
    else if (pid == 0)
    {
      execlp(buf, buf, (char *)0); //execlp 函数要求的参数是以null结束而不是换行符结束的
      err_ret("couldn't excute: %s", buf);
      exit(127);
    }
    if ((pid = waitpid(pid, &status, 0)) < 0)
      err_sys("waitpid error");
    printf("%% ");
  }
  exit(0);
}

void sig_int(int signo)
{
  printf("interrupt\n%% ");
}