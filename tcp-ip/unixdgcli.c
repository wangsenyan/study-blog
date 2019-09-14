#include <string.h>
#include <stdio.h>  //stdin
#include <stdlib.h> //exit
#include <sys/un.h>
#include <sys/socket.h>
#include <sys/unistd.h> //unlink
#include "util.h"
int main(int argc, char *argv)
{
  int sockfd;

  struct sockaddr_un servaddr, cliaddr;
  sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);
  bzero(&cliaddr, sizeof(cliaddr));
  cliaddr.sun_family = AF_LOCAL;
  strcpy(cliaddr.sun_path, tmpnam(NULL));
  bind(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, UNIXSTR_PATH);

  dg_cli(stdin, sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  exit(0);
}