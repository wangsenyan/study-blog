#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
// #include <sys/types.h>
#include "util.h"
int main(int argc, char **argv)
{
  int fd, n;
  char buff[BUFSIZE];
  if (argc != 2)
    err_quit("usage: mycat <pathname>");
  if ((fd = my_open(argv[1], O_RDONLY)) < 0)
    err_sys("cannot open %s", argv[1]);
  while ((n = read(fd, buff, BUFSIZE)) > 0)
    write(STDOUT_FILENO, buff, n);
  exit(0);
}