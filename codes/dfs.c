#include <stdio.h>
#include "util.h"
#include <stdlib.h>
#include <limits.h>
#define N 17
void add_equl(int *p, int n, int x);
int main(void)
{

  int a[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 2, 4, 5, 7, 1, 2, 3, 6};
  //int b[N] = {0, 1, 1, 0, 1, 0, 0, 1, 0};
  add_equl(a, 17, 9);
  //int *p = and_binary(a, b, N);
  // for (int i = 0; i < N; i++)
  //   printf("%.f ", *(p + i));
  return 0;
}
double *insertion_sort(double *p, int n)
{
  for (int j = 1; j < n; j++)
  {
    double key = *(p + j);
    int i = j - 1;
    while (i >= 0 && *(p + i) <= key)
    {
      *(p + i + 1) = *(p + i);
      i = i - 1;
    }
    *(p + i + 1) = key;
  }
  return p;
}

int *and_binary(int *a, int *b, int n)
{
  int *p = (int *)malloc((n + 1) * sizeof(int));
  int i = 0;
  int k = 0;
  int d = 0;
  for (i = 0; i < n; i++)
  {
    k = (*(a + i) + *(b + i) + d) % 2;
    d = (*(a + i) + *(b + i) + d) / 2;
    *(p + i) = k;
  }
  *(p + i) = d;
  return p;
}

double *select_sort(double *p, int n)
{
  int i = 0;
  for (; i < n - 1; i++)
  {
    double key = *(p + i);
    int k = i;
    for (int j = i + 1; j < n; j++)
    {
      if (*(p + j) < key)
      {
        key = *(p + j);
        k = j;
      }
    }
    *(p + k) = *(p + i);
    *(p + i) = key;
  }
  return p;
}

double *merge(double *A, int p, int q, int r)
{
  int n1 = q - p + 1;
  int n2 = r - q;
  double *L = (double *)malloc((n1) * sizeof(double));
  double *R = (double *)malloc((n2) * sizeof(double));
  int i, j;
  for (i = 0; i < n1; i++)
    *(L + i) = *(A + p + i);
  for (i = 0; i < n2; i++)
    *(R + i) = *(A + q + i + 1);
  // *(L + n1) = INT_MAX;
  // *(R + n2) = INT_MAX;
  i = 0;
  j = 0;
  int k = p;
  while (k <= r && i < n1 && j < n2)
  {
    if (*(L + i) <= *(R + j))
    {
      *(A + k) = *(L + i);
      i++;
    }
    else
    {
      *(A + k) = *(R + j);
      j++;
    }
    k++;
  }
  if (i == n1)
  {
    for (; j < n2; j++, k++)
      *(A + k) = *(R + j);
  }
  else
  {
    for (; i < n1; i++, k++)
      *(A + k) = *(L + i);
  }
  // for (int k = p; k <= r; k++)
  // {
  //   if (i < n1 && j < n2)
  //   {
  //     if (*(L + i) <= *(R + j))
  //     {
  //       *(A + k) = *(L + i);
  //       i++;
  //     }
  //     else
  //     {
  //       *(A + k) = *(R + j);
  //       j++;
  //     }
  //   }
  // }
  free(L);
  free(R);
  return A;
}

double *merge_sort(double *A, int p, int r)
{
  if (p < r)
  {
    int q = (p + r) / 2;
    merge_sort(A, p, q);
    merge_sort(A, q + 1, r);
    merge(A, p, q, r);
    return A;
  }
}

void add_equl(int *p, int n, int x)
{
  int k = n;
  int i = 0;
  int j = 0;
  for (; i < n; i++)
    for (j = i; j < n; j++)
    {
      if (*(p + i) + *(p + j) == x)
        printf("%d  %d\n", *(p + i), *(p + j));
    }
}

struct node
{
  int max_left;
  int max_right;
  double left_sum;
  double right_sum;
};
struct node *find_max_crossing_subarray(double *A, int low, int mid, int high)
{
  struct node *fd;
  fd->left_sum = INT_MIN;
  fd->right_sum = INT_MIN;
  fd->max_left = mid;
  fd->max_right = mid + 1;
  double sum = 0;
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
    sum = sum + *(A + j);
    if (sum > fd->right_sum)
    {
      fd->right_sum = sum;
      fd->max_right = j;
    }
  }
  return fd;
}