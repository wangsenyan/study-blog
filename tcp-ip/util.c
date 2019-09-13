#include <unistd.h>
#include <errno.h>
#include <stdlib.h> //exit
#include <stdio.h>  //peeor
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "util.h"
#include "sock_ntop.h"
#include <netdb.h>
#include <syslog.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/devpoll.h>
int daemon_proc;
void str_echo(int sockfd)
{
  ssize_t n;
  char buf[MAXLINE];
  // write(sockfd, "hello world", sizeof("hello world"));
again:
  while ((n = read(sockfd, buf, MAXLINE)) > 0)
    write(sockfd, buf, n);
  if (n < 0 && errno == EINTR)
    goto again;
  else if ((n < 0))
  {
    perror("str_echo:read error");
    exit(1);
  }
}

//int snprintf(char *str, int n, char * format [, argument, ...]);
//字符串传递参数
// void str_echo(int sockfd)
// {
// 	long arg1,arg2;
// 	ssize_t n;
// 	char line[MAXLINE];
// 	for(;;){
// 		if((n=readline(sockfd,line,MAXLINE))==0)
// 			return;
// 		if(sscanf(line,"%ld%ld",&arg1,&arg2)==2)
// 			snprintf(line,sizeof(line),"%ld\n",arg1+arg2);
// 	    else
// 	    	snprintf(line,sizeof(line),"input error\n");
// 	    n=strlen(line);
// 	    write(sockfd,line,n);
// 	}
// }
//二进制传递数据
// void str_echo(int sockfd)
// {
//   ssize_t n;
//   struct args args;
//   struct result result;
//   char line[MAXLINE];
//   for (;;)
//   {
//     if ((n = readn(sockfd, &args, sizeof(args))) == 0)
//       return;
//     result.sum = args.arg1 + args.arg2;
//     write(sockfd, &result, sizeof(result));
//   }
// }
// void str_cli(FILE *fp,int sockfd)
// {
// 	char sendline[MAXLINE],recvline[MAXLINE];
// 	while(fgets(sendline,MAXLINE,fp)!=NULL){
// 		//writen(sockfd,sendline,1);
// 		//sleep(1);
// 		//writen(sockfd,sendline+1,strlen(sendline)-1);
// 		writen(sockfd,sendline,strlen(sendline));
// 		if(readline(sockfd,recvline,MAXLINE)==0)
// 		{
// 			perror("str_cli:server terminated prematurely");
// 			exit(0);
// 		}
// 		fputs(recvline,stdout);
// 	}
// }

//传递二进制
// void str_cli(FILE *fp,int sockfd)
// {
// 	char sendline[MAXLINE];
// 	struct args args;
// 	struct result result;

// 	while(fgets(sendline,MAXLINE,fp)!=NULL){
//         if(sscanf(sendline,"%ld%ld",&args.arg1,&args.arg2)!=2){
//         	printf("invalid input: %s",sendline);
//         	continue;
//         }
// 		writen(sockfd,&args,sizeof(args));
// 		if(readn(sockfd,&result,sizeof(result))==0)
// 		{
// 			perror("str_cli:server terminated prematurely");
// 			exit(0);
// 		}
// 		printf("%ld\n",result.sum);
// 	}
// }

//可复用I/O
// void str_cli(FILE *fp, int sockfd)
// {
//   int maxfdp1;
//   fd_set rset;
//   char sendline[MAXLINE], recvline[MAXLINE];

//   FD_ZERO(&rset);
//   for (;;)
//   {
//     FD_SET(fileno(fp), &rset);
//     FD_SET(sockfd, &rset);
//     maxfdp1 = MAX(fileno(fp), sockfd) + 1;
//     select(maxfdp1, &rset, NULL, NULL, NULL);

//     if (FD_ISSET(sockfd, &rset))
//     {
//       if (readline(sockfd, recvline, MAXLINE) == 0)
//       {
//         perror("str_cli:server terminated prematurely");
//         exit(0);
//       }
//       fputs(recvline, stdout);
//     }
//     if (FD_ISSET(fileno(fp), &rset))
//     {
//       if (fgets(sendline, MAXLINE, fp) == NULL)
//         return;
//       writen(sockfd, sendline, strlen(sendline));
//     }
//   }
// }

