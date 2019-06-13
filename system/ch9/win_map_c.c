
#include <Windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  HANDLE hMapFile;
  LPVOID lpMapAddress;
  hMapFile = OpenFileMapping(FILE_MAP_ALL_ACCESS,
                             FALSE,
                             TEXT("SharedObject"));
  lpMapAddress = MapViewOfFile(hMapFile,
                               FILE_MAP_ALL_ACCESS,
                               0,
                               0,
                               0);
  printf("Read message %s", lpMapAddress);
  UnmapViewOfFile(lpMapAddress);
  CloseHandle(hMapFile);
}