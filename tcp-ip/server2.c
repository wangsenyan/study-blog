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
#include <poll.h>
#include "util.h"
#define SERV_TCP_PORT 8000
#define MAX_SIZE 80
//避免为每个客户创建一个新的进程的所有开销
int main(int argc, char *argv[])
{
  int port;
  int i, maxi, maxfd, listenfd, connfd, sockfd;
  int nready;
  ssize_t n;
  char buf[MAXLINE];
  socklen_t clilen;
  struct pollfd client[OPEN_MAX];
  struct sockaddr_in cliaddr, servaddr;

  if (argc == 2)
    sscanf(argv[1], "%d", &port);
  else
    port = SERV_TCP_PORT;
  if ((listenfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    perror("can't open stream socket");
    exit(1);
  }
  bzero((char *)&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  if (bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
  {
    perror("can't bind local address");
    exit(1);
  }

  listen(listenfd, LISTENQ);
  client[0].fd = listenfd;
  client[0].events = POLLRDNORM;
  for (i = 1; i < OPEN_MAX; i++)
    client[i].fd = -1;
  maxi = 0; //client数组当前正在使用的最大下标值
  //signal(SIGCHLD, sig_chld);
  for (;;)
  {
    nready = poll(client, maxi + 1, INFTIM);
    if (client[0].revents & POLLRDNORM) /*new client connection*/
    {
      clilen = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen);
      if (connfd < 0)
      {
        if (errno == EINTR)
          continue;
        else
        {
          perror("can't bind local address");
          exit(1);
        }
      }
      for (i = 1; i < OPEN_MAX; i++)
        if (client[i].fd < 0)
        {
          client[i].fd = connfd;
          break;
        }
      if (i == OPEN_MAX)
      {
        perror("too many clients");
        exit(1);
      }
      client[i].events = POLLRDNORM;
      if (i > maxi)
        maxi = i;
      if (--nready <= 0)
        continue;
    }
    for (i = 1; i <= maxi; i++) /*check all clients for data*/
    {
      if ((sockfd = client[i].fd) < 0)
        continue;
      if (client[i].revents & (POLLRDNORM | POLLERR))
      {
        if ((n = read(sockfd, buf, MAXLINE)) < 0)
        {
          if (errno == ECONNRESET)
          {
            close(connfd); //connectiuon reset by client
            client[i].fd = -1;
          }
          else
          {
            perror("read error");
            exit(1);
          }
        }
        else if (n == 0) //connection closed by client
        {
          close(sockfd);
          client[i].fd = -1;
        }
        else
          writen(sockfd, buf, n);
        if (--nready <= 0)
          break; /*no more readable descriptors*/
      }
    }
  }
}
