#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/wait.h>
void *runner(void *param)
{
  //int i = atoi(param);
  printf("My thread id is %ld\n", pthread_self());
  //printf("\nValue of parameter = %d", i);
  pthread_exit(0);
}

int main()
{
  pid_t pid;
  pthread_t tid;
  pthread_attr_t attr;

  pid = fork();
  //wait(NULL);

  if (pid == 0)
  { /* Child Process */

    fork();
    //wait(NULL);
    pthread_attr_init(&attr);
    //i++;
    pthread_create(&tid, &attr, runner, NULL);
    //pthread_join(tid, NULL);
  }
  fork();

  printf("is there any?\n");
  //wait(NULL);
  //printf("\n\n");
  return 0;
}