//优化可复用I/O 问题 不能终止客户端
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

ssize_t readn(int fd, void *vptr, size_t n)
{
  size_t nleft;
  ssize_t nread;
  char *ptr;
  ptr = vptr;
  nleft = n;
  while (nleft > 0)
  {
    if ((nread = read(fd, ptr, nleft)) < 0)
    {
      if (errno == EINTR)
        nread = 0;
      else
        return (-1);
    }
    else if (nread == 0)
      break; //EOF
    nleft -= nread;
    ptr += nread;
  }
  return (n - nleft);
}
//读取一行数据
ssize_t readline(int fd, void *vptr, size_t maxlen)
{
  ssize_t n, rc;
  char c, *ptr;
  ptr = vptr;
  for (n = 1; n < maxlen; n++)
  {
  again:
    if ((rc = (fd, &c, 1)) == 1)
    {
      *ptr++ = c;
      if (c == '\n')
        break;
    }
    else if (rc == 0)
    {
      *ptr = 0;
      return (n - 1);
    }
    else
    {
      if (errno == EINTR)
        goto again;
      return (-1);
    }
  }
  *ptr = 0;
  return (n);
}

Sigfunc *signal(int signo, Sigfunc *func)
{
  struct sigaction act;
  struct sigaction oact;
  act.sa_handler = func;
  sigemptyset(&act.sa_mask); //ÉèÖÃÎª¿Õ¼¯£¬ÔÚÐÅºÅ´¦Àíº¯ÊýÔËÐÐÆÚ¼ä²»×èÈû¶îÍâµÄÐÅºÅ
  act.sa_flags = 0;
  if (signo == SIGALRM)
  {
#ifdef SA_INTERRUPT
    act.sa_flags |= SA_INTERRUPT;
#endif
  }
  else
  {
#ifdef SA_RESTART
    act.sa_flags |= SA_RESTART;
#endif
  }
  if (sigaction(signo, &act, &oact) < 0)
    return (SIG_ERR);
  return (oact.sa_handler);
}

void sig_chld(int signal)
{
  pid_t pid;
  int stat;
  //pid = wait(&stat);//waitÈ¡µ½×Ó½ø³ÌµÄpidºÍÖÕÖ¹×´Ì¬
  while ((pid = waitpid(-1, &stat, WNOHANG)) > 0)
    printf("child %d terminated\n", pid);
  return;
}

void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
  int n;
  socklen_t len;
  char mesg[MAXLINE];
  for (;;)
  {
    len = clilen;
    n = recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
    sendto(sockfd, mesg, n, 0, pcliaddr, len);
  }
}

void dg_echo_calc(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen)
{
  int n;

  socklen_t len;
  char mesg[MAXLINE];
  signal(SIGINT, recvfrom_int);

  n = 220 * 1024;
  setsockopt(sockfd, SOL_SOCKET, SO_RCVBUF, &n, sizeof(n)); //设置套接字缓冲区大小

  for (;;)
  {
    len = clilen;
    recvfrom(sockfd, mesg, MAXLINE, 0, pcliaddr, &len);
    count++;
  }
}

static void recvfrom_int(int signc)
{
  printf("\nreceived %d datagrams\n", count);
  exit(0);
}
//不保留服务器端？
static void sig_alarm(int signo)
{
  return;
}

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  signal(SIGALRM, sig_alarm);
  while (fgets(sendline, MAXLINE, fp) != NULL)
  {
    sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
    alarm(5);
    if((n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL))<0)
    {
      if(errno==EINTR)
        fprintf(stderr, "socket timeout\n");
      else
        err_sys("recvfrom error");
    }else{
      alarm(0);
      recvline[n] = 0;
      fputs(recvline, stdout);
    }
    //n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
  }
}

