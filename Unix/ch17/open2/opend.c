#include "opend.h"
#include <sys/select.h>

#define NALLOC 10
#define MAXARGC 50
#define WHITE " \t\n"
static void client_alloc(void)
{
  int i;
  if (client == NULL)
    client = malloc(NALLOC * sizeof(Client));
  else
    client = realloc(client, (client_size + NALLOC) * sizeof(Client));
  if (client == NULL)
    err_sys("can't alloc for client array");

  for (i = client_size; i < client_size + NALLOC; i++)
    client[i].fd = -1;
  client_size += NALLOC;
}

int client_add(int fd, uid_t uid)
{
  int i;
  if (client == NULL)
    client_alloc();
again:
  for (i = 0; i < client_size; i++)
  {
    if (client[i].fd == -1)
    {
      client[i].fd = fd;
      client[i].uid = uid;
      return (i);
    }
  }
  client_alloc();
  goto again;
}

void client_del(int fd)
{
  int i;
  for (i = 0; i < client_size; i++)
  {
    if (client[i].fd == fd)
    {
      client[i].fd = -1;
      return;
    }
  }
  log_quit("can't find client entry for fd %d", fd);
}

void loop(void)
{
  int i, n, maxfd, maxi, listenfd, clifd, nread;
  char buf[MAXLINE];
  uid_t uid;
  fd_set rset, allset;
  FD_ZERO(&allset);

  if ((listenfd = serv_listen(CS_OPEN)) < 0)
    log_sys("serv_listen error");
  FD_SET(listenfd, &allset);
  maxfd = listenfd;
  maxi = -1;

  for (;;)
  {
    rset = allset;
    if ((n = select(maxfd + 1, &rset, NULL, NULL, NULL)) < 0)
      log_sys("select error");
    if (FD_ISSET(listenfd, &rset))
    {
      fprintf(stderr, "listenfd %d\n", listenfd);
      if ((clifd = serv_accept(listenfd, &uid)) < 0)
        log_sys("serv_accept error: %d", clifd);
      i = client_add(clifd, uid);
      FD_SET(clifd, &allset);
      if (clifd > maxfd)
        maxfd = clifd;
      if (i > maxi)
        maxi = i;
      log_msg("new connection: uid %d,fd %d", uid, clifd);
      continue;
    }
    for (i = 0; i <= maxi; i++)
    {
      if ((clifd = client[i].fd) < 0)
        continue;
      if (FD_ISSET(clifd, &rset))
      {
        if ((nread = read(clifd, buf, MAXLINE)) < 0)
          log_sys("read error on fd %d", clifd);
        else if (nread == 0)
        {
          log_msg("closed: uid %d,  fd %d", client[i].uid, clifd);
          client_del(clifd);
          FD_CLR(clifd, &allset);
          close(clifd);
        }
        else
        {
          handle_request(buf, nread, clifd, client[i].uid);
        }
      }
    }
  }
}

void handle_request(char *buf, int nread, int clifd, uid_t uid)
{
  int newfd;
  if (buf[nread - 1] != 0)
  {
    snprintf(errmsg, MAXLINE - 1, "request from uid %d not null terminated: %*.*s\n", uid, nread, nread, buf);
    send_err(clifd, -1, errmsg);
    return;
  }
  log_msg("request: %s,from uid %d", buf, uid);
  if (buf_args(buf, cli_args) < 0)
  {
    send_err(clifd, -1, errmsg);
    log_msg(errmsg);
    return;
  }
  if ((newfd = open(pathname, oflag)) < 0)
  {
    snprintf(errmsg, MAXLINE - 1, "can't open %s: %s\n", pathname, strerror(errno));
    send_err(clifd, -1, errmsg);
    log_msg(errmsg);
    return;
  }
  if (send_fd(clifd, newfd) < 0)
    log_sys("send_fd error");
  log_msg("send fd %d over fd %d for %s", newfd, clifd, pathname);
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