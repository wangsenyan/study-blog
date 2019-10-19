#include "apue.h"

#include <sys/types.h>
int main(void)
{
  printf("uid = %d, gid = %d, euid = %d, egid = %d\n", getuid(), getgid(), geteuid(), getegid());
  exit(0);
}