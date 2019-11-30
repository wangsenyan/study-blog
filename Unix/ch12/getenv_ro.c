#include <string.h>
#include <errno.h>
#include <pthread.h>
#include <stdlib.h>

#define MAXSTRINGSZ 4096
static pthread_key_t key;
//static pthread_once_t init_done = PTHREAD_ONCE_INIT;

extern char **environ;
pthread_mutex_t env_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_once_t init_done = PTHREAD_ONCE_INIT;

static void thread_init(void)
{
  pthread_key_create(&key, free); //因为设置了线程私有变量，不用担心同步问题
  // pthread_mutexattr_t attr;
  // pthread_mutexattr_init(&attr);
  // pthread_mutexattr_settype(&attr, PTHREAD_MUTEX_RECURSIVE);
  // pthread_mutex_init(&env_mutex, &attr);
  // pthread_mutexattr_destroy(&attr);
}

int getenv_r(const char *name, char *buf, int buflen)
{
  int i, len; //, olen;
  char *envbuf;
  pthread_once(&init_done, thread_init);
  pthread_mutex_lock(&env_mutex);
  envbuf = (char *)pthread_getspecific(key);
  if (envbuf == NULL)
  {
    envbuf = malloc(MAXSTRINGSZ);
    if (envbuf == NULL)
    {
      pthread_mutex_unlock(&env_mutex);
      return (NULL);
    }
    pthread_setspecific(key, envbuf);
  }
  len = strlen(name);
  for (i = 0; environ[i] != NULL; i++)
  {
    if ((strncmp(name, environ[i], len) == 0) && (environ[i][len] == '='))
    {
      strncmp(envbuf, &environ[i][len + 1], MAXSTRINGSZ - 1);
      pthread_mutex_unlock(&env_mutex);
      return (envbuf);
      // olen = strlen(&environ[i][len + 1]);
      // if (olen >= buflen)
      // {
      //   pthread_mutex_unlock(&env_mutex); //buf不满足，出口
      //   return (ENOSPC);
      // }
      // strcpy(buf, &environ[i][len + 1]);
      // pthread_mutex_unlock(&env_mutex); //正常情况，出口
      // return (0);
    }
  }
  pthread_mutex_unlock(&env_mutex); //没有改环境变量 ，出口
  return (NULL);
}