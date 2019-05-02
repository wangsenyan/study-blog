#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define BUFFER_SIZE 25

int main(VOID)
{
  HANDLE ReadHandle, WriteHandle;
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  char message[BUFFER_SIZE] = "Greetings\n";
  DWORD written;

  SECURITY_ATTRIBUTES sa = {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE};

  ZeroMemory(&pi, sizeof(pi));

  if (!CreatePipe(&ReadHandle, &WriteHandle, &sa, 0))
  {
    fprintf(stderr, "Create Pipe Failed");
    return 1;
  }
  GetStartupInfo(&si);
  si.hStdOutput = GetStdHandle(STD_OUTPUT_HANDLE);
  si.hStdInput = ReadHandle;
  si.dwFlags = STARTF_USESTDHANDLES;

  SetHandleInformation(WriteHandle, HANDLE_FLAG_INHERIT, 0);

  CreateProcess(NULL, "child.exe", NULL, NULL, TRUE, 0, NULL, NULL, &si, &pi);
  CloseHandle(ReadHandle);

  if (!WriteFile(WriteHandle, message, BUFFER_SIZE, &written, NULL))
    fprintf(stderr, "Error writing to pipe");
  CloseHandle(WriteHandle);

  WaitForSingleObject(pi.hProcess, INFINITE);
  CloseHandle(pi.hProcess);
  CloseHandle(pi.hThread);
  return 0;
}
