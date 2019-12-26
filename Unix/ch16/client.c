#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h> //read write
#include <errno.h>
#include "apue.h"
#define SERV_TCP_PORT 8000

int main(int argc, char *argv[])
{
  int sockfd;
  //int i,sockfd[5];
  struct sockaddr_in serv_addr;
  char *serv_host = "localhost";
  struct hostent *host_ptr;
  int port;
  int buff_size = 0;
  char *msg;
  if (argc >= 2)
    serv_host = argv[1];
  if (argc >= 3)
    sscanf(argv[2], "%d", &port);
  if (argc > 3)
    msg = argv[3];
  else
    port = SERV_TCP_PORT;

  if ((host_ptr = gethostbyname(serv_host)) == NULL)
    err_sys("gethostbyname error");

  if (host_ptr->h_addrtype != AF_INET)
    err_sys("gethostbyname error");

  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = ((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
  serv_addr.sin_port = htons(port);

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    err_sys("can't open stream socket,%s", strerror(errno));

  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    err_sys("can't connect to server");
  str_cli(stdin, sockfd);
  exit(0);
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