#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //对posix支持
#include <stdlib.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
  char write_msg[BUFFER_SIZE] = "Greetings\n";
  char read_msg[BUFFER_SIZE];
  int fd[2];
  pid_t pid;
  int n;
  if (pipe(fd) == -1)
  {
    fprintf(stderr, "Pipe failed");
    return 1;
  }
  pid = fork();

  if (pid < 0)
  {
    fprintf(stderr, "Fork Failed");
    return 1;
  }

  if (pid > 0)
  {
    close(fd[READ_END]);
    write(fd[WRITE_END], write_msg, strlen(write_msg) + 1);
    close(fd[WRITE_END]);
  }
  else
  {
    close(fd[WRITE_END]);
    n = read(fd[READ_END], read_msg, BUFFER_SIZE);
    printf("read %s", read_msg);
    //write(STDOUT_FILENO, read_msg, n);
    close(fd[READ_END]);
  }
  return 0;
}
