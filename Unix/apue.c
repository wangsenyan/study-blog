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

void err_cont(int error, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  err_doit(1, error, fmt, ap);
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
  if (action.sa_handler == SIG_IGN)
  {
    action.sa_handler = SIG_DFL;
    sigaction(SIGABRT, &action, NULL);
  }
  if (action.sa_handler == SIG_DFL)
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
  sigprocmask(SIG_SETMASK, &mask, NULL); //阻塞除SIGABRT外的所有信号
  kill(getpid(), SIGABRT);
  exit(1);
}

int system(const char *cmdstring)
{
  pid_t pid;
  int status;
  struct sigaction ignore, saveintr, savequit;
  sigset_t chldmask, savemask;
  if (cmdstring == NULL)
    return (1);
  ignore.sa_handler = SIG_IGN;
  sigemptyset(&ignore.sa_mask);
  ignore.sa_flags = 0;
  if (sigaction(SIGINT, &ignore, &saveintr) < 0)
    return (-1);
  if (sigaction(SIGQUIT, &ignore, &savequit) < 0)
    return (-1);
  sigemptyset(&chldmask);
  sigaddset(&chldmask, SIGCHLD);
  if (sigprocmask(SIG_BLOCK, &chldmask, &savemask) < 0)
    status = -1;
  if ((pid = fork()) < 0)
  {
    status = -1;
  }
  else if (pid == 0)
  {
    sigaction(SIGINT, &saveintr, NULL);
    sigaction(SIGQUIT, &savequit, NULL);
    execl("/bin/sh", "sh", "-c", cmdstring, (char *)0);
    _exit(127);
  }
  else
  {
    while (waitpid(pid, &status, 0) < 0)
    {
      if (errno != EINTR)
      {
        status = -1;
        break;
      }
    }
  }
  if (sigaction(SIGINT, &saveintr, NULL) < 0)
    return (-1);
  if (sigaction(SIGQUIT, &savequit, NULL) < 0)
    return (-1);
  if (sigprocmask(SIG_SETMASK, &savemask, NULL) < 0)
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

void daemonize(const char *cmd)
{
  int i, fd0, fd1, fd2;
  pid_t pid;
  struct rlimit rl;
  struct sigaction sa;

  umask(0);

  if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    err_quit("%s: can't get file limit", cmd);

  if ((pid = fork()) < 0)
    err_quit("%s: can't fork", cmd);
  else if (pid != 0)
    exit(0);
  setsid();

  sa.sa_handler = SIG_IGN;
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  if (sigaction(SIGHUP, &sa, NULL) < 0)
    err_quit("%s: can't ignore SIGHUP", cmd);
  if ((pid = fork()) < 0)
    err_quit("%s: can't fork", cmd);
  else if (pid != 0)
    exit(0);

  if (chdir("/") < 0)
    err_quit("%s: can't change directory to /", cmd);

  if (rl.rlim_max == RLIM_INFINITY)
    rl.rlim_max = 1024;
  for (i = 0; i < rl.rlim_max; i++)
    close(i);
  fd0 = open("/dev/null", O_RDWR);
  fd1 = dup(0);
  fd2 = dup(0);

  openlog(cmd, LOG_CONS, LOG_DAEMON);
  if (fd0 != 0 || fd1 != 1 || fd2 != 2)
  {
    syslog(LOG_ERR, "unexpected file descriptors %d %d %d", fd0, fd1, fd2);
    exit(1);
  }
  // pr_mask("child");
}
int lockfile(int fd)
{
  struct flock fl;

  fl.l_type = F_WRLCK;
  fl.l_start = 0;
  fl.l_whence = SEEK_SET;
  fl.l_len = 0;
  return (fcntl(fd, F_SETLK, &fl));
}
int already_running(void)
{
  int fd;
  char buf[16];

  fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);
  if (fd < 0)
  {
    syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
    exit(1);
  }
  if (lockfile(fd) < 0)
  {
    if (errno == EACCES || errno == EAGAIN)
    {
      close(fd);
      return (1);
    }
    syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
    exit(1);
  }
  ftruncate(fd, 0); //文件截断
  sprintf(buf, "%ld", (long)getpid());
  write(fd, buf, strlen(buf) + 1);
  return (0);
}

