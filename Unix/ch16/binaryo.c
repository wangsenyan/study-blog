#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>

int main(void)
{
  uint32_t i = 0x04030201; //在栈上，栈顶地址最大，看栈顶是什么？
  unsigned char *cp = (unsigned char *)&i;
  if (*cp == 1)
    printf("little-endian\n");
  else if (*cp == 4)
    printf("big-endian\n");
  else
    printf("who kowns?\n");
  exit(0);
}