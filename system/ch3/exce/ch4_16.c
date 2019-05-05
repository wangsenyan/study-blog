
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <unistd.h>
#include <limits.h> //INT_MAX
int value = 0;
struct params
{
  int argc;
  char **argv;
};
void *average(void *param);
void *minimum(void *param);
void *maxinum(void *param);

int main(int argc, char *argv[])
{
  pid_t pid;
  pthread_t tid;
  pthread_attr_t attr;

  struct params p;
  p.argc = argc;
  p.argv = argv;

  pthread_attr_init(&attr);

  pthread_create(&tid, &attr, average, &p);
  pthread_create(&tid, &attr, minimum, &p);
  pthread_create(&tid, &attr, maxinum, &p);
  sleep(2000);
  return 0;
}

void *average(void *param)
{
  struct params *pp;
  pp = (struct params *)param;
  int sum = 0;
  for (int i = 1; i < pp->argc; i++)
    sum += atoi((pp->argv[i]));
  printf("The average value is %d\n", sum / (pp->argc - 1));
}
void *minimum(void *param)
{
  struct params *pp;
  pp = (struct params *)param;
  int mn = INT_MAX;
  for (int i = 1; i < pp->argc; i++)
  {
    //printf("%", atoi((pp->argv[i])));
    if (mn > atoi((pp->argv[i])))
      mn = atoi((pp->argv[i]));
  }
  printf("The minimum value is %d\n", mn);
}
void *maxinum(void *param)
{
  struct params *pp;
  pp = (struct params *)param;
  int mx = INT_MIN;
  for (int i = 1; i < pp->argc; i++)
    if (mx < atoi((pp->argv[i])))
      mx = atoi((pp->argv[i]));
  printf("The maxinum value is %d\n", mx);
}