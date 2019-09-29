#include "util.h"

int main(int argc, char **argv)
{
  int listenfd, connfd;
  pid_t childpid;
  void sig_chld(int), sig_int(int), web_child(int);
  socklen_t clilen, addrlen;
  struct sockaddr *cliaddr;

  if (argc == 2)
    listenfd = tcp_listen(NULL, argv[1], &addrlen);
  else if (argc == 3)
    listenfd = tcp_listen(argv[1], argv[2], &addrlen);
  else
    err_quit("usage:serv01 [<host>|<port#>]");
  cliaddr = malloc(addrlen);
  signal(SIGCHLD, sig_chld);
  signal(SIGINT, sig_int);
  for (;;)
  {
    clilen = addrlen;
    if ((connfd = accept(listenfd, cliaddr, &clilen)) < 0)
    {
      if (errno == EINTR)
        continue;
      else
        err_sys("accept error");
    }
    if ((childpid = fork()) == 0)
    {
      close(listenfd);
      web_child(connfd);
      exit(0);
    }
    close(connfd);
  }
}