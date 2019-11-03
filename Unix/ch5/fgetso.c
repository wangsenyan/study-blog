#include "apue.h"
#if defined MAXLINE
#undef MAXLINE
#define MAXLINE 4
#endif

int main(void)
{
  char buf[MAXLINE];
  while (fgets(buf, MAXLINE, stdin) != NULL)
    if (fputs(buf, stdout) == EOF)
      err_sys("output error");
  if (ferror(stdin))
    err_sys("input error");
  exit(0);
}