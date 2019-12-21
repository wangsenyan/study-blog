#include <semaphore.h>
struct slock
{
  sem_t *semp;
  char name[_POSIX_NAME_MAX];
}