void dg_cli_pri(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  socklen_t len;
  struct sockaddr *preply_addr;
  preply_addr = malloc(servlen);
  while (fgets(sendline, MAXLINE, fp) != NULL)
  {
    sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
    len = servlen;
    n = recvfrom(sockfd, recvline, MAXLINE, 0, preply_addr, &len);
    if (len != servlen || memcmp(pservaddr, preply_addr, len) != 0)
    {
      printf("reply from %s (ignore)\n", sock_ntop(preply_addr, len));
      continue;
    }
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
}

void dg_cli_conn(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];

  connect(sockfd, (struct sockaddr *)pservaddr, servlen);
  while (fgets(sendline, MAXLINE, fp) != NULL)
  {

    write(sockfd, sendline, strlen(sendline));
    n = read(sockfd, recvline, MAXLINE);
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
}

void dg_cli_bigdata(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
{
  int i;
  char sendline[DGLEN];
  for (i = 0; i < NDG; i++)
  {
    sendto(sockfd, sendline, DGLEN, 0, pservaddr, servlen);
  }
}

int tcp_connect(const char *host, const char *serv)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;
  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
  {
    printf("tcp_connect error for %s, %s: %s\n", host, serv, gai_strerror(n));
    exit(0);
  }
  ressave = res;
  do
  {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue;
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;
    close(sockfd);
  } while ((res = res->ai_next) != NULL);
  if (res == NULL)
    printf("tcp_connect error for %s,  %s", host, serv);
  freeaddrinfo(ressave);
  return (sockfd);
}

int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp)
{
  int listenfd, n;
  const int on = 1;
  struct addrinfo hints, *res, *ressave;
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_STREAM;

  if ((n = getaddrinfo(host, serv, &hints, &res)) != 0)
  {
    printf("tcp_listen error for %s, %s: %s\n", host, serv, gai_strerror(n));
    exit(0);
  }
  ressave = res;
  do
  {
    listenfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (listenfd < 0)
      continue;
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); //重复绑定
    if (bind(listenfd, res->ai_addr, res->ai_addrlen) == 0)
      break;
    close(listenfd);
  } while ((res = res->ai_next) != NULL);
  if (res == NULL)
  {
    printf("tcp_listen error for %s, %s\n", host, serv);
  }
  listen(listenfd, LISTENQ);
  if (addrlenp)
    *addrlenp = res->ai_addrlen;
  freeaddrinfo(ressave);
  return (listenfd);
}

int udp_client(const char *hostname, const char *service, struct sockaddr **saptr, socklen_t *lenp)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;

  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
  {
    printf("udp_client error for %s, %s: %s\n", hostname, service, gai_strerror(n));
    exit(0);
  }
  ressave = res;
  do
  {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd >= 0)
      break;
  } while ((res = res->ai_next) != NULL);
  if (res == NULL)
  {
    printf("udp_client error for %s, %s\n", hostname, service);
  }
  *saptr = malloc(res->ai_addrlen);
  memcpy(*saptr, res->ai_addr, res->ai_addrlen);
  *lenp = res->ai_addrlen;

  freeaddrinfo(ressave);
  return (sockfd);
}

