#include "apue.h"
#include <signal.h>
#include <unistd.h>
#include <setjmp.h>

unsigned int sleep2(unsigned int);
static void sig_int(int);

int main(void)
{
  unsigned int unslept;
  if (signal(SIGINT, sig_int) == SIG_ERR)
    err_sys("signal(SIGINT) error");
  unslept = sleep2(5);
  printf("sleep2 returned: %u\n", unslept);
  exit(0);
}

static jmp_buf env_alrm;
static void sig_alrm(int signo)
{
  longjmp(env_alrm, 1);
}

unsigned int sleep1(unsigned int seconds)
{
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    return (seconds);
  alarm(seconds);
  pause();
  return (alarm(0));
}

unsigned int sleep2(unsigned int seconds)
{
  if (signal(SIGALRM, sig_alrm) == SIG_ERR)
    return (seconds);
  if (setjmp(env_alrm) == 0) // 1
  {
    alarm(seconds); //2 相当于1~2之间没执行过
    pause();
  }
  return (alarm(0));
}
static void sig_int(int signo)
{
  int i, j;
  volatile int k;
  printf("\nsig_int starting\n");
  for (i = 0; i < 300000; i++)
    for (j = 0; j < 4000; j++)
      k += i * j;
  printf("sig_int  finished\n");
}