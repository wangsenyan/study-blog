//gcc -pthread ch4_19.c -o ch4_19 -lm
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
//#include <unistd.h> //read,write.getpid

int *num, n;
void *runner(void *param);
int main(int argc, char *argv[])
{
  if (argc < 2)
  {
    printf("need param!\n");
    return -1;
  }

  n = atoi(argv[1]);
  int k = sqrt(n);
  int i;
  num = (int *)malloc(sizeof(int) * n);
  for (i = 0; i < n; i++)
  {
    num[i] = 0;
  }

  pthread_t tid[k];
  pthread_attr_t attr;

  pthread_attr_init(&attr);

  for (i = 2; i <= k; i++)
  {
    int *p = (int *)malloc(sizeof(int));
    *p = i;
    pthread_create(&tid[i], &attr, runner, p);
  }

  for (i = 2; i <= k; i++)
  {
    pthread_join(tid[i], NULL);
  }

  for (i = 2; i < n; i++)
  {
    if (num[i] == 0)
      printf("%d\t", i);
  }
  printf("\n");
  return 0;
}

void *runner(void *param)
{
  int m = *((int *)param);
  int j;
  if (num[m] == 0)
  {
    for (j = 2 * m; j <= n; j += m)
    {
      num[j] = 1;
    }
  }
  free((int *)param);
  pthread_exit(0);
}
