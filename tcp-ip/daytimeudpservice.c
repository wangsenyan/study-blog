#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <arpa/inet.h>
#include "util.h"
#include "sock_ntop.h"

int main(int argc, char **argv)
{
  int sockfd;
  ssize_t n;
  char buff[MAXLINE];
  time_t ticks;
  socklen_t len;
  struct sockaddr_storage cliaddr;
  if (argc == 2)
    sockfd = udp_server(NULL, argv[1], NULL);
  else if (argc == 3)
    sockfd = udp_server(argv[1], argv[2], NULL);
  else
  {
    perror("Usage:daytimeudpservice [<host>]<service or port>");
    exit(0);
  }
  for (;;)
  {
    len = sizeof(cliaddr);
    n = recvfrom(sockfd, buff, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);
    printf("datagram from %s\n", sock_ntop((struct sockaddr *)&cliaddr, len));
    ticks = time(NULL);
    snprintf(buff, sizeof(buff), "%.24s\r\n", ctime(&ticks));
    sendto(sockfd, buff, sizeof(buff), 0, (struct sockaddr *)&cliaddr, len);
  }
}