#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <omp.h>
#include <stdio.h>
#include <pthread.h>
#include <math.h>
#include <time.h>

#define NUM_COUNT 100000000
int c = 0;
int tot = 0;
int i;
void *cal(void *param);
int main()
{
  srand(time(NULL));

#pragma omp parallel for
  for (i = 0; i < NUM_COUNT; i++)
  {
    tot++;
    double x_ran = ((double)(2) / RAND_MAX) * rand() - 1;
    double y_rand = ((double)(2) / RAND_MAX) * rand() - 1;
    double dist = sqrt(pow(x_ran, 2) + pow(y_rand, 2));
    if (dist < 1)
      c++;
  }

  double pi = 4 * ((double)c) / tot;
  printf("π = %f\n", pi);

  return 0;
}