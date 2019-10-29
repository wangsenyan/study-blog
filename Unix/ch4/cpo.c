#include "apue.h"

#ifndef BUFSIZE
#define BUFSIZE 4096
#endif

static int iszeros(char *buf, int len)
{
  int i;
  for (i = 0; i < len; i++)
    if (buf[i] != 0)
      return 0;
  return 1;
}

int main(int argc, char *argv[])
{
  ssize_t nread, nwrite;
  char *buf;
  size_t len = BUFSIZ;
  struct stat st;
  if (fstat(STDIO_FILENO, &st) != 0)
    perror("fstat");
  else
    len = st.st_blksize;
  if ((buf = (char *)malloc(len)) == NULL)
  {
    perror("malloc error");
    exit(-1);
  }
  while ((nread = read(STDIN_FILENO, buf, len)) > 0)
  {
    if (iszeros(buf, len))
    {
      if (lseek(STDOUT_FILENO, len, SEEK_CUR) < 0)
      {
        perror("seek error");
        exit(-1);
      }
      continue;
    }
    if ((nwrite = write(STDOUT_FILENO, buf, nread)) < 0)
    {
      perror("write error");
      exit(-1);
    }
  }
  free(buf);
  return 0;
}