#include "apue.h"
#include <fcntl.h>
#define PATH "/dev/fd/1"
int main(void)
{
  int fd;
  unlink(PATH);
  if ((fd = creat(PATH, FILE_MODE)) < 0)
    err_sys("creat failed");
  exit(0);
}