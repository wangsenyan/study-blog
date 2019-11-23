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

void pr_exit(int status)
{
  if (WIFEXITED(status))
    printf("normal termination,exit status = %d\n",
           WEXITSTATUS(status));
  else if (WIFSIGNALED(status))
    printf("abnormal termination,signal number = %d%s\n",
           WTERMSIG(status),
#ifdef WCOREDUMP
           WCOREDUMP(status) ? " (core file generated)" : "");
#else
           "");
#endif
  else if (WIFSTOPPED(status))
    printf("child stopped,signal number = %d\n",
           WSTOPSIG(status));
}

void pr_ids(char *name)
{
  printf("%s: pid = %ld, ppid = %ld, pgrp = %ld, tpgrp = %ld\n", name, (long)getpid(), (long)getppid(), (long)getpgrp(), (long)tcgetpgrp(STDIN_FILENO));
  fflush(stdout);
}

Sigfunc *signal(int signo, Sigfunc *func)
{
  struct sigaction act, oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;

  if (signo == SIGALRM)
  {
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
  }
  else
  {
    act.sa_flags |= SA_RESTART;
  }
  if (sigaction(signo, &act, &oact) < 0)
    return (SIG_ERR);
  return (oact.sa_handler);
}

Sigfunc *signal_intr(int signo, Sigfunc *func)
{
  struct sigaction act, oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask);
  act.sa_flags = 0;
#ifdef SA_INTERRUPT
  act.sa_flags |= SA_INTERRUPT;
#endif
  if (sigaction(signo, &act, &oact) < 0)
    return (SIG_ERR);
  return (oact.sa_handler);
}

void pr_mask(const char *str)
{
  sigset_t sigset;
  int errno_save;
  errno_save = errno;
  if (sigprocmask(0, NULL, &sigset) < 0)
    err_ret("sigpromask error");
  else
  {
    printf("%s", str);
    if (sigismember(&sigset, SIGINT))
      printf(" SIGINT");
    if (sigismember(&sigset, SIGQUIT))
      printf(" SIGQUIT");
    if (sigismember(&sigset, SIGUSR1))
      printf(" SIGUSR1");
    if (sigismember(&sigset, SIGALRM))
      printf(" SIGALRM");
    printf(" \n");
  }
  errno = errno_save;
}

void abort(void)
{
  sigset_t mask;
  struct sigaction action;
  sigaction(SIGABRT, NULL, &action);
  if(action.sa_handler==SIG_IGN)
  {
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
  }
  if(action.sa_handler==SIG_DFL)
  {
    fflush(NULL);
  }
  sigfillset(&mask);
  sigdelset(&mask, SIGABRT);
  sigprocmask(SIG_SETMASK, &mask, NULL);
  kill(getpid(), SIGABRT);

  //信号处理程返回时，abort终止该进程
  fflush(NULL);
  action.sa_handler = SIG_DFL;
  sigaction(SIGABRT, &action, NULL);
  sigprocmask(SIG_SETMASK, &mask, NULL);//阻塞除SIGABRT外的所有信号
  kill(getpid(), SIGABRT);
  exit(1);
}

int system(const char *cmdstring)
{
  pid_t pid;
  int status;
  struct sigaction ignore, saveintr, savequit;
  sigset_t chldmask, savemask;
  if(cmdstring == NULL)
    return (1);
  ignore.sa_handler = SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;
  if(sigaction(SIGINT,&ignore,&saveintr)<0)
    return (-1);
  if(sigaction(SIGQUIT,&ignore,&savequit)<0)
    return (-1);
  sigemptyset(&chldmask);
  sigaddset(&chldmask, SIGCHLD);
  if(sigprocmask(SIG_BLOCK,&chldmask,&savemask)<0)
    status = -1;
  if((pid=fork())<0){
    status = -1;
  }else if(pid==0){
    sigaction(SIGINT, &saveintr, NULL);
    sigaction(SIGQUIT, &savequit, NULL);
    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127);
  }else{
    while (waitpid(pid,&status,0)<0)
    {
      if(errno!=EINTR){
        status = -1;
        break;
      }
    }
  }
  if(sigaction(SIGINT,&saveintr,NULL)<0)
    return (-1);
  if(sigaction(SIGQUIT,&savequit,NULL)<0)
    return (-1);
  if(sigprocmask(SIG_SETMASK,&savemask,NULL)<0)
    return (-1);
  return (status);
} 

static void sig_alrm(int signo)
{

}
unsigned int sleep(unsigned int seconds)
{
  struct sigaction newact, oldact;
  sigset_t newmask, oldmask, suspmask;
  unsigned int unslept;

  newact.sa_handler = sig_alrm;
  sigemptyset(&newact.sa_mask);
  newact.sa_flags = 0;
  sigaction(SIGALRM, &newact, &oldact);

  sigemptyset(&newmask);
  sigaddset(&newmask, SIGALRM);
  sigprocmask(SIG_BLOCK, &newmask, &oldmask);

  alarm(seconds);

  suspmask = oldmask;
  sigdelset(&suspmask, SIGALRM);

  sigsuspend(&suspmask);

  unslept = alarm(0);

  sigaction(SIGALRM, &oldact, NULL);
  sigprocmask(SIG_SETMASK, &oldmask, NULL);
  return (unslept);
}