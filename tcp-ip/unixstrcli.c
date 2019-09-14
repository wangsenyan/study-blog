#include <stdio.h>
#include <stdlib.h>
#include <string.h>     //bzero strcpy
#include <sys/socket.h> //socket connect sockaddr
#include <sys/un.h>     //sockaddr_un
#include "util.h"
int main(int argc, char **argv)
{
  int sockfd;
  struct sockaddr_un servaddr;

  sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, UNIXSTR_PATH);

  connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  str_cli(stdin, sockfd);
  exit(0);
}