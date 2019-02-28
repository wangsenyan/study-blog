#include <stdio.h>
#include "util.h"
#include <stdlib.h>
//#include <limits.h>
#include <float.h>
#define N 17
typedef struct
{
  int max_left;
  int max_right;
  double left_sum;
  double right_sum;
} node;
typedef struct
{
  int low;
  int high;
  double sum;
} result;
result *find_max_crossing_subarray(double *A, int low, int mid, int high);
result *find_maximum_subarray(double *A, int low, int high);
result *find_maximum_subarray_boom(double *A, int n);
result *find_maximum_subarray_dynamic(double *A, int n);
int main(void)
{

  double a[N] = {-1, -2, -3, -4, 5, -6, -7, 8, -9, 17, 4, -5, 7, 1, -2, -3, -6};
  result *p = find_maximum_subarray_dynamic(a, N);
  //result *p = find_maximum_subarray(a, 0, 16);
  // result *p = find_maximum_subarray_boom(a, N);
  //printf("%d", a[0]);
  printf("%d\n %d\n %.2f\n", p->low, p->high, p->sum);
  free(p);
  return 0;
}
result *find_max_crossing_subarray(double *A, int low, int mid, int high)
{
  node *fd = (node *)malloc(sizeof(node));
  result *cross_sum = (result *)malloc(sizeof(result));
  //= {INT_MIN, INT_MIN, mid, mid + 1};
  fd->left_sum = FLT_MIN;
  fd->right_sum = FLT_MIN;
  fd->max_left = 0;
  fd->max_right = 0;
  double sum = 0;
  //printf("%.2f\n %.2f\n %d\n", fd->left_sum, fd->right_sum, fd->max_left + fd->max_right);
  for (int i = mid; i >= 0; i--)
  {
    sum += *(A + i);
    if (sum > fd->left_sum)
    {
      fd->left_sum = sum;
      fd->max_left = i;
    }
  }
  sum = 0;
  for (int j = mid + 1; j <= high; j++)
  {
    sum += *(A + j);
    if (sum > fd->right_sum)
    {
      fd->right_sum = sum;
      fd->max_right = j;
    }
  }
  cross_sum->low = fd->max_left;
  cross_sum->high = fd->max_right;
  cross_sum->sum = fd->left_sum + fd->right_sum;
  return cross_sum;
}

result *find_maximum_subarray(double *A, int low, int high)
{
  result *left_sum = (result *)malloc(sizeof(result));
  result *right_sum = (result *)malloc(sizeof(result));
  result *cross_sum = (result *)malloc(sizeof(result));
  result *last_sum = (result *)malloc(sizeof(result));
  last_sum->low = low;
  last_sum->high = high;
  last_sum->sum = *(A + low);
  int isNUll = 1;
  for (int i = low; i <= high; i++)
  {
    if (*(A + i) > 0)
      isNUll = 0;
  }
  if (isNUll)
  {
    last_sum->high = 0;
    last_sum->low = 0;
    last_sum->sum = 0;
    return last_sum;
  }
  else if (high == low)
    return last_sum;
  else
  {
    int mid = (low + high) / 2;
    left_sum = find_maximum_subarray(A, low, mid);
    right_sum = find_maximum_subarray(A, mid + 1, high);
    cross_sum = find_max_crossing_subarray(A, low, mid, high);
    if (left_sum->sum >= right_sum->sum && left_sum->sum >= cross_sum->sum)
      return left_sum;
    else if (right_sum->sum >= left_sum->sum && right_sum->sum >= cross_sum->sum)
      return right_sum;
    else
      return cross_sum;
  }
}

result *find_maximum_subarray_boom(double *A, int n)
{
  result *p = (result *)malloc(sizeof(result));
  p->low = 0;
  p->high = 0;
  p->sum = *A;
  for (int i = 0; i < n; i++)
  {
    double sum = 0;
    for (int j = i; j < n; j++)
    {
      sum += *(A + j);
      if (p->sum < sum)
      {
        p->sum = sum;
        p->low = i;
        p->high = j;
      }
    }
  }
  return p;
}
//线性时间算法
result *find_maximum_subarray_dynamic(double *A, int n)
{
  result *p = (result *)malloc(sizeof(result));
  int isNUll = 1;
  for (int i = 0; i < n; i++)
  {
    if (*(A + i) > 0)
    {
      isNUll = 0;
      p->low = i;
      p->high = i;
      p->sum = *(A + i);
      break;
    }
  }
  if (isNUll)
  {
    p->low = 0;
    p->high = 0;
    p->sum = 0;
    return p;
  }
  int low = p->low;
  for (int j = p->low; j < n - 1; j++)
  {
    double sum = 0;
    for (int k = j + 1; k >= p->low; k--)
    {
      sum += *(A + k);
      if (sum > p->sum)
      {
        p->low = k;
        p->high = j + 1;
        p->sum = sum;
      }
    }
  }
  return p;
}

