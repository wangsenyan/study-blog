//gcc -o ch1_3_15c ch1_3_15c.c -lrt  编程练习3.15
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <sys/wait.h>
int main()
{
  const int SIZE = 8192;
  const char *name = "Collatz";
  int shm_fd;
  int *ptr;
  int n;
  pid_t pid;

  printf("enter n: ");
  scanf("%d", &n);
  shm_fd = shm_open(name, O_CREAT | O_RDWR, 0666);
  ftruncate(shm_fd, SIZE);
  pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "Fork Failed");
    return 1;
  }
  else if (pid == 0)
  {
    ptr = (int *)mmap(0, SIZE, PROT_WRITE, MAP_SHARED, shm_fd, 0);
    int i = 0;
    while (n > 1)
    {
      ptr[i++] = n;
      if (n % 2 == 0)
        n = n / 2;
      else
        n = n * 3 + 1;
    }
    ptr[i] = n;
  }
  else
  {
    wait(NULL);
    ptr = mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);
    int i = 0;
    while (ptr[i] != 1)
    {
      printf("%d ", ptr[i]);
      i++;
    }
    printf("%d\n", ptr[i]);
    shm_unlink(name);
  }
  return 0;
}
