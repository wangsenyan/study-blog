#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include "util.h"
#include "sock_ntop.h"
int main(int argc, char **argv)
{
  int sockfd, n;
  char recvline[MAXLINE];
  socklen_t salen;
  struct sockaddr *sa;
  if (argc != 3)
  {
    perror("usage: daytimeudpclient <hostname/IPaddress> <service/port#>");
    exit(0);
  }
  sockfd = udp_client(argv[1], argv[2], (struct sockaddr **)&sa, &salen);
  printf("sending to %s\n", sock_ntop(sa, salen));
  sendto(sockfd, "", 1, 0, sa, salen);
  n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
  recvline[n] = '\0';
  fputs(recvline, stdout);
  exit(0);
}