#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
int main()
{
  static int j = 0;
  int i;
  for (i = 0; i < 4; i++)
    fork();
  j++;
  printf("%d \n", j);
  return 0;
}