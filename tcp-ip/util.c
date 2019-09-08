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
void str_echo(int sockfd)
{
  ssize_t n;
  char buf[MAXLINE];
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
// void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
// {
//   int n;
//   char sendline[MAXLINE], recvline[MAXLINE + 1];
//   while (fgets(sendline, MAXLINE, fp) != NULL)
//   {
//     sendto(sockfd, sendline, strlen(sendline), 0, pservaddr, servlen);
//     n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
//     recvline[n] = 0;
//     fputs(recvline, stdout);
//   }
// }

void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen)
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
    printf("tcp_connect error for %s, %s: %s", host, serv, gai_strerror(n));
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