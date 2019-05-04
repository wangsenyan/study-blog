#include <Windows.h>
#include <stdio.h>
#include <stdlib.h>
DWORD Sum;
DWORD WINAPI Summation(LPVOID Param)
{
  DWORD Upper = *(DWORD *)Param;
  DWORD i;
  for (i = 0; i <= Upper; i++)
    Sum += i;
  return 0;
}

int main(int argc, char *argv[])
{
  DWORD ThreadId;
  HANDLE ThreadHandle;
  int Param;

  if (argc != 2)
  {
    fprintf(stderr, "An interger parameter is required\n");
    return -1;
  }
  Param = atoi(argv[1]);
  if (Param < 0)
  {
    fprintf(stderr, "An interger >=0 is required\n");
    return -1;
  }
  ThreadHandle = CreateThread(
      NULL,
      0,
      Summation,
      &Param,
      0,
      &ThreadId);
  if (ThreadHandle != NULL)
  {
    WaitForSingleObject(ThreadHandle, INFINITE);
    //WaitForMultipleObjects(N, THandles, TRUE, INFINITE);等待N个线程INFINITE时间
    CloseHandle(ThreadHandle);

    printf("sum = %d\n", Sum);
  }
  return 0;
}
