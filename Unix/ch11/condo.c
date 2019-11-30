#include <pthread.h>
struct msg
{
  struct msg *m_next;
};
struct msg *workq;
pthread_cond_t qready = PTHREAD_COND_INITIALIZER;
pthread_mutex_t qlock = PTHREAD_MUTEX_INITIALIZER;

void process_msg(void)
{
  struct msg *mp;
  for (;;)
  {
    pthread_mutex_lock(&qlock);
    while (workq == NULL)
      pthread_cond_wait(&qready, &qlock); //为了让调用线程放到等待条件的线程列表上原子操作，先加锁后解锁，然后重新计算条件变量(每次wait都在更改？)
    mp = workq;
    workq = mp->m_next;
    pthread_mutex_unlock(&qlock);
  }
}

void enqueue_msg(struct msg *mp)
{
  pthread_mutex_lock(&qlock);
  mp->m_next = workq;
  workq = mp;
  pthread_mutex_unlock(&qlock);
  pthread_cond_signal(&qready);
}

