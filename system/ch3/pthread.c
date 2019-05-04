//gcc -pthread -o pthread pthread.c
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h> //atoi
#define MUN_THREADS 10
int sum = 0;
void *runner(void *param);

int main(int argc, char *argv[])
{
  //pthread_t tid;
  pthread_t workers[MUN_THREADS];
  pthread_attr_t attr;

  if (argc != 2)
  {
    fprintf(stderr, "Usage: a.out<integer value>\n");
    return -1;
  }
  if (atoi(argv[1]) < 0)
  {
    fprintf(stderr, "%d must b>=0\n", atoi(argv[1]));
    return -1;
  }
  pthread_attr_init(&attr);
  for (int i = 0; i < MUN_THREADS; i++)
  {
    pthread_create(&workers[i], &attr, runner, argv[1]);
  }
  for (int i = 0; i < MUN_THREADS; i++)
  {
    pthread_join(workers[i], NULL);
  }
  //pthread_create(&tid, &attr, runner, argv[1]);
  //pthread_join(tid, NULL);
  printf("sum = %d\n", sum);
  return 0;
}

void *runner(void *param)
{
  int i, upper = atoi(param);
  // sum = 0;
  for (i = 0; i <= upper; i++)
    sum += i;
  pthread_exit(0);
}