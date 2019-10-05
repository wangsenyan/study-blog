//gcc serv06.c util.c sock_ntop.c web_child.c pr_cpu_time.c  -o serv06 -lpthread
//有问题？为啥？可能是sig_int的问题 ,或web_clild的问题
#include "util.h"
#include <pthread.h>

int main(int argc,char **argv)
{
    int listenfd, connfd;
    void sig_int(int);
    void *doit(void *);
    pthread_t tid;
    socklen_t clilen, addrlen;
    struct sockaddr *cliaddr;

    if(argc==2)
        listenfd = tcp_listen(NULL, argv[1], &addrlen);
    else if(argc==3)
        listenfd = tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage: serv06 [<host>] <port#>");

    cliaddr = malloc(addrlen);

    //signal(SIGINT, sig_int);

    for (;;)
    {
        clilen = addrlen;
        connfd = accept(listenfd, cliaddr, &clilen);
        pthread_create(&tid, NULL, &doit, (void *)connfd);
    }
}

void *doit(void *arg)
{
    void web_child(int);
    pthread_detach(pthread_self());
    web_child((int)arg);
    close((int)arg);
    return (NULL);
}

void sig_int(int signo)
{
  void pr_cpu_time(void);
  pr_cpu_time();
  exit(0);
}