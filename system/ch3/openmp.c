#include <omp.h>
#include <stdio.h>
#define N 100
int main(int argc, char *argv[])
{
  int a[N] = {0};
  int b[N] = {2};
  int c[N] = {0};
#pragma omp parallel
  {
    printf("this is a  parallel region.\n");
  }
  int i;
#pragma omp parallel for
  for (i = 0; i < N; i++)
    c[i] = a[i] + b[i];
  return 0;
}