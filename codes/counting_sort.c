#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 11
int counting_sort(int *a, int *b, int k, int n);
int main()
{
  int a[N + 1] = {0, 6, 0, 2, 0, 1, 3, 4, 6, 1, 3, 2};
  int b[N + 1] = {0};
  counting_sort(a, b, 6, N);
  for (int i = 1; i <= N; i++)
  {
    printf("%d ", b[i]);
  }

  return 0;
}

int counting_sort(int *a, int *b, int k, int n)
{
  int *c = (int *)malloc((k + 1) * sizeof(int));
  for (int i = 0; i <= k; i++)
    *(c + i) = 0;
  for (int j = 1; j <= n; j++)
    *(c + *(a + j)) = *(c + *(a + j)) + 1;
  for (int i = 1; i <= k; i++)
    *(c + i) = *(c + i) + *(c + i - 1);
  for (int j = n; j > 0; j--)
  {
    b[c[a[j]]] = a[j];
    c[a[j]] = c[a[j]] - 1;
  }
  free(c);
  return 0;
}

typedef struct
{
  double value;
  bucket *next;
} bucket;
int bucket_sort(double *a, int n)
{
  bucket *b[N] = {0};
  for (int i = 1; i <= n; i++)
  {
    insert_bucket();
  }
}

void insert_bucket(bucket **p, double value, int n)
{
  bucket *p = (bucket *)malloc(sizeof(bucket));
  int v = (int)value * n;
  if ((*p + v)->next == 0)
  {
    (*p + v)->next = p;
    (*p + v)->value = value;
  }
  else
  {
    bucket *next = (*p + v)->next;
    while (next)
      next = next->next;
    next->
  }
}