int udp_connect(const char *hostname, const char *service)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;
  if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
  {
    printf("udp_connect error for %s, %s: %s", hostname, service, gai_strerror(n));
    exit(0);
  }
  ressave = res;
  do
  {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue;
    if (connect(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;
    close(sockfd);
  } while ((res = res->ai_next) != NULL);
  if (res == NULL)
    printf("udp_connect error for %s, %s", hostname, service);
  freeaddrinfo(ressave);
  return (sockfd);
}

int udp_server(const char *hostname, const char *service, socklen_t *lenptr)
{
  int sockfd, n;
  struct addrinfo hints, *res, *ressave;
  bzero(&hints, sizeof(struct addrinfo));
  hints.ai_flags = AI_PASSIVE;
  hints.ai_family = AF_UNSPEC;
  hints.ai_socktype = SOCK_DGRAM;

  if ((n = getaddrinfo(hostname, service, &hints, &res)) != 0)
  {
    printf("udp_server error for %s, %s: %s\n", hostname, service, gai_strerror(n));
    exit(0);
  }
  ressave = res;
  do
  {
    sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (sockfd < 0)
      continue;
    if (bind(sockfd, res->ai_addr, res->ai_addrlen) == 0)
      break;
    close(sockfd);
  } while ((res = res->ai_next) != NULL);
  if (res == NULL)
    printf("udp_server error for %s, %s", hostname, service);
  if (lenptr)
    *lenptr = res->ai_addrlen;
  freeaddrinfo(ressave);
  return (sockfd);
}

int deamon_init(const char *pname, int facility)
{
  int i;
  pid_t pid;

  if ((pid = fork()) < 0)
    return (-1);
  else if (pid)
    _exit(0);

  if (setsid() < 0)
    return (-1);

  signal(SIGHUP, SIG_IGN);
  //再次fork目的:确保本守护进程将来即使打开一个终端，也不会自动获得控制终端
  if ((pid = fork()) < 0)
    return (-1);
  else if (pid)
    _exit(0);

  daemon_proc = 1;
  chdir("/");
  for (i = 0; i < MAXFD; i++)
    close(i);
  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);
  openlog(pname, LOG_PID, facility);
  return (0);
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

int connect_timeo(int sockfd,const struct sockaddr *saptr,socklen_t salen,int nsec)
{
  Sigfunc *sigfunc;
  int n;
  sigfunc = signal(SIGALRM, connect_alarm);
  if(alarm(nsec)!=0)
    err_msg("connect_timeo: alarm war already set");
  if((n=connect(sockfd,saptr,salen))<0){
    close(sockfd);
    if(errno==EINTR)
      errno = ETIMEDOUT;
  }
  alarm(0);
  signal(SIGALRM, sigfunc);
  return (n);
}

static void connect_alarm(int signo)
{
  return;
}

//返回：出错时为-1，超时发生时为0，否则返回正值给出已就绪描述符的数目
int readable_timeo(int fd,int sec)
{
  fd_set rset;
  struct timeval tv;
  FD_ZERO(&rset);
  FD_SET(fd, &rset);
  tv.tv_sec = sec;
  tv.tv_usec = 0;
  return (select(fd + 1, &rset, NULL, NULL, NULL));
}

//为单个套接字设置select
void dg_cli_select(FILE *fp,int sockfd,const struct sockaddr *pservaddr,socklen_t servlen)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  while (fgets(sendline,MAXLINE,fp)!=NULL)
  {
    sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
    if(readable_timeo(sockfd,5)==0)
      fprintf(stderr, "socket timeout\n");
    else{
      n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
      recvline[n] = 0;
      fputs(recvline, stdout);
    }
  }
}

void dg_cli_so(FILE *fp,int sockfd,const struct sockaddr *pservaddr,socklen_t servlen)
{
  int n;
  char sendline[MAXLINE], recvline[MAXLINE + 1];
  struct timeval tv;
  tv.tv_sec = 5;
  tv.tv_usec = 0;
  setsockopt(sockfd, SOL_SOCKET, SO_RCVTIMEO, &tv, sizeof(tv));
  while (fgets(sendline,MAXLINE,fp)!=NULL)
  {
    sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
    n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
    if(n < 0){
      if(errno==EWOULDBLOCK){
        fprintf(stderr, "socket timeout\n");
        continue;
      }else
        err_sys("recvfrom error");
    }
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
  
}
// /dev/poll tcp 
void str_cli_poll(FILE *fp,int sockfd)
{
  int stdineof;
  char buf[MAXLINE];
  int n;
  int wfd;
  struct pollfd pollfd[2];
  struct dvpoll dopoll;
  int i;
  int result;

  wfd = open("dev/poll", O_RDWR, 0);
  pollfd[0].fd = fileno(fp);
  pollfd[0].events = POLLIN;
  pollfd[0].revents = 0;

  pollfd[1].fd = sockfd;
  pollfd[1].events = POLLIN;
  pollfd[1].revents = 0;

  write(wfd, pollfd, sizeof(struct pollfd) * 2);

  stdineof = 0;
  for (;;)
  {
    dopoll.dp_timeout = -1;
    dopoll.dp_nfds = 2;
    dopoll.dp_fds = pollfd;

    result = ioctl(wfd, DP_POLL, &dopoll);
    for (i = 0; i < result;i++)
    {
      if(dopoll.dp_fds[i].fd == sockfd){
         if((n=read(sockfd,buf,MAXLINE))==0){
           if(stdineof==1)
             return;
            else
              err_quit("str_cli_poll:server terminated prematurely");
         }
         write(fileno(fp), buf, n);
      }else{
        if((n=read(fileno(fp),buf,MAXLINE))==0)
        {
          stdineof = 1;
          shutdown(sockfd, SHUT_WR);
          continue;
        }
        writen(sockfd, buf, n);
      }
    }
  }
}