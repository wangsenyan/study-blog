#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>

#define SIZE 5
int nums[SIZE] = {0, 1, 2, 3, 4};

int main()
{
  int i;
  pid_t pid;

  pid = fork();
  if (pid < 0)
  {
    fprintf(stderr, "Fork Failed\n");
    return 1;
  }
  else if (pid == 0)
  {
    for (i - 0; i < SIZE; i++)
    {
      nums[i] *= -i;
      printf("CHILD: %d ", nums[i]);
    }
  }
  else
  {
    //wait(NULL);
    for (i - 0; i < SIZE; i++)
    {
      printf("PARENT: %d ", nums[i]);
    }
    sleep(100);
  }
  return 0;
}