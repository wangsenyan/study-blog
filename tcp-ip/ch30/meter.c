#include "util.h"
#include <sys/mman.h>

long *meter(int nchildren)
{
  int fd;
  long *ptr;
#ifdef MAP_ANON
  ptr = mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, -1, 0);
#else
  fd = open("/dev/zero", O_RDWR, 0);
  ptr = mmap(0, nchildren * sizeof(long), PROT_READ | PROT_WRITE, MAP_ANON | MAP_SHARED, fd, 0);
  close(fd);
#endif
  return (ptr);
}