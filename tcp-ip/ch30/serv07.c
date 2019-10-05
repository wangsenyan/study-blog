//sig_int需要wait
//gcc serv07.c util.c sock_ntop.c web_child.c pr_cpu_time.c  -o serv07 -lpthread
#include <pthread.h>
#include "util.h"
#include "pthread07.h"

pthread_mutex_t mlock = PTHREAD_MUTEX_INITIALIZER;

int main(int argc,char **argv)
{
    int i;
    void sig_int(int), thread_make(int);

    if(argc==3)
        listenfd = tcp_listen(NULL, argv[1], &addrlen);
    else if(argc==4)
        listenfd = tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage : serv07 [<host>] <port#> <#threads>");

    nthreads = atoi(argv[argc - 1]);
    tptr = calloc(nthreads, sizeof(Thread));

    for (i = 0; i < nthreads;i++)
        thread_make(i);
    signal(SIGINT, sig_int);
    for (;;)
        pause();
}

// void sig_int(int signo)
// {
//   void pr_cpu_time(void);
//   pr_cpu_time();
//   exit(0);
// }

void sig_int(int signo)
{
  int i;
  void pr_cpu_time(void);
  while (wait(NULL) > 0)
    ;
  if (errno != ECHILD)
    err_sys("wait error");
  pr_cpu_time();
  exit(0);
}