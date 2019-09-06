#include <stdio.h>
#include <stdlib.h>
#include <string.h> //bzero
#include <sys/socket.h>
//#include <netinet/in.h> //sockaddr_in
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include "util.h"
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_in servaddr, cliaddr;
  sockfd = socket(AF_INET, SOCK_DGRAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(8000);

  bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)); //协议无关的
  dg_echo_calc(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}
