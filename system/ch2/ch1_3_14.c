#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
int main()
{
  pid_t pid;
  pid = fork();
  if (pid < 0)
  {
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0)
  {
    int n;
    printf("enter your n: ");
    scanf("%d", &n);
    while (n != 1)
    {
      if (n % 2 == 0)
        n = n / 2;
      else
        n = 3 * n + 1;
      printf("%d ", n);
    }
    //execlp("bin/ls", "ls", NULL);
  }
  else
  {
    wait(NULL); //一旦父进程调用wait,僵尸进程的进程标识符和它在进程表中的条目就会释放
    //如果没有调用wait，父进程终止，则子进程成为孤儿进程

    printf("Child Complete\n");
  }
  return 0;
}