#include "apue.h"
#include <fcntl.h>
#include <dirent.h>
#include <ctype.h>
#include <pwd.h>
#include <pthread.h>
#include <strings.h>
#include <sys/select.h>
#include <sys/uio.h>

#include "print.h"
#include "ipp.h"

#define HTTP_INFO(x) ((x) >= 100 && (x) <= 199)
#define HTTP_SUCCESS(x) ((x) >= 200 && (x) <= 299)

struct job
{
  struct job *next;
  struct job *prev;
  long jobid;
  struct printreq req;
};

/**
 * Describes a thread processing a client request
 */
struct worker_thread
{
  struct worker_thread *next;
  struct worker_thread *prev;
  pthread_t tid;
  int sockfd;
};

int log_to_stderr = 0;

/**
 * Printer-related stuff 
 * 打印机的网络地址
 */
struct addrinfo *printer;
char *printer_name;
pthread_mutex_t configlock = PTHREAD_MUTEX_INITIALIZER;
int reread;

/**
 * Thread-related stuff
*/
struct worker_thread *workers; //双向链表的头部
pthread_mutex_t workerlock = PTHREAD_MUTEX_INITIALIZER;
sigset_t mask;

/**
 * Job-related stuff
*/
struct job *jobhead, *jobtail;
int jobfd;
int32_t nextjob;
pthread_mutex_t joblock = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t jobwait = PTHREAD_COND_INITIALIZER;

void init_request(void);
void init_printer(void);
void update_jobno(void);
int32_t get_newjobno(void);
void add_job(struct printreq *, int32_t);
void replace_job(struct job *);
void remove_job(struct job *);
void build_qonstart(void);
void *client_thread(void *);
void *printer_thread(void *);
void *signal_thread(void *);
ssize_t readmore(int, char **, int, int *);
int printer_status(int, struct job *);
void add_worker(pthread_t, int);
void kill_workers(void);
void client_cleanup(void *);

int main(int argc, char *argv[])
{
  pthread_t tid;
  struct addrinfo *ailist, *aip;
  int sockfd, err, i, n, maxfd;
  char *host;
  fd_set rendezvous, rset;
  struct sigaction sa;
  struct passwd *pwdp;

  if (argc != 1)
    err_quit("usage:printd");
  daemonize("printd");
  sigemptyset(&sa.sa_mask);
  sa.sa_flags = 0;
  sa.sa_handler = SIG_IGN;
  if (sigaction(SIGFIPE, &sa, NULL) < 0)
    log_sys("sigaction failed");
  sigemptyset(&mask);
  sigaddset(&mask, SIGHUP);
  sigaddset(&mask, SIGTERM);
  if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
    log_sys("pthread_sigmask failed");
  n = sysconf(_SC_HOST_NAME_MAX);
  if (n < 0)
    n = HOST_NAME_MAX;
  if ((host = malloc(n)) == NULL)
    log_sys("malloc error");
  if (gethostname(host, n) < 0)
    log_sys("gethostname error");
  if ((err = getaddrlist(host, "print", &ailist)) != 0)
  {
    log_quit("getaddrinfo error: %s", gai_strerror(err));
    exit(1);
  }
  FD_ZERO(&rendezvous);
  maxfd = -1;
  for (aip = ailist; aip != NULL; aip = aip->ai_next)
  {
    if ((sockfd = initserver(SOCK_STREAM, aip->ai_addr, aip->ai_addrlen, QLEN)) >= 0)
    {
      FD_SET(sockfd, &rendezvous);
      if (sockfd > maxfd)
        maxfd = sockfd;
    }
  }
  if (maxfd == -1)
    log_quit("service not enabled");
  pwdp = getpwnam(LPNAME);
  if (pwdp == NULL)
    log_sys("can't find user %s", LPNAME);
  if (pwdp->pw_uid == 0)
    log_quit("user %s is privileged", LPNAME);
  if (setgid(pwdp->pw_gid) < 0 || setuid(pwdp->pw_uid) < 0)
    log_sys("can't change IDs to user %s", LPNAME);
  init_request();
  init_printer();

  err = pthread_create(&tid, NULL, printer_thread, NULL);
  if (err == 0)
    err = pthread_create(&tid, NULL, signal_thread, NULL);
  if (err != 0)
    log_exit(err, "can't create thread");
  build_qonstart();
  log_msg("deamon initialized");
  for (;;)
  {
    rset = rendezvous;
    if (select(maxfd + 1, &rset, NULL, NULL, NULL) < 0)
      log_sys("select failed");
    for (i = 0; i <= maxfd; i++)
    {
      if (FD_ISSET(i, &rset))
      {
        if ((sockfd = accept(i, NULL, NULL)) < 0)
          log_ret("accept failed");
        pthread_create(&tid, NULL, client_thread, (void *)((long)sockfd));
      }
    }
  }
  exit(0);
}

