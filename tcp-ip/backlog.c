#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include "util.h"
#define PORT 9999
#define ADDR "127.0.0.1"
#define MAXBACKLOG 1000

struct sockaddr_in serv;
pid_t pid;
int pipefd[2];
#define pfd pipefd[1]
#define cfd pipefd[0]

void do_parent(void);
void do_child(void);

int main(int argc, char **argv)
{
  if (argc != 1)
    err_quit("usage: backlog");
  socketpair(AF_UNIX, SOCK_STREAM, 0, pipefd);

  bzero(&serv, sizeof(serv));
  serv.sin_family = AF_INET;
  serv.sin_port = htons(PORT);
  inet_pton(AF_INET, ADDR, &serv.sin_addr);
  if ((pid = fork()) == 0)
    do_parent();
  else
    do_child();
  exit(0);
}

void parent_alrm(int signo)
{
  return;
}

void do_parent(void)
{
  int backlog, j, k, junk, fd[MAXBACKLOG + 1];
  close(cfd);
  signal(SIGALRM, parent_alrm);

  for (backlog = 0; backlog <= 14; backlog++)
  {
    printf("backlog = %d: ", backlog);
    write(pfd, &backlog, sizeof(int));
    read(pfd, &junk, sizeof(int));

    for (j = 1; j <= MAXBACKLOG; j++)
    {
      fd[j] = socket(AF_INET, SOCK_STREAM, 0);
      alarm(2);
      if (connect(fd[j], (struct sockaddr *)&serv, sizeof(serv)) < 0)
      {
        if (errno != EINTR)
          err_sys("connect error,j = %d", j);
        printf("timeout, %d connections completed \n", j - 1);
        for (k = 1; k <= j; k++)
          close(fd[k]);
        break;
      }
      alarm(0);
    }
    if (j > MAXBACKLOG)
      printf("%d connections?\n", MAXBACKLOG);
  }
  backlog = -1;
  write(pfd, &backlog, sizeof(int));
}

void do_child(void)
{
  int listenfd, backlog, junk;
  const int on = 1;
  close(pfd);
  read(cfd, &backlog, sizeof(int));
  while (backlog >= 0)
  {
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));
    bind(listenfd, (struct sockaddr *)&serv, sizeof(serv));
    listen(listenfd, backlog);
    write(cfd, &junk, sizeof(int));
    read(cfd, &backlog, sizeof(int));
    close(listenfd);
  }
}