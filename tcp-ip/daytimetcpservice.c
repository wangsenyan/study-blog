#include <time.h>
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
#include "util.h"
#include "sock_ntop.h"
int main(int argc, char **argv)
{
  int listenfd, connfd;
  socklen_t len;
  char buff[MAXLINE];
  time_t ticks;
  struct sockaddr_storage cliaddr;

  if (argc != 2)
  {
    perror("usage: daytimetcpservice <service or port#>");
    exit(0);
  }
  listenfd = tcp_listen(NULL, argv[1], NULL);

  for (;;)
  {
    len = sizeof(cliaddr);
    connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &len);

    printf("connection from %s\n", sock_ntop((struct sockaddr *)&cliaddr, len));
    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    write(connfd, buff, strlen(buff));
    close(connfd);
  }
}