#include <stdlib.h>
#include <pthread.h>

struct foo
{
  int f_count;
  pthread_mutex_t f_lock;
  int f_id;
};

struct foo *foo_alloc(int id)
{
  struct foo *fp;
  if ((fp = malloc(sizeof(struct foo))) != NULL)
  {
    fp->f_count = 1;
    fp->f_id = id;
    if (pthread_mutex_init(&fp->f_lock, NULL) != 0)
    {
      free(fp);
      return (NULL);
    }
  }
  return (fp);
}

void foo_hold(struct foo *fp)
{
  pthread_mutex_lock(&fp->f_lock);
  fp->f_count++;
  pthread_mutex_unlock(&fp->f_lock);
}

void foo_rele(struct foo *fp)
{
  pthread_mutex_lock(&fp->lock);
  if (--fp->f_count == 0)
  {
    pthread_mutex_unlock(&fp->f_lock);
    //如果在这之间有其他锁呢？
    pthread_mutex_destory(&fp->f_lock);
    free(fp);
  }
  else
  {
    pthread_mutex_unlock(&fp->lock);
  }
}