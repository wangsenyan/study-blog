#include <stdio.h>
#include <pthread.h>
#include <sys/wait.h>
#include <unistd.h>

void *runner(void *param)
{
  printf("this is what???");
  pthread_exit(0);
}

int main()
{
  pid_t pid;
  pthread_t tid;
  pthread_attr_t attr;
  pid = fork();

  if (pid == 0)
  {
    fork();
    pthread_attr_init(&attr);
    pthread_create(&tid, &attr, &runner, NULL);
  }
  fork();
  return 0;
}