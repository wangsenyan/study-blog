#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/unistd.h>
#include <sys/un.h>
#include "util.h"

int main(int argc, char *argv)
{
  int sockfd;
  struct sockaddr_un cliaddr, servaddr;

  sockfd = socket(AF_LOCAL, SOCK_DGRAM, 0);

  unlink(UNIXSTR_PATH);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, UNIXSTR_PATH);

  bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  dg_echo(sockfd, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
}