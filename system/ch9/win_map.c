#include <Windows.h>
#include <stdio.h>

int main(int argc, char *argv[])
{
  HANDLE hFile, hMapFile;
  LPVOID lpMapAddress;
  hFile = CreateFile("win_map.c",
                     GENERIC_READ | GENERIC_WRITE,
                     0,
                     NULL,
                     OPEN_ALWAYS,
                     FILE_ATTRIBUTE_NORMAL,
                     NULL);
  hMapFile = CreateFileMapping(hFile,
                               NULL,
                               PAGE_READWRITE,
                               0,
                               0,
                               TEXT("SharedObject"));
  lpMapAddress = MapViewOfFile(hMapFile,
                               FILE_MAP_ALL_ACCESS,
                               0,
                               0,
                               0);
  //sprintf(lpMapAddress, "Shared memory message");
  printf("%s",lpMapAddress);
  getch();
  UnmapViewOfFile(lpMapAddress);
  CloseHandle(hFile);
  CloseHandle(hMapFile);
}
