#include <sys/wait.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>

#include <sys/acct.h>
int main(int argc, char *argv[])
{
  pid_t pid;
  int status;
  // int i;
  // for (i = 0; i < argc; i++)
  //   printf("argv[%d]: %s\n", i, argv[i]);
  if (argc < 2)
    return 1;
  else
  {
    if ((pid = fork()) < 0)
      status = -1;
    else if (pid == 0)
    {
      printf("this is child %s", argv[1]);
      execl("/bin/sh", "sh", "-c", argv[1], (char *)0);
      _exit(127);
    }
    else
    {
      while (waitpid(pid, &status, 0) < 0)
      {
        if (errno != EINTR)
        {
          status = -1;
          break;
        }
      }
    }
    return status;
  }
}