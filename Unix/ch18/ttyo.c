#include "apue.h"
#include <stdio.h>
#include <string.h>
#include <termios.h>
//static char ctermid_name[L_ctermid];
// extern char cterm
// char ctermid(char *str)
// {
//   if (str == NULL)
//     str = ctermid_name;
//   return (strcpy(str, "/dev/tty"));
// }

int isatty(int fd)
{
  struct termios ts;
  return (tcgetattr(fd, &ts) != -1);
}

int main(void)
{
  printf("fd 0 %s\n", isatty(0) ? "tty" : "not a tty");
  printf("fd 1 %s\n", isatty(1) ? "tty" : "not a tty");
  printf("fd 2 %s\n", isatty(2) ? "tty" : "not a tty");
  exit(0);
}