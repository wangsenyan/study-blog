#include "apue.h"

int main(void)
{
  int n, int1, int2;
  char line[MAXLINE];
  // if (setvbuf(stdin, NULL, _IOLBF, 0) != 0)//当有一行可用时，fgets就返回
  //   err_sys("setvbuf error");
  // if (setvbuf(stdout, NULL, _IOLBF, 0) != 0)//当输入一个换行符时，printf立即执行fflush
  //   err_sys("setvbuf error");
  // while (fgets(line, MAXLINE, stdin) != NULL)//会分配缓冲区，并选择缓冲的类型，因标准输入是一个管道，所以标准I/O库默认是全缓冲的
  // {
  //   if (scanf(line, "%d%d", &int1, &int2) == 2)
  //   {
  //     if (printf("%d\n", int1 + int2) == EOF)
  //       err_sys("printf error");
  //   }
  //   else
  //   {
  //     if (printf("invalid args\n") == EOF)
  //       err_sys("printf error");
  //   }
  //   exit(0);
  // }
  while ((n = read(STDIN_FILENO, line, MAXLINE)) > 0)
  {
    line[n] = 0;
    // if (sscanf(line, "%*s%d%d", &int1, &int2) == 2)
    if (sscanf(line, "%d%d", &int1, &int2) == 2)
    {
      sprintf(line, "%d\n", int1 + int2);
      n = strlen(line);
      if (write(STDOUT_FILENO, line, n) != n)
        err_sys("write error");
    }
    else
    {
      //printf("%d %d\n", n, i);
      // if (write(STDOUT_FILENO, line, strlen(line)) != 13)
      if (write(STDOUT_FILENO, "invalid args\n", 13) != 13)
        err_sys("write error");
    }
  }
  exit(0);
}