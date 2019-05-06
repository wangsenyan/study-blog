#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define N 11
typedef struct
{
  int col;
  int row;
} parameters;

int vct[9][9] = {
    {6, 2, 4, 5, 3, 9, 1, 8, 7},
    {5, 1, 9, 7, 2, 8, 6, 3, 4},
    {8, 3, 7, 6, 1, 4, 2, 9, 5},
    {1, 4, 3, 8, 6, 5, 7, 2, 9},
    {9, 5, 8, 2, 4, 7, 3, 6, 1},
    {7, 6, 2, 3, 9, 1, 4, 5, 8},
    {3, 7, 1, 9, 5, 6, 8, 4, 2},
    {4, 9, 6, 1, 8, 2, 5, 7, 3},
    {2, 8, 5, 4, 7, 3, 9, 1, 6}};
int tag = 1;
void *eachCol();
void *eachRow();
void *eachNet(void *param);

int main()
{
  pthread_t tid[N];
  pthread_attr_t attr;
  int i, j, k = 2;
  //arameters *data[3] = (parameters *)malloc(sizeof(parameters) * 3);

  pthread_attr_init(&attr);

  pthread_create(&tid[0], &attr, eachCol, NULL);
  pthread_create(&tid[1], &attr, eachRow, NULL);
  for (i = 0; i < 9; i += 3)
  {
    for (j = 0; j < 9; j += 3)
    {
      parameters *c = (parameters *)malloc(sizeof(parameters));
      c->col = i;
      c->row = i;
      pthread_create(&tid[k++], &attr, eachNet, c);
    }
  }
  for (i = 0; i < N; i++)
  {
    pthread_join(tid[i], NULL);
  }
  if (tag)
    printf("True\n");
  else
    printf("False\n");
}
void *eachCol()
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    int r = 0;
    for (j = 0; j < 9; j++)
    {
      r = r ^ (j + 1) ^ vct[i][j];
    }
    if (r != 0)
    {
      printf("%d col is error\n", i + 1);
      tag = 0;
      pthread_exit(0);
    }
  }
  pthread_exit(0);
}
void *eachRow()
{
  int i, j;
  for (i = 0; i < 9; i++)
  {
    int r = 0;
    for (j = 0; j < 9; j++)
    {
      r = r ^ (j + 1) ^ vct[j][i];
    }
    if (r != 0)
    {
      printf("%d row is error\n", i + 1);
      tag = 0;
      pthread_exit(0);
    }
  }
  pthread_exit(0);
}
void *eachNet(void *param)
{
  parameters *p = (parameters *)param;
  int i, j, k = 1, r = 0;
  for (i = p->col; i < p->col + 3; i++)
  {
    for (j = p->row; j < p->row + 3; j++)
    {
      r = r ^ k ^ vct[i][j];
    }
  }
  if (r != 0)
  {
    printf("%d col %d row is error\n", p->col, p->row);
    tag = 0;
  }
  free(p);
  pthread_exit(0);
}
