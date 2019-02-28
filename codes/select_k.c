#include <stdio.h>
#include <stdlib.h>
#define N 10
int randomized_partition(int *a, int p, int r);
int randomized_select(int *a, int p, int r, int i);
int loop_select(int *a, int p, int r, int i);
int main()
{
  int a[N + 1] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
  int b = randomized_select(a, 1, N, 6);
  int c = loop_select(a, 1, N, 6);
  printf("%d ", c);
}
int randomized_select(int *a, int p, int r, int i)
{
  if (p == r)
    return *(a + p);
  int q = randomized_partition(a, p, r);
  int k = q - p + 1;
  if (i == k)
    return *(a + q);
  else if (i < k)
    return randomized_select(a, p, q - 1, i);
  else
    return randomized_select(a, q + 1, r, i - k);
}
int loop_select(int *a, int p, int r, int i)
{
  if (p == r)
    return *(a + p);
  int q = randomized_partition(a, p, r);
  while (q != i)
  {
    if (q > i)
      q = randomized_partition(a, p, q - 1);
    else
      q = randomized_partition(a, q + 1, r);
  }
  return *(a + q);
}

int median(int *a, int *b, int n)
{
  if (n == 1)
    return min(*(a + 1), *(b + 1));
  else if (*(a + n / 2) < *(b + n / 2))
    return median(a, b, n / 2);
  else
    return median(a, b, n / 2);
}

int randomized_partition(int *a, int p, int r)
{
  int k = *(a + r);
  int i = p - 1;
  for (int j = p; j < r; j++)
  {
    if (*(a + j) <= k)
    {
      i++;
      if (i != j)
      {
        int temp = *(a + i);
        *(a + i) = *(a + j);
        *(a + j) = temp;
      }
    }
  }
  *(a + r) = *(a + i + 1);
  *(a + i + 1) = k;
  return i + 1;
}