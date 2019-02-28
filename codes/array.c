#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
int main()
{

  int a[3][3] = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
  int(*ptr)[3] = a;
  for (int j = 0; j < 3; j++)
    for (int i = 0; i < 3; i++)
      printf("%d\t", *(*(ptr + j) + i));
}