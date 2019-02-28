#include <stdio.h>

int next[9];
int key[9];
int prev[9];
int L;
int F;

void print_array();
void print_list(int);
void print_lists();
void create();
void exchange(int, int);
void compactify_list();
void swap_next(int, int);
void swap_key(int, int);
void swap_prev(int, int);
void swap(int, int);

void create()
{
  next[0] = 0;
  key[0] = 0;
  prev[0] = 0;

  L = 7;

  next[7] = 5;
  key[7] = 9;
  prev[7] = 0;

  next[5] = 2;
  key[5] = 16;
  prev[5] = 7;

  next[2] = 3;
  key[2] = 4;
  prev[2] = 5;

  next[3] = 0;
  key[3] = 1;
  prev[3] = 2;

  F = 6;

  next[6] = 4;
  key[6] = -1;
  prev[6] = 0;

  next[4] = 8;
  key[4] = -1;
  prev[4] = 6;

  next[8] = 1;
  key[8] = -1;
  prev[8] = 4;

  next[1] = 0;
  key[1] = -1;
  prev[1] = 8;
}

void swap_next(int a, int b)
{
  int temp;
  temp = next[a];
  next[a] = next[b];
  next[b] = temp;
}

void swap_key(int a, int b)
{
  int temp;
  temp = key[a];
  key[a] = key[b];
  key[b] = temp;
}

void swap_prev(int a, int b)
{
  int temp;
  temp = prev[a];
  prev[a] = prev[b];
  prev[b] = temp;
}

void swap(int a, int b)
{
  swap_next(a, b);
  swap_key(a, b);
  swap_prev(a, b);
}

void exchange(int h, int x)
{
  if (next[x] == h)
  {
    if (prev[x] != 0)
      next[prev[x]] = h;
    if (next[h] != 0)
      prev[next[h]] = x;
    swap_key(h, x);

    next[x] = next[h];
    prev[h] = prev[x];

    prev[x] = h;
    next[h] = x;
  }
  else
  {
    if (prev[h] != 0)
      next[prev[h]] = x;
    if (next[h] != 0)
      prev[next[h]] = x;
    if (prev[x] != 0)
      next[prev[x]] = h;
    if (next[x] != 0)
      prev[next[x]] = h;
    swap(h, x);
  }
}

void compactify_list()
{
  int h = 1;
  int x = L;
  while (x != 0)
  {
    if (x != h)
    {
      if (h == F)
        F = x;
      exchange(h, x);
    }
    x = next[h];
    h++;
  }
  L = 1;
}

void print_list(int i)
{
  while (i != 0)
  {
    printf("index: %d, next: %d, key: %d, prev: %d\n", i, next[i], key[i], prev[i]);
    i = next[i];
  }
}

void print_lists()
{
  printf("------- doubly linked list ----------------\n");
  print_list(L);
  printf("------- free list ----------------\n");
  print_list(F);
}

void print_array()
{
  int i;
  printf("------- array ----------------\n");
  for (i = 1; i < 9; i++)
  {
    printf("index: %d, next: %d, key: %d, prev: %d\n", i, next[i], key[i], prev[i]);
  }
}

int main(int argc, const char *argv[])
{
  create();
  print_array();
  compactify_list();
  print_lists();
  return 0;
}