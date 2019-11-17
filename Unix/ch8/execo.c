#include "apue.h"
#include <sys/wait.h>

char *env_init[] = {"USER=unkown", "PATH=/home/unix/", NULL};

int main(void)
{
  pid_t pid;
  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0)
    if (execle("/home/unix/paramo", "paramo", "myarg1", "MY ARG2", (char *)0, env_init) < 0)
      err_sys("execle error");

  if (waitpid(pid, NULL, 0) < 0)
    err_sys("wait error");
  if ((pid = fork()) < 0)
    err_sys("fork error");
  else if (pid == 0)
    if (execlp("./paramo", "paramo", "only 1  arg", (char *)0) < 0)
      err_sys("execlp error");
  exit(0);
}