int set_cloexec(int fd)
{
  int val;
  if ((val = fcntl(fd, F_GETFD, 0)) < 0)
    return (-1);
  val |= FD_CLOEXEC;
  return (fcntl(fd, F_SETFD, val));
}

void set_fl(int fd, int flags)
{
  int val;
  if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    err_sys("fcntl F_GETFL error");
  val |= flags;
  if (fcntl(fd, F_SETFL, val) < 0)
    err_sys("fcntl F_SETFL error");
}
void clr_fl(int fd, int flags)
{
  int val;
  if ((val = fcntl(fd, F_GETFL, 0)) < 0)
    err_sys("fcntl F_GETFL error");
  val &= ~flags;
  if (fcntl(fd, F_SETFL, val) < 0)
    err_sys("fcntl F_SETFL error");
}

int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len)
{
  struct flock lock;
  lock.l_type = type;
  lock.l_start = offset;
  lock.l_whence = whence;
  lock.l_len = len;
  return (fcntl(fd, cmd, &lock));
}
int lock_test(int fd, int type, off_t offset, int whence, off_t len)
{
  struct flock lock;
  lock.l_type = type;
  lock.l_start = offset;
  lock.l_whence = whence;
  lock.l_len = len;
  if (fcntl(fd, F_GETLK, &lock) < 0)
    err_sys("fcntl error");
  if (lock.l_type == F_UNLCK)
    return (0);
  return (lock.l_pid);
}

static volatile sig_atomic_t sigflag;
static sigset_t newmask, oldmask, zeromask;
static void sig_usr(int signo)
{
  sigflag = 1;
}
//添加信号处理函数SIGUSR1,SIGUSR2 并屏蔽这两个信号
void TELL_WAIT(void)
{
  if (signal(SIGUSR1, sig_usr) == SIG_ERR)
    err_sys("signal(SIGUSR1) error");
  if (signal(SIGUSR2, sig_usr) == SIG_ERR)
    err_sys("signal(SIGUSR2) error");
  sigemptyset(&zeromask);
  sigemptyset(&newmask);
  sigaddset(&newmask, SIGUSR1);
  sigaddset(&newmask, SIGUSR2);

  if (sigprocmask(SIG_BLOCK, &newmask, &oldmask) < 0)
    err_sys("SIG_BLOCK error");
}

void TELL_PARENT(pid_t pid)
{
  kill(pid, SIGUSR2);
}

void WAIT_PARENT(void)
{
  while (sigflag == 0)
    sigsuspend(&zeromask);
  sigflag = 0;
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}
void TELL_CHILD(pid_t pid)
{
  kill(pid, SIGUSR1);
}
void WAIT_CHILD(void)
{
  while (sigflag == 0)
    sigsuspend(&zeromask);
  sigflag = 0;
  if (sigprocmask(SIG_SETMASK, &oldmask, NULL) < 0)
    err_sys("SIG_SETMASK error");
}

void str_cli(FILE *fp, int sockfd)
{
  int maxfdp1, stdineof;
  fd_set rset;
  char buf[MAXLINE];
  int n;
  stdineof = 0;
  FD_ZERO(&rset);
  for (;;)
  {
    if (stdineof == 0)
      FD_SET(fileno(fp), &rset);
    FD_SET(sockfd, &rset);
    maxfdp1 = MAX(fileno(fp), sockfd) + 1;
    select(maxfdp1, &rset, NULL, NULL, NULL);
    if (FD_ISSET(sockfd, &rset))
    {
      if ((n = read(sockfd, buf, MAXLINE)) == 0) //read读取一行数据
        if (stdineof == 1)
          return;
        else
        {
          perror("str_cli:server terminated prematurely");
          exit(0);
        }
      write(fileno(stdout), buf, n);
    }
    if (FD_ISSET(fileno(fp), &rset))
    {
      if ((n = read(fileno(fp), buf, MAXLINE)) == 0)
      {
        stdineof = 1;
        shutdown(sockfd, SHUT_WR);
        FD_CLR(fileno(fp), &rset);
        continue;
      }
      writen(sockfd, buf, n);
    }
  }
}

