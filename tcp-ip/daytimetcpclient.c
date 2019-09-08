#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> //inet_aton
#include "util.h"
#include "sock_ntop.h"

int main(int argc, char **argv)
{
  int sockfd, n;
  char recvline[MAXLINE];
  socklen_t len;
  struct sockaddr_storage ss;
  if (argc != 3)
  {
    perror("usage: daytimetcpclient <hostname/IPaddress> <service/port#>");
    exit(0);
  }
  sockfd = tcp_connect(argv[1], argv[2]);
  len = sizeof(ss);
  getpeername(sockfd, (struct sockaddr *)&ss, &len);
  printf("connected to %s\n", sock_ntop((struct sockaddr *)&ss, len));

  while ((n = read(sockfd, recvline, MAXLINE)) > 0)
  {
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
  exit(0);
}