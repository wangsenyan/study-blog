#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
//#include <limits.h>
#include <float.h>
int **matrix(int rows, int cols)
{
  int **p1 = (int **)malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++)
    p1[i] = (int *)malloc(sizeof(int) * cols);
  return p1;
}
int **intial_matrix(int **m, int n)
{
  for (int i = 0; i < n; i++)
    for (int j = 0; j < n; j++)
      *(m + i * n + j) = (int *)(rand() % 100);
  return m;
}

void show_matrix(int **p, int n)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
      printf("%d\t", *(p + n * i + j));
    printf("\n");
  }
}

void free_matrix(int **p, int n)
{
  printf("%d", n);
  for (int i = 0; i < n; i++)
  {
    printf("i am rush");
    free((void *)p[i]);
  }
  free((void *)p);
}