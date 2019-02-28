#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
//#include <limits.h>
#include <float.h>
#define N 8
int main(void)
{

  return 0;
}

int **square_matrix_multiply_recursive(int **a, int **b, int n)
{
  if (n < 2)
  {
    //计算
  }
  else
  {
    //分割
    int **p = a;
    int **q = b;
    square_matrix_multiply_recursive(a, b, n / 2);
  }
}
//remember to free