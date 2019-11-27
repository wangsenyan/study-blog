#include "apue.h"
#include <pthread.h>

struct job
{
  struct job *j_next;
  struct job *j_prev;
  pthread_t j_id;
};
struct queue
{
  struct job *q_head;
  struct job *q_tail;
  pthread_rwlock_t q_lock;
};

int queue_init(struct queue *qp)
{
  int err;
  qp->q_head = NULL;
  qp->q_tail = NULL;
  err = pthread_rwlock_init(&qp->q_lock, NULL);
  if (err != 0)
    return (err);
  return (0);
}