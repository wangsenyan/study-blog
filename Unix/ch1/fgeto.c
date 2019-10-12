#include "apue.h"

int main(void)
{
  int c;
  while ((c = getc(stdin)) != EOF) //获取单个字符
    if (putc(c, stdout) == EOF)
      err_sys("output error");
  if (ferror(stdin))
    err_sys("input error");
  exit(0);
}