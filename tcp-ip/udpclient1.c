//获取临时端口
#include <stdio.h>
#include <stdlib.h>
#include <string.h> //bzero
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/tcp.h>
#include "util.h"
#include "sock_ntop.h"
int main(int argc, char **argv)
{
  int sockfd;
  socklen_t len;
  struct sockaddr_in cliaddr, servaddr;

  if (argc != 2)
  {
    perror("usage: udpcli<IPaddress>");
    exit(1);
  }
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(8000);
  inet_pton(AF_INET, argv[1], &servaddr.sin_addr);

  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  len = sizeof(cliaddr);
  getsockname(sockfd, (struct sockaddr *)&cliaddr, &len);
  printf("local address %s\n", sock_ntop((struct sockaddr *)&cliaddr, len));
  exit(0);
}