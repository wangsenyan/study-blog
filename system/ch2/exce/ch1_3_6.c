#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h> //implicit declaration of function ‘wait’
int main()
{
  pid_t pid;
  pid = fork();
  if (pid < 0)
  {
    fprintf(stderr, "Fork Failed\n");
    return 1;
  }
  else if (pid == 0)
  {
    execlp("/bin/ls", "ls", NULL);
    printf("LINE J\n"); //地址空间被覆盖
  }
  else
  {
    wait(NULL);
    printf("Child Complete!\n");
  }
  return 0;
}