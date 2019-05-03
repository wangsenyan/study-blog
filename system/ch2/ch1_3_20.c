#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h> //对posix支持
#include <sys/wait.h>
#define BUFFER_SIZE 1000
#define READ_END 0
#define WRITE_END 1

int main(int argc, char *argv[])
{
  // printf("%s %s", argv[1], argv[2]);
  char write_msg[BUFFER_SIZE];
  char read_msg[BUFFER_SIZE];
  int fd[2], des, bytes, target; //父进程写
  pid_t pid;
  if (pipe(fd) == -1)
  {
    fprintf(stderr, "Pipe1 failed");
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
    des = open(argv[1], O_RDONLY);
    read(des, write_msg, sizeof(write_msg));
    write(fd[WRITE_END], write_msg, sizeof(write_msg));
    wait(NULL);
    close(fd[WRITE_END]);
  }
  else
  {
    close(fd[WRITE_END]);
    read(fd[READ_END], read_msg, sizeof(read_msg));
    close(fd[READ_END]);
    target = open(argv[2], O_CREAT | O_WRONLY, 00777); //必须有O_WRONLY
    write(target, read_msg, (strlen(read_msg) - 1));
  }
  return 0;
}
