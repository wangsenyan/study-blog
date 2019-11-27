#include "apue.h"
#include <pthread.h>

int main(void)
{
  int err;
  struct timespec tout;
  struct tm *tmp;
  char buf[64];
  pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

  pthread_mutex_lock(&lock);
  printf("mutex is locked\n");
  /*
  #include<time.h>
  int clock_gettime(clockid_t clk_id,struct timespec *tp);//CLOCK_REALTIME 系统实时时间
  */
  clock_gettime(CLOCK_REALTIME, &tout);
  //tm* localtime(const time_t* t_ptr);
  tmp = localtime(&tout.tv_sec);
  //%r 12小时的时间 根据区域格式化时间
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("current time is %s\n", buf);
  tout.tv_sec += 10;
  err = pthread_mutex_timedlock(&lock, &tout);
  clock_gettime(CLOCK_REALTIME, &tout);
  tmp = localtime(&tout.tv_sec);
  strftime(buf, sizeof(buf), "%r", tmp);
  printf("the time is now %s\n", buf);
  if (err == 0)
    printf("mutex locked again!\n");
  else
    printf("can't lock mutex again:%s\n", strerror(err));
  exit(0);
}