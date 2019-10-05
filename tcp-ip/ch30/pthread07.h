
typedef struct {
    pthread_t thread_tid;
    long thread_count;
} Thread;
Thread *tptr;
int listenfd, nthreads;
socklen_t addrlen;
pthread_mutex_t mlock;