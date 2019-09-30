#include "util.h"

pid_t child_make(int i, int listenfd, int addrlen)
{
  int sockfd[2];
  pid_t pid;
  void child_main(int, int, int);

  socketpair(AF_LOCAL, SOCK_STREAM, 0, sockfd);
  if ((pid = fork()) > 0)
  {
    close(sockfd[1]);
    cptr[i].child_pid = pid;
    cptr[i].child_pipefd = sockfd[0];
    cptr[i].child_status = 0;
    return (pid);
  }
  dup2(sockfd[1], STDERR_FILENO);
  close(sockfd[0]);
  close(sockfd[1]);
  close(listenfd);
  child_main(i, listenfd, addrlen);
}
void child_main(int i, int listenfd, int addrlen)
{
  char c;
  int connfd;
  ssize_t n;
  void web_child(int);
  printf("child %ld starting\n", (long)getpid());

  for (;;)
  {
    if ((n = read_fd(STDERR_FILENO, &c, 1, &connfd)) == 0)
      err_quit("read_fd returned 0");
    if (connfd < 0)
      err_quit("no descripter  from read_fd");
    web_child(connfd);
    close(connfd);
    write(STDERR_FILENO, "", 1);
  }
}