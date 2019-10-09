#include "apue.h"
#include <dirent.h> //opendir readdir closedir及 dirent结构定义

int main(int argc, char **argv)
{
  DIR *dp;
  struct dirent *dirp;
  if (argc != 2)
    err_quit("usage: ls direcory_name");
  if ((dp = opendir(argv[1])) == NULL)
    err_sys("cant open %s", argv[1]);
  while ((dirp = readdir(dp)) != NULL)
  {
    printf("%s\n", dirp->d_name);
  }
  closedir(dp);
  exit(0);
}