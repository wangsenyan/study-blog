#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NTHREADS 1000
#define NUM_COUNT 100000
int c = 0;
int tot = 0;
int i, j;
void *cal(void *param);
int main()
{
  pid_t pid;
  pthread_t tid[NTHREADS];
  pthread_attr_t attr;

  srand(time(NULL));
  pthread_attr_init(&attr);

  for (j = 0; i < NTHREADS; j++)
  {
    pthread_create(&tid[j], &attr, cal, NULL);
  }

  for (j = 0; i < NTHREADS; j++)
  {
    pthread_join(tid[j], NULL);
  }

  double pi = 4 * ((double)c) / tot;
  printf("π = %f\n", pi);
}
void *cal(void *param)
{
  printf("Thread running\n");
  for (i = 0; i < NUM_COUNT; i++)
  {
    tot++;
    double x_ran = ((double)(2) / RAND_MAX) * rand() - 1;
    double y_rand = ((double)(2) / RAND_MAX) * rand() - 1;
    double dist = sqrt(pow(x_ran, 2) + pow(y_rand, 2));
    if (dist < 1)
      c++;
  }
  printf("Thread completed,c=%d\n", c);
  pthread_exit(0);
}