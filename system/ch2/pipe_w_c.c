
#include <stdio.h>
#include <Windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
  HANDLE Readhandle;
  CHAR buffer[BUFFER_SIZE];
  DWORD read;

  Readhandle = GetStdHandle(STD_INPUT_HANDLE);
  if (ReadFile(Readhandle, buffer, BUFFER_SIZE, &read, NULL))
    printf("child read %s\n", buffer);
  else
    fprintf(stderr, "Error reading from pipe");

  return 0;
}