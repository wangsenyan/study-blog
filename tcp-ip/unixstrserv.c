#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h> //inet_addr
#include <netinet/tcp.h>
#include <sys/unistd.h>
#include <sys/un.h> //struct sockaddr_un
#include <errno.h>
#include <signal.h>
#include "util.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  pid_t childpid;
  socklen_t clilen;
  struct sockaddr_un cliaddr, servaddr;
  void sig_chld(int);

  listenfd = socket(AF_LOCAL, SOCK_STREAM, 0);

  unlink(UNIXSTR_PATH);
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sun_family = AF_LOCAL;
  strcpy(servaddr.sun_path, UNIXSTR_PATH);
  bind(listenfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
  listen(listenfd, LISTENQ);

  signal(SIGCHLD, sig_chld);
  for (;;)
  {
    clilen = sizeof(cliaddr);
    if ((connfd = accept(listenfd, (struct sockaddr *)&cliaddr, &clilen)) < 0)
    {
      if (errno == EINTR)
        continue;
      else
        err_sys("accept error");
    }
    if ((childpid = fork()) == 0)
    {
      close(listenfd);
      str_echo(connfd);
      exit(0);
    }
    close(connfd);
  }
}