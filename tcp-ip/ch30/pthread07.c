#include <pthread.h>
#include "util.h"
#include "pthread07.h"

void thread_make(int i)
{
    void *thread_main(void *);
    pthread_create(&tptr[i].thread_tid, NULL, &thread_main, (void *)i);
    return;
}

void *thread_main(void *arg)
{
    int connfd;
    void web_child(int);
    socklen_t clilen;
    struct sockaddr *cliaddr;

    cliaddr = malloc(addrlen);

    printf("thread %d starting\n", (int)arg);
    for (;;)
    {
        clilen = addrlen;
        pthread_mutex_lock(&mlock);
        connfd = accept(listenfd, cliaddr, &clilen);
        pthread_mutex_unlock(&mlock);
        tptr[(int)arg].thread_count++;
        web_child(connfd);
        close(connfd);
    }
}