#include "apue.h"
extern char **environ;
int main(int argc, char *argv[])
{
  pr_ids("child");
  int i;
  for (i = 0; i < argc; i++)
    printf("argv[%d]: %s\n", i, argv[i]);
  for (i = 0; environ[i] != NULL; i++)
    printf("environ[%d]: %s\n", i, environ[i]);
  exit(0);
}