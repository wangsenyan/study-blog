#include "apue.h"

#ifdef PATH_MAX
static int pathmax = PATH_MAX;
#else
static int pathmax = 0;
#endif

#define SUSV3 200112L
static long posix_version = 0;
#define PATH_MAX_GUESS 1024

char *path_alloc(size_t *sizep)
{
  char *ptr;
  int size;

  if (posix_version == 0)
    posix_version = sysconf(_SC_VERSION);

  if (pathmax == 0)
  {
    errno = 0;
    if ((pathmax = pathconf("/", _PC_PATH_MAX)) < 0)
    {
      if (errno == 0)
        pathmax = PATH_MAX_GUESS;
      else
        err_sys("pathconf error for _PC_PATH_MAX");
    }
    else
    {
      pathmax++;
    }
  }
  if (posix_version < SUSV3)
    size = pathmax + 1;
  else
    size = pathmax;
  if ((ptr = malloc(size)) == NULL)
    err_sys("malloc error for pathname");
  if (sizep != NULL)
    *sizep = size;
  return (ptr);
}
void err_exit(int error, const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_msg(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
}
void err_quit(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(0, 0, fmt, ap);
  va_end(ap);
  exit(1);
}

void err_sys(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  exit(1);
}
void err_ret(const char *fmt, ...)
{
  va_list ap;

  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
}
void err_dump(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, errno, fmt, ap);
  va_end(ap);
  abort();
  exit(1);
}
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap)
{
  char buf[MAXLINE];
  vsnprintf(buf, MAXLINE, fmt, ap);
  if (errnoflag)
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf), ": %s", strerror(error));
  strcat(buf, "\n");
  fflush(stdout); /* in case stdout and stderr are the same */
  fputs(buf, stderr);
  fflush(NULL); /* flushes all stdio output streams */
}