#include <string.h>
#include <stdio.h>  //standard input/output
#include <stdlib.h> //standard library
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "apue.h"
#define SERV_TCP_PORT 8000
#define MAX_SIZE 80
#define LISTENQ 128
#define BUFLEN 128
//避免为每个客户创建一个新的进程的所有开销
int main(int argc, char *argv[])
{
  int port;
  int i, maxi, maxfd, listenfd, connfd, sockfd;
  FILE *fp;
  int nready, client[FD_SETSIZE];
  ssize_t n;
  fd_set rset, allset;
  char buf[MAXLINE];
  socklen_t clilen;
  struct sockaddr_in cliaddr, servaddr;

  if (argc == 2)
    sscanf(argv[1], "%d", &port);
  else
    port = SERV_TCP_PORT;
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_sys("can't open stream socket");

  bzero((char *)&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
    err_sys("can't bind local address");

  listen(listenfd, LISTENQ);
  maxfd = listenfd;
  maxi = -1;
  for (i = 0; i < FD_SETSIZE; i++)
    client[i] = -1;
  FD_ZERO(&allset);
  FD_SET(listenfd, &allset);

  //signal(SIGCHLD, sig_chld);
  for (;;)
  {
    rset = allset; /*structurer assignment*/
    nready = select(maxfd + 1, &rset, NULL, NULL, NULL);
    if (FD_ISSET(listenfd, &rset)) /*new client connection*/
    {
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
      if (connfd < 0)
      {
        if (errno == EINTR)
          continue;
        else
          err_sys("can't bind local address");
      }
      for (i = 0; i < FD_SETSIZE; i++)
      {
        if (client[i] < 0)
        {
          client[i] = connfd; /*save descriptor*/
          break;
        }
      }
      if (i == FD_SETSIZE)
        err_sys("too many clients");
      FD_SET(connfd, &allset);
      if (connfd > maxfd)
        maxfd = connfd;
      if (i > maxi)
        maxi = i; /*max index in client[] array*/
      if (--nready == 0)
        continue; /*no more readable descriptore*/
    }
    for (i = 0; i <= maxi; i++) /*check all clients for data*/
    {
      if ((sockfd = client[i]) < 0)
        continue;
      if (FD_ISSET(sockfd, &rset))
      {
        if ((n = read(sockfd, buf, MAXLINE)) == 0)
        {
          close(sockfd);
          FD_CLR(sockfd, &allset);
          client[i] = -1;
        }
        else //此处获取进程数
        {
          if ((fp = popen("ps -ef| wc -l", "r")) == NULL)
          {
            sprintf(buf, "error:%s\n", strerror(errno));
            write(sockfd, buf, n);
          }
          else
          {
            while (fgets(buf, BUFLEN, fp) != NULL)
              write(sockfd, buf, strlen(buf));
            pclose(fp);
          }
        }
        if (--nready <= 0)
          break; /*no more readable descriptors*/
      }
    }
  }
}
