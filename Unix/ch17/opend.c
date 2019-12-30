#include "opend.h"
#include <fcntl.h>
#include "apue.h"
#define MAXARGC 50
#define WHITE " \t\n"
char errmsg[MAXLINE];
int oflag;
char *pathname;

int main(void)
{
  int nread;
  char buf[MAXLINE];
  for (;;)
  {
    if ((nread = read(STDOUT_FILENO, buf, MAXLINE)) < 0)
      err_sys("read error on stream pipe");
    else if (nread == 0)
      break;
    handle_request(buf, nread, STDOUT_FILENO);
  }
  exit(0);
}

void handle_request(char *buf, int nread, int fd)
{
  int newfd;
  if (buf[nread - 1] != 0)
  {
    snprintf(errmsg, MAXLINE - 1, "request not null terminated: %*.*s\n", nread, nread, buf);
    send_err(fd, -1, errmsg);
    return;
  }
  if (buf_args(buf, cli_args) < 0)
  {
    send_err(fd, -1, errmsg);
  }
  if ((newfd = open(pathname, oflag)) < 0)
  {
    snprintf(errmsg, MAXLINE - 1, "can't open %s: %s\n", pathname, strerror(errno));
    send_err(fd, -1, errmsg);
    return;
  }
  if (send_fd(fd, newfd) < 0)
    err_sys("send_fd error");
  close(newfd);
}

int buf_args(char *buf, int (*optfunc)(int, char **))
{
  char *ptr, *argv[MAXARGC];
  int argc;
  if (strtok(buf, WHITE) == NULL)
    return (-1);
  argv[argc = 0] = buf;
  while ((ptr = strtok(NULL, WHITE)) != NULL)
  {
    if (++argc >= MAXARGC - 1)
      return (-1);
    argv[argc] = ptr;
  }
  argv[++argc] = NULL;
  return ((*optfunc)(argc, argv));
}

int cli_args(int argc, char **argv)
{
  if (argc != 3 || strcmp(argv[0], CL_OPEN) != 0)
  {
    strcpy(errmsg, "usage: <pathname> <oflag>\n");
    return (-1);
  }
  pathname = argv[1];
  oflag = atoi(argv[2]);
  return (0);
}