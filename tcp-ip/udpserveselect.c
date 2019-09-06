#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include <unistd.h> //fork
#include <signal.h> //signal
#include <errno.h>

#include "util.h"
int main(int argc, int **argv)
{
  int listenfd, connfd, udpfd, nready, maxfdp1;
  char mesg[MAXLINE];
  pid_t childpid;
  fd_set rset;
  ssize_t n;
  socklen_t len;
  const int on = 1;
  struct sockaddr_in cliaddr, servaddr;

  void sig_chld(int);

  listenfd = socket(AF_INET, SOCK_STREAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8000);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)); //防止该端口上已有连接存在
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);

  udpfd = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(8000);

  bind(udpfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

  signal(SIGCHLD, sig_chld); //会中断我们对select的调用所以处理EINTY错误
  FD_ZERO(&rset);
  maxfdp1 = MAX(listenfd, udpfd) + 1;
  for (;;)
  {
    FD_SET(listenfd, &rset);
    FD_SET(udpfd, &rset);
    if ((nready = select(maxfdp1, &rset, NULL, NULL, NULL)) < 0)
    {
      if (errno == EINTR)
        continue;
      else
      {
        perror("select error");
        exit(0);
      }
    }
    if (FD_ISSET(listenfd, &rset))
    {
      len = sizeof(cliaddr);
      connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);
      if ((childpid = fork()) == 0)
      {
        close(listenfd);
        str_echo(connfd);
        exit(0);
      }
      close(connfd);
    }
    if (FD_ISSET(udpfd, &rset))
    {
      len = sizeof(cliaddr);
      n = recvfrom(udpfd, mesg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
      sendto(udpfd, mesg, n, 0, (struct sockaddr *)&cliaddr, len);
    }
  }
}