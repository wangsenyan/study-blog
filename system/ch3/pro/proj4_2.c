#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>

typedef struct
{
  int l;
  int r;
} interval;
void *sort(void *param);
void *merge(void *param);
int *arr;

int main(int argc, char *argv[])
{
  arr = (int *)malloc(sizeof(int) * (argc - 1));
  int i, j, mid;
  for (i = 0; i < argc - 1; i++)
    arr[i] = atoi(argv[i + 1]);

  pthread_t tid[3];
  pthread_attr_t attr;

  interval *s = (interval *)malloc(sizeof(interval));
  s->l = 0;
  s->r = (argc - 2) / 2;
  pthread_create(&tid[0], &attr, sort, s);

  interval *ss = (interval *)malloc(sizeof(interval));
  ss->l = (argc - 2) / 2 + 1;
  ss->r = argc - 2;
  pthread_create(&tid[1], &attr, sort, ss);

  pthread_join(tid[0], NULL);
  pthread_join(tid[1], NULL);

  pthread_create(&tid[2], &attr, merge, NULL);

  pthread_join(tid[2], NULL);

  return 0;
}

void *sort(void *param)
{
  interval *s = (interval *)param;
  //sort
}
void *merge(void *param)
{ //merge
}