void init_request(void)
{
  int n;
  char name[FILENMSZ];
  sprintf(name, "%s/%s", SPOOLDIR, JOBFILE);
  jobfd = open(name, O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
  if (write_lock(jobfd, 0, SEEK_SET, 0) < 0)
    log_quit("deamon already running");
  if ((n = read(jobfd, name, FILENMSZ)) < 0)
    log_sys("can't read job file");
  if (n == 0)
    nextjob = 1;
  else
    nextjob = atol(name);
}

void init_printer(void)
{
  printer = get_printaddr();
  if (printer == NULL)
    exit(1);
  printer_name = printer->ai_canonname;
  if (printer_name == NULL)
    printer_name = "printer";
  log_msg("printer is %s", printer_name);
}

void update_jobno(void)
{
  char buf[32];
  if (lseek(jobfd, 0, SEEK_SET) == -1)
    log_sys("can't seek in job file");
  sprintf(buf, "%d", nextjob);
  if (write(jobfd, buf, strlen(buf)) < 0)
    log_sys("can't update job file");
}

int32_t get_newjobno(void)
{
  int32_t jobid;

  pthread_mutex_lock(&joblock);
  jobid = nextjob++;
  if (nextjob <= 0)
    nextjob = 1;
  pthread_mutex_unlock(&joblock);
  return (jobid);
}

void add_job(struct printreq *reqp, int32_t jobid)
{
  struct job *jp;
  if ((jp = malloc(sizeof(struct job))) == NULL)
    log_sys("malloc failed");
  memcpy(&jp->req, reqp, sizeof(struct printreq));
  jp->jobid = jobid;
  jp->next = NULL;
  pthread_mutex_lock(&joblock);
  jp->prev = jobtail;
  if (jobtail == NULL)
    jobhead = jp;
  else
    jobtail->next = jp;
  jobtail = jp;
  jobtail = jp;
  pthread_mutex_unlock(&joblock);
  pthread_cond_signal(&jobwait);
}

/**
 * Replace a job back on the head of the list
*/
void replace_job(struct job *jp)
{
  pthread_mutex_lock(&joblock);
  jp->prev = NULL;
  jp->next = jobhead;
  if (jobhead == NULL)
    jobtail = jp;
  else
    jobhead->prev = jp;
  jobhead = jp;
  pthread_mutex_unlock(&joblock);
}

/**
 * Remove a job from the list of pending jobs
*/
void remove_job(struct job *target)
{
  if (target->next != NULL)
    target->next->prev = target->prev;
  else
    jobtail = target->prev;
  if (target->prev != NULL)
    target->prev->next = target->next;
  else
    jobhead = target->next;
}
/**
 * check the spool directory for pending jobs on start-up
 * 在启动时检查假脱机目录中是否有挂起的作业
*/
void build_qonstart(void)
{
  int fd, err, nr;
  int32_t jobid;
  DIR *dirp;
  struct dirent *entp;
  struct printreq req;
  char dname[FILENMSZ], fname[FILENMSZ];
  sprintf(dname, "%s/%s", SPOOLDIR, REQDIR);
  if ((dirp = opendir(dname)) == NULL)
    return;
  while ((entp = readdir(dirp)) != NULL)
  {
    if (strcmp(entp->d_name, ".") == 0 || strcmp(entp->d_name, "..") == 0)
      continue;
    sprintf(fname, "%s%s%s", SPOOLDIR, REQDIR, entp->d_name);
    if ((fd = open(fname, O_RDONLY)) < 0)
      continue;
    nr = read(fd, &req, sizeof(struct printreq));
    if (nr != sizeof(struct printreq))
    {
      if (nr < 0)
        err = errno;
      else
        err = EIO;
      close(fd);
      log_msg("build_qonstart: can't read %s: %s", fname, strerror(err));
      unlink(fname);
      sprintf(fname, "%s%s%s", SPOOLDIR, DATADIR, entp->d_name);
      unlink(fname);
      continue;
    }
    jobid = atol(entp->d_name);
    log_msg("adding job %d to queue", jobid);
    add_job(&req, jobid);
  }
  closedir(dirp);
}

/**
 * accept a print job from a client
*/
void client_thread(void *arg)
{
  int n, fd, sockfd, nr, nw, first;
  int32_t jobid;
  pthread_t tid;
  struct printreq req;
  struct printresp res;
  char name[FILENMSZ];
  char buf[IOBUFSZ];
  tid = pthread_self();
  pthread_cleanup_push(client_cleanup, (void *)((long)tid));
  sockfd = (long)arg;
  add_worker(tid, sockfd);
  if ((n = treadn(sockfd, &req, sizeof(struct printreq), 10)) != sizeof(struct printreq))
  {
    res.jobid = 0;
    if (n < 0)
      res.retcode = htonl(errno);
    else
      res.retcode = htonl(EIO);
    strncpy(res.msg, strerror(res.retcode), MSGLEN_MAX);
    writen(sockfd, &res, sizeof(struct printresp));
    pthread_exit((void *)1);
  }
  req.size = ntohl(req.size);
  req.flags = ntohl(req.flags);
  jobid = get_newjobno();
  sprintf(name, "%s/%s/%ld", SPOOLDIR, DATADIR, jobid);
  fd = creat(name, FILEPERM);
  if (fd < 0)
  {
    res.jobid = 0;
    res.retcode = htonl(errno);
    log_msg("client_thread: can't create %s: %s", name, strerror(res.retcode));
    strncpy(res.msg, strerror(res.retcode), MSGLEN_MAX);
    writen(sockfd, &res, sizeof(struct printresp));
    pthread_exit((void *)1);
  }
  first = 1;
  while ((nr = tread(sockfd, buf, IOBUFSZ, 20)) > 0)
  {
    if (first)
    {
      first = 0;
      if (strncmp(buf, "%!PS", 4) != 0)
        req.flags |= PR_TEXT;
    }
    nw = write(fd, buf, nr);
    if (nw != nr)
    {
      res.jobid = 0;
      if (nw < 0)
        res.retcode = htonl(errno);
      else
        res.retcode = htonl(EIO);
      log_msg("client_thtread: can't write %s: %s", name, strerror(res.retcode));
      close(fd);
      strncpy(res.msg, strerror(res.retcode), MSGLEN_MAX);
      writen(sockfd, &res, sizeof(struct printresp));
      unlink(name);
      pthread_exit((void *)1);
    }
  }
  close(fd);
  sprintf(name, "%s/%s/%s", SPOOLDIR, REQDIR, jobid);
  fd = creat(name, FILEPERM);
  if (fd < 0)
  {
    res.jobid = 0;
    res.retcode = htonl(errno);
    log_msg("client_thread: can't create %s: %s", name, strerror(res.retcode));
    strncpy(res.msg, strerror(res.retcode), MSGLEN_MAX);
    writen(sockfd, &res, sizeof(struct printresp));
    sprintf(name, "%s/%s/%ld", SPOOLDIR, DATADIR, jobid);
    unlink(name);
    pthread_exit((void *)1);
  }
  nw = write(fd, &req, sizeof(struct printreq));
  if (nw != sizeof(struct printreq))
  {
    res.jobid = 0;
    if (nw < 0)
      res.retcode = htonl(errno);
    else
      res.retcode = htonl(EIO);
    log_msg("client_thtread: can't write %s: %s", name, strerror(res.retcode));
    close(fd);
    strncpy(res.msg, strerror(res.retcode), MSGLEN_MAX);
    writen(sockfd, &res, sizeof(struct printresp));
    unlink(name);
    sprintf(name, "%s/%s/%ld", SPOOLDIR, DATADIR, jobid);
    unlink(name);
    pthread_exit((void *)1);
  }
  clsoe(fd);
  res.retcode = 0;
  res.jobid = htonl(jobid);
  sprintf(res.msg, "reqeust ID %d", jobid);
  writen(sockfd, &res, sizeof(struct printresp));

  log_msg("adding job %d to queue", jobid);
  add_job(&req, jobid);
  pthread_cleanup_pop(1);
  return ((void *)0);
}

/**
 * Add a worker to the list of worker threads
*/
void add_worker(pthread_t tid, int sockfd)
{
  struct worker_thread *wtp;
  if ((wtp = malloc(sizeof(struct worker_thread))) == NULL)
  {
    log_ret("add_worker: can't malloc");
    pthread_exit((void *)1);
  }
  wtp->tid = tid;
  wtp->sockfd = sockfd;
  pthread_mutex_lock(&workerlock);
  wtp->prev = NULL;
  wtp->next = workers;
  if (workers != NULL)
    workers->prev = wtp;

  workers = wtp;
  pthread_mutex_unlock(&workerlock);
}

/**
 * Cancel (kill) all outstanding workers
*/
void kill_workers(void)
{
  struct worker_thread *wtp;
  pthread_mutex_lock(&workerlock);
  for (wtp = workers; wtp != NULL; wtp = wtp->next)
    pthread_cancel(wtp->tid);
  pthread_mutex_unlock(&workerlock);
}

/**
 * Cancellation routine for the worker thread
*/
void client_cleanup(void *arg)
{
  struct worker_thread *wtp;
  pthread_t tid;
  tid = (pthread_t)((long)arg);
  pthread_mutex_lock(&workerlock);
  for (wtp = workers; wtp != NULL; wtp = wtp->next)
  {
    if (wtp->tid == tid)
    {
      if (wtp->next != NULL)
        wtp->next->prev = wtp->prev;
      if (wtp->prev != NULL)
        wtp->prev->next = wtp->next;
      else
        workers = wtp->next;
      break;
    }
  }
  pthread_mutex_unlock(&workers);
  if (wtp != NULL)
  {
    close(wtp->sockfd);
    free(wtp);
  }
}

/**
 * Deal with signal
*/
void *signal_thread(void *arg)
{
  int err, signo;
  for (;;)
  {
    err = sigwait(&mask, &signo);
    if (err != 0)
      log_quit("sigwait failed: %s", strerror(err));
    switch (signo)
    {
    case SIGHUP:
      pthread_mutex_lock(&configlock);
      reread = 1;
      pthread_mutex_unlock(&configlock);
      break;
    case SIGTERM:
      kill_workers();
      log_msg("terminate with signal %s", strsignal(signo));
      exit(0);
    default:
      kill_workers();
      log_quit("unexpected signal %d", signo);
    }
  }
}

/**
 * Add an option to the IPP header
*/
char *add_option(char *cp, int tag, char *optname, char *optval)
{
  int n;
  union {
    int16_t s;
    char c[2];
  } u;
  *cp++ = tag;
  n = strlen(optname);
  u.s = htons(n);
  //保持对齐
  *cp++ = u.c[0];
  *cp++ = u.c[1];
  strcpy(cp, optname);
  cp += n;
  n = strlen(optval);
  u.s = htons(n);
  //保持对齐
  *cp++ = u.c[0];
  *cp++ = u.c[1];
  strcpy(cp, optval);
  return (cp + n);
}

/**
 * Single thread to communicate with the printer
*/
void *printer_thread(void *arg)
{
  struct job *jp;
  int hlen, ilen, sockfd, fd, nr, nw, extra;
  char *icp, *hcp, *p;
  struct ipp_hdr *hp;
  struct stat sbuf;
  struct iovec iov[2];
  char name[FILENMSZ];
  char hbuf[HBUFSZ]; /* http header */
  char ibuf[IBUFSZ]; /* ipc header */
  char buf[IOBUFSZ];
  char str[64];
  struct timespec ts = {60, 0};
  for (;;)
  {
    pthread_mutex_lock(&joblock);
    while (jobhead == NULL)
    {
      log_msg("printer_thread: waiting...");
      pthread_cond_wait(&jobwait, &joblock);
    }
    remove_job(jp = jobhead);
    log_msg("printer_thread: picked up job %d", jp->jobid);
    pthread_mutex_unlock(&joblock);
    update_jobno();
  }
}