ssize_t writen(int fd, const void *vptr, size_t n)
{
  size_t nleft;
  ssize_t nwritten;
  const char *ptr;
  ptr = vptr;
  nleft = n;
  while (nleft > 0)
  {
    if ((nwritten = write(fd, ptr, nleft)) <= 0)
    {
      if (nwritten < 0 && errno == EINTR)
        nwritten = 0;
      else
        return (-1);
    }
    nleft -= nwritten;
    ptr += nwritten;
  }
  return (n);
}

int fd_pipe(int fd[2])
{
  return (socketpair(AF_UNIX, SOCK_STREAM, 0, fd));
}

int serv_listen(const char *name)
{
  int fd, len, err, rval;
  struct sockaddr_un un;
  if (strlen(name) >= sizeof(un.sun_path))
  {
    errno = ENAMETOOLONG;
    return (-1);
  }

  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    return (-2);

  unlink(name);
  memset(&un, 0, sizeof(un));
  un.sun_family = AF_UNIX;
  strcpy(un.sun_path, name);
  len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
  if (bind(fd, (sockaddr *)&un, len) < 0)
  {
    rval = -3;
    goto errout;
  }
  return (fd);

errout:
  err = errno;
  close(fd);
  errno = err;
  return (rval);
}

int serv_accept(int listenfd, uid_t *uidptr)
{
  int clifd, err, rval;
  socklen_t len;
  time_t staletime;
  struct sockaddr_un un;
  struct stat statbuf;
  char *name;
  if ((name = malloc(sizeof(un.sun_path) + 1)) == NULL)
    return (-1);
  len = sizeof(un);
  if ((clifd = accept(listenfd, (sockaddr *)&un, len)) < 0)
  {
    free(name);
    return (-2);
  }
  len -= offsetof(struct sockaddr_un, sun_path);
  memcpy(name, un.sun_path, len);
  name[len] = 0;
  if (stat(name, &statbuf) < 0)
  {
    rval = -3;
    goto errout;
  }
#ifdef S_ISSOCK
  if (S_ISSOCK(statbuf.st_mode) == 0)
  {
    rval = -4;
    goto errout;
  }
#endif
  if ((statbuf.st_mode & (S_IRWXG | S_IRWXO)) || (statbuf.st_mode & S_IRWXU) != S_IRWXU)
  {
    rval = -4;
    goto errout;
  }
  staletime = time(NULL) - STALE;
  if (statbuf.st_atime < staletime ||
      statbuf.st_ctime < staletime ||
      statbuf.st_mtime < staletime)
  {
    rval = -6;
    goto errout;
  }
  if (uidptr != NULL)
    *uidptr = statbuf.st_uid;
  unlink(name);
  fread(name);
  return (clifd);

errout:
  err = errno;
  close(clifd);
  free(name);
  errno = err;
  return (rval);
}

int cli_conn(const char *name)
{
  int fd, len, err, rval;
  struct sockaddr_un un, sun;
  int do_unlink = 0;

  if (strlen(name) >= sizeof(un.sun_path))
  {
    errno = ENAMETOOLONG;
    return (-1);
  }
  if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
    return (-1);
  memset(&un, 0, sizeof(un));
  un.sun_family = AF_UNIX;
  sprintf(un.sun_path, "%s%05ld", CLI_PATH, (long)getpid());
  len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);
  unlink(un.sun_path);
  if (bind(fd, (struct sockaddr *)&un, len) < 0)
  {
    rval = -2;
    goto errout;
  }
  if (chmod(un.sun_path, CLI_PERM) < 0)
  {
    rval = -3;
    do_unlink = 1;
    goto errout;
  }
  memset(&sun, 0, sizeof(sun));
  sun.sun_family = AF_UNIX;
  strcpy(sun.sun_path, name);
  len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
  if (connect(fd, (struct sockaddr *)&sun, len) < 0)
  {
    rval = -4;
    do_unlink = 1;
    goto errout;
  }
  return (fd);

