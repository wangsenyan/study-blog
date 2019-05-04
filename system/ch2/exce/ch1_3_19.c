#include <sys/types.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h> //对posix支持
#include <stdlib.h>
#include <sys/wait.h>
#define BUFFER_SIZE 25
#define READ_END 0
#define WRITE_END 1

int main(void)
{
  char write_msg[BUFFER_SIZE];
  char read_msg[BUFFER_SIZE];
  int fd1[2]; //父进程写
  int fd2[2]; //父进程读
  pid_t pid;
  int n;
  if (pipe(fd1) == -1)
  {
    fprintf(stderr, "Pipe1 failed");
    return 1;
  }
  if (pipe(fd2) == -1)
  {
    fprintf(stderr, "Pipe2 failed");
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
    close(fd1[READ_END]);
    close(fd2[WRITE_END]);
    fgets(write_msg, BUFFER_SIZE, stdin);
    write(fd1[WRITE_END], write_msg, strlen(write_msg) + 1);
    wait(NULL);
    n = read(fd2[READ_END], read_msg, BUFFER_SIZE);
    printf("%s\n", read_msg);
    close(fd1[WRITE_END]);
    close(fd2[READ_END]);
  }
  else
  {
    close(fd1[WRITE_END]);
    close(fd2[READ_END]);
    n = read(fd1[READ_END], read_msg, BUFFER_SIZE);
    printf("%s", read_msg);
    int i = 0;
    while (read_msg[i] != '\0' && read_msg[i] != '\r')
    {
      if (read_msg[i] != ' ' && read_msg[i] >= 'a')
        write_msg[i] = read_msg[i] - 32;
      if (read_msg[i] != ' ' && read_msg[i] <= 'Z')
        write_msg[i] = read_msg[i] + 32;
      if (read_msg[i] == ' ')
        write_msg[i] = ' ';
      i++;
    }
    write_msg[i] = '\0';
    //printf("%s %d", write_msg, (int)strlen(write_msg) + 1);
    write(fd2[WRITE_END], write_msg, strlen(write_msg) + 1);
    //write(STDOUT_FILENO, read_msg, n);
    close(fd2[WRITE_END]);
    close(fd1[READ_END]);
  }
  return 0;
}
