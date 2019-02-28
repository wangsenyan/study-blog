#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define LETT(i) 2 * i
#define RIGHT(i) 2 * i + 1
#define PARENT(i) i / 2
#define LETT_D(i, d) i *d
#define CHILD_D_K(i, d, k) i *d - d + 1 + k
#define PARENT_D(i, d) i / d
#define N 24
static int time = 0;
int *max_heapify(int *p, int i, int n);
int *build_max_heap(int *p, int n);
int *heap_sort(int *p, int n);
int *heap_increase_key(int *p, int i, int key, int n);
int *max_heap_insert(int *p, int n, int key);
int *heap_delete(int *p, int i, int n);
int *max_heapify_d(int *p, int i, int d, int n);
int heap_extract_max_d(int *p, int d, int n);
int *max_heap_insert_d(int *p, int key, int d, int n);
int *heap_increase_key_d(int *p, int i, int key, int d, int n);
int young(int p[4][4], int i, int j, int m, int n);
int heap_extract_max_young(int p[4][4], int m, int n);
int select_young(int p[][4], int m, int n, int k);
int check(int p[][4], int m, int n, int k);
int main(void)
{
  int a[N + 1] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
  int b[N + 2] = {0, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
  int c[4][4] = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}, {13, 14, 15, 16}};
  //max_heap_insert_d(b, 20, 3, N);
  //int rt = select_young(c, 4, 4, 16);
  int rt = check(c, 4, 4, 16);
  printf("%d ", rt);
  //heap_extract_max_young(c, 4, 4);
  // for (int i = 0; i < 4; i++)
  // {
  //   for (int j = 0; j < 4; j++)
  //     printf("%d  ", c[i][j]);
  //   printf("\n");
  // }
  return 0;
}

int *max_heapify(int *p, int i, int n)
{
  int l = LETT(i);
  int r = RIGHT(i);
  int largest = i;

  //printf("%d %d %d\n",l,r,largest );
  if (l <= n && *(p + l) >= *(p + i))
    largest = l;
  if (r <= n && *(p + r) >= *(p + largest))
    largest = r;
  if (largest != i)
  {
    int temp = *(p + largest);
    *(p + largest) = *(p + i);
    *(p + i) = temp;
    max_heapify(p, largest, n);
  }
}

int *build_max_heap(int *p, int n)
{
  for (int i = n / 2; i > 0; i--)
    max_heapify(p, i, n);
}

int *heap_sort(int *p, int n)
{
  build_max_heap(p, n);
  for (int i = n; i > 1; i--)
  {
    int temp = *(p + 1);
    *(p + 1) = *(p + n);
    *(p + n) = temp;
    n--;
    max_heapify(p, 1, n);
  }
}

int heap_maximum(int *p)
{
  return *p;
}
int heap_extract_max(int *p, int n)
{
  if (n < 2)
    return -1;
  int max = *(p + 1);
  *(p + 1) = *(p + n);
  n--;
  max_heapify(p, 1, n);
  return max;
}
int *heap_increase_key(int *p, int i, int key, int n)
{
  if (key < *(p + i))
    return NULL;
  *(p + i) = key;
  int parent = PARENT(i);
  while (i > 1 && key > *(p + parent))
  {
    //printf("%d %d %d %d", *(p + i), *(p + parent), i, parent);
    // int temp = *(p + parent);
    // *(p + parent) = *(p + i);
    // *(p + i) = temp;
    *(p + i) = *(p + parent);
    i = parent;
    parent = PARENT(i);
  }
  *(p + i) = key;
  return p;
}

int *max_heap_insert(int *p, int n, int key)
{
  n++;
  *(p + n) = INT_MIN;
  heap_increase_key(p, n, key, n);
}

int *heap_delete(int *p, int i, int n)
{
  heap_increase_key(p, i, INT_MAX, n);
  *(p + 1) = *(p + n);
  n--;
  max_heapify(p, 1, n);
  return p;
}

int heap_extract_max_d(int *p, int d, int n)
{
  if (n < 2)
    return -1;
  int max = *(p + 1);
  *(p + 1) = *(p + n);
  n--;
  max_heapify_d(p, 1, d, n);
  return max;
}
int *max_heapify_d(int *p, int i, int d, int n)
{
  int l = CHILD_D_K(i, d, 1);
  int r = CHILD_D_K(i, d, d);
  int largest = i;
  while (l <= r && l <= n)
  {
    if (*(p + l) > *(p + largest))
      largest = l;
    l++;
  }

  //printf("%d %d %d\n",l,r,largest );
  if (largest != i)
  {
    int temp = *(p + largest);
    *(p + largest) = *(p + i);
    *(p + i) = temp;
    max_heapify_d(p, largest, d, n);
  }
}

int *max_heap_insert_d(int *p, int key, int d, int n)
{
  n++;
  *(p + n) = INT_MIN;
  heap_increase_key_d(p, n, key, d, n);
}
int *heap_increase_key_d(int *p, int i, int key, int d, int n)
{
  if (key < *(p + i))
    return NULL;
  *(p + i) = key;
  int parent = PARENT_D(i, d);
  while (i > 1 && key > *(p + parent))
  {
    //printf("%d %d %d %d", *(p + i), *(p + parent), i, parent);
    // int temp = *(p + parent);
    // *(p + parent) = *(p + i);
    // *(p + i) = temp;
    *(p + i) = *(p + parent);
    i = parent;
    parent = PARENT(i);
  }
  *(p + i) = key;
  return p;
}

int heap_extract_max_young(int p[4][4], int m, int n)
{
  if (n < 1 || m < 1)
    return -1;
  int max = p[0][0];
  p[0][0] = p[m - 1][n - 1];
  p[m - 1][n - 1] = INT_MAX;
  young(p, 0, 0, m, n);
  return max;
}
int young(int p[4][4], int i, int j, int m, int n)
{
  int down = i + 1;
  int right = j + 1;
  int minimum_i = i;
  int minimum_j = j;
  if (i < m - 1 && p[i][j] > p[down][j])
  {
    minimum_i = down;
    minimum_j = j;
  }
  if (j < m - 1 && p[minimum_i][minimum_j] > p[i][right])
  {
    minimum_j = right;
    minimum_i = i;
  }
  if (minimum_i != i || minimum_j != j)
  {
    int temp = p[i][j];
    p[i][j] = p[minimum_i][minimum_j];
    p[minimum_i][minimum_j] = temp;
    young(p, minimum_i, minimum_j, n, m);
  }
  return 0;
}

int select_young(int p[][4], int m, int n, int k)
{
  int i = 0;
  int j = 0;
  while (p[i][j] < k && j < n - 1)
    j++;
  while (p[i][j] < k && i < m - 1)
    i++;
  while (p[i][j] > k && i >= 0)
    j--;
  if (p[i][j] == k)
    return 1;
  else
    return 0;
}
int check(int p[][4], int m, int n, int k)
{
  int i = 0;
  int j = 0;
  while (p[i][j] < k && i < m - 1)
    i++;
  while (i > 0 && j < n - 1)
  {
    if (p[i][j] < k)
      j++;
    if (p[i][j] > k)
      i--;
  }
  if (p[i][j] == k)
    return 1;
  else
    return 0;
}