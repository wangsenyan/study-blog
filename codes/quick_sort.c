#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define N 12
int partition_increase(int *a, int p, int r);
void quick_sort(int *a, int p, int r);
int partition_decrease(int *a, int p, int r);
int *partition_equl(int *a, int p, int r);
void quick_sort_equl(int *a, int p, int r);
void tail_recursive_quicksort(int *a, int p, int r);
int main()
{
  int a[N + 1] = {0, 13, 19, 9, 5, 12, 8, 7, 4, 21, 2, 6, 11};
  int b[N + 1] = {0, 4, 2, 4, 5, 4, 1, 1, 1, 1, 1, 3, 4};
  //quick_sort_equl(b, 1, N);
  tail_recursive_quicksort(b, 1, N);
  for (int i = 1; i <= N; i++)
    printf("%d \t", b[i]);
}

int partition_increase(int *a, int p, int r)
{
  int x = *(a + r);
  int i = p - 1;
  for (int j = p; j < r; j++)
  {
    if (*(a + j) <= x)
    {
      i = i + 1;
      if (i != j)
      {
        int temp = *(a + i);
        *(a + i) = *(a + j);
        *(a + j) = temp;
      }
    }
  }
  *(a + r) = *(a + i + 1);
  *(a + i + 1) = x;
  return i + 1;
}
int partition_decrease(int *a, int p, int r)
{
  int x = *(a + r);
  int i = p - 1;
  for (int j = p; j < r; j++)
  {
    if (*(a + j) >= x)
    {
      i = i + 1;
      int temp = *(a + i);
      *(a + i) = *(a + j);
      *(a + j) = temp;
    }
  }
  *(a + r) = *(a + i + 1);
  *(a + i + 1) = x;
}

void quick_sort(int *a, int p, int r)
{
  if (p < r)
  {
    int q = partition_decrease(a, p, r);
    quick_sort(a, p, q - 1);
    quick_sort(a, q + 1, r);
  }
}
int *partition_equl(int *a, int p, int r)
{
  int x = *(a + r);
  int i = p - 1;
  //int q = p - 1;
  int t = p - 1;
  int temp;
  for (int j = p; j < r; j++)
  {
    if (*(a + j) <= x)
    {
      t++; 
      temp = *(a + j);
      *(a + j) = *(a + t);
      *(a + t) = temp;
      if (temp < x)
      {
        i++;
        //q++;
        temp = *(a + t);
        *(a + t) = *(a + i);
        *(a + i) = temp;
      }
    }
  }
  *(a + r) = *(a + t + 1);
  *(a + t + 1) = x;
  int b[2] = {i + 1, t + 1};
  //int b[2] = {q + 1, t + 1};
  int *ptr;
  return ptr = b;
}

void quick_sort_equl(int *a, int p, int r)
{
  if (p < r)
  {
    int *b = partition_equl(a, p, r);
    int q = b[0];
    int t = b[1];
    quick_sort_equl(a, p, q - 1);
    quick_sort_equl(a, t + 1, r);
  }
}

void tail_recursive_quicksort(int *a, int p, int r)
{
  while (p < r)
  { 
    int q = partition_increase(a, p, r);
    if(q<(r+p)/2){
      tail_recursive_quicksort(a,p,q-1);
      p=q+1;
    } else{
     tail_recursive_quicksort(a, p+1, r);
     r=q-1;
    }
  }
}
