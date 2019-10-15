#include "apue.h"
#include <fcntl.h>

char buf1[] = "abcdefghij";
char buf2[] = "ABCDEFGHIJ";

int main(void)
{
  int fd;
  char buf3[16394];
  for (int i = 0; i < 16394; i++)
    buf3[i] = 'a';
  if ((fd = creat("file.hole", FILE_MODE)) < 0)
    err_sys("creat error");
  if (write(fd, buf1, 10) != 10)
    err_sys("buf1 write error");
  if (lseek(fd, 16384, SEEK_SET) == -1)
    err_sys("lseek error");
  if (write(fd, buf2, 10) != 10)
    err_sys("buf2 write error");

  if ((fd = creat("file.nohole", FILE_MODE)) < 0)
    err_sys("creat error");
  if (write(fd, buf3, 16394) != 16394)
    err_sys("buf1 write error");
  exit(0);
}