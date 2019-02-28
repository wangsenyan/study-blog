#include <stdio.h>
#include <math.h>
#include <limits.h>
#include <stdlib.h>
#define N 7
//int *dy(float *, float *, int *, int n);
int cut_rod(int *p, int n);
//int Max(int a, int b, int c);
int main(void)
{
  int s[N] = {8, 9, 10, 9, 8, 11, 13};
  //float e[N] = {10, 11, 12, 13, 14, 14, 14};
  //int w[N] = {2, 3, 5, 6, 7, 2, 3};
  //dy(s, e, w, N);
  int a = cut_rod(s, N);
  printf("%d ", a);
  return 0;
}
// int *dy(float *s, float *e, int *w, int n)
// {
//   //printf("%d\n", n);
//   int *T = (int *)malloc((n + 1) * sizeof(int));
//   int *p = (int *)malloc((n + 2) * sizeof(int));
//   T[n] = '\0';
//   p[n + 1] = '\0';
//   int i, j;
//   for (i = 0; i < n; i++)
//   {
//     p[i] = 0;
//     for (j = 0; j < i; j++)
//     {
//       if (e[j] <= s[i])
//         p[i] = j + 1;
//     }
//   }
//   for (i = 0; i < n; i++)
//   {
//     printf("%d\n", p[i]);
//   }
//   for (i = 1, *T = 0; i <= n; i++)
//   {
//     T[i] = max(w[i - 1] + T[p[i - 1]], T[i - 1]);
//   }
//   for (i = 0; i <= n; i++)
//   {
//     printf("%d\n", T[i]);
//   }
//   free(T);
//   free(p);
//   return 0;
// }

int cut_rod(int *p, int n)
{
  if (n == 0)
    return 0;
  int q = INT_MIN;
  int i=0; 
  for (; i < n; i++)
    q = max(q, p[i] + cut_rod(p, n - i - 1));
  return q;
}

// int Max(int a, int b, int c)
// {
//   if (a > b)
//     return a > c ? a : c;
//   else
//     return b > c ? b : c;
// }

int memoized_cut_rod(int *p, int n)
{
  int r[N + 1] = {0};
  int i=0;
  for (; i <= n; i++)
    r[i] = INT_MIN;
  return memoized_cut_rod_aux(p, n, r);
}

int memoized_cut_rod_aux(int *p, int n, int *r)
{
  int q = INT_MIN;
  if (r[n] >= 0)
    return r[n];
  if (n == 0)
    q = 0;
  else{
  	int i=0;
  	for (; i <= n; i++)
      q = max(q, p[i] + memoized_cut_rod_aux(p, n - i, r));
  }
  r[n] = q;
  return q;
}

int bottom_up_cut_rod(int *p, int n)
{
  int r[N + 1] = {0};
  int q = INT_MIN;
  int i,j;
  for (j = 1; j <= n; j++)
  {
    for ( i = 1; i <= j; i++)
      q = max(q, p[i] + r[j - i]);
    r[j] = q;
  }
  return r[n];
}

int *extended_bottom_up_cut_rod(int *p, int n)
{
  int r[N + 1] = {0}, s[N + 1] = {0};
  int i,j;
  int q = INT_MIN;
  for ( j = 1; j <= n; j++)
  {
    for ( i = 1; i <= j; i++)
      if (q < p[j] + r[j - i])
      {
        q = p[j] + r[j - i];
        s[j] = i;
      }
    r[j] = q;
  }
  return s;
}
