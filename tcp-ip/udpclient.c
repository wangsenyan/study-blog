#include <stdio.h>
#include <stdlib.h>
#include <string.h> //bzero
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "util.h"
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr;
  if (argc != 2)
  {
    perror("usage:udpclient <IPaddress>");
    exit(1);
  }
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8000);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  exit(0);
}