errout:
  err = errno;
  close(fd);
  if (do_unlink)
    unlink(un.sun_path);
  errno = err;
  return (rval);
}

int send_err(int fd, int errcode, const char *msg)
{
  int n;
  if ((n = strlen(msg)) > 0)
    if (writen(fd, msg, n) != n)
      return (-1);
  if (errcode >= 0)
    errcode = -1;
  if (send_fd(fd, errcode) < 0)
    return (-1);
  return (0);
}

static struct cmsghdr *cmptr = NULL;
int send_fd(int fd, int fd_to_send)
{
  struct iovec iov[1];
  struct msghdr msg;
  char buf[2];

  iov[0].iov_base = buf;
  iov[0].iov_len = 2;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;

  if (fd_to_send < 0)
  {
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    buf[1] = -fd_to_send;
    if (buf[1] == 0) // -256
      buf[1] = 1;
  }
  else
  {
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return (-1);
    cmptr->cmsg_level = SOL_SOCKET;
    cmptr->cmsg_type = SCM_RIGHTS;
    cmptr->cmsg_len = CONTROLLEN;
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    *(int *)CMSG_DATA(cmptr) = fd_to_send;
    buf[1] = 0;
  }
  buf[0] = 0;
  if (sendmsg(fd, &msg, 0) != 2)
    return (-1);
  return (0);
}

int recv_fd(int fd, ssize_t (*userfunc)(int, const void *, size_t))
{
  int newfd, nr, status;
  char *ptr;
  char buf[MAXLINE];
  struct iovec iov[1];
  struct msghdr msg;
  status = -1;
  for (;;)
  {
    iov[0].iov_base = buf;
    iov[0].iov_len = sizeof(buf);
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;
    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return (-1);
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    if ((nr = recvmsg(fd, &msg, 0)) < 0)
    {
      err_ret("recvmsg error");
      return (-1);
    }
    else if (nr == 0)
    {
      err_ret("connection closed by server");
      return (-1);
    }
    for (ptr = buf; ptr < &buf[nr];)
    {
      if (*ptr++ == 0)
      {
        if (ptr != &buf[nr - 1])
          err_dump("message format error");
        status = *ptr & 0xFF;
        if (status == 0)
        {
          if (msg.msg_controllen < CONTROLLEN)
            err_dump("status =0 but no fd");
          newfd = *(int *)CMSG_DATA(cmptr);
        }
        else
        {
          newfd = -status;
        }
        nr -= 2;
      }
    }
    if (nr > 0 && (*userfunc)(STDERR_FILENO, buf, nr) != nr)
      return (-1);
    if (status >= 0)
      return (newfd);
  }
}

static void log_doit(int, int, int, const char *, va_list ap);
extern int log_to_stderr;

void log_open(const char *ident, int option, int facility)
{
  if (log_to_stderr == 0)
    openlog(ident, option, facility);
}

void log_ret(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
}

void log_sys(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  log_doit(1, errno, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

void log_msg(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  log_doit(0, 0, LOG_ERR, fmt, ap);
  va_end(ap);
}

void log_quit(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  log_doit(0, 0, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

void log_exit(int error, const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  log_doit(1, error, LOG_ERR, fmt, ap);
  va_end(ap);
  exit(2);
}

static void log_doit(int errnoflag, int error, int priority, const char *fmt, va_list ap)
{
  char buf[MAXLINE];
  vsnprintf(buf, MAXLINE - 1, fmt, ap);
  if (errnoflag)
    snprintf(buf + strlen(buf), MAXLINE - strlen(buf) - 1, ": %s", strerror(error));
  strcat(buf, "\n");
  if (log_to_stderr)
  {
    fflush(stdout);
    fputs(buf, stderr);
    fflush(stderr);
  }
  else
  {
    syslog(priority, "%s", buf);
  }
}