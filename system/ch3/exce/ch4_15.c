#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <pthread.h>
#include <unistd.h>
#define MIN_PID 300
#define MAX_PID 3000
#define cb CHAR_BIT

int sz = MAX_PID - MIN_PID + 1;

unsigned char *b;

int allocate_map();
int allocate_pid();
void release_pid(int pid);
void *runner(void *param);

int main()
{
  int map = allocate_map();
  if (map == 1)
  {
    int i = 0;
    pthread_t tid;
    pthread_attr_t attr;

    pthread_attr_init(&attr);
    while (i++ < 100)
    {
      pthread_create(&tid, &attr, runner, NULL);
    }
    sleep(2000);
  }
  else
    printf("\nFailed to initialize data structure.\n");
}

/* Creates and initializes a data structure for representing pids;
 returns —1 if unsuccessful, 1 if successful */
int allocate_map()
{
  b = (unsigned char *)malloc((sz + cb - 1) / cb * sizeof(char));
  if (b)
    return 1;
  return -1;
}

/* Allocates and returns a pid; returns -1
if unable to allocate a pid (all pids are in use) 
bit calculate
*/
int allocate_pid()
{
  int i = 0;
  int pid = b[i / cb] & (1 << (i & (cb - 1)));
  while (pid != 0)
  {
    i++;
    pid = b[i / cb] & (1 << (i & (cb - 1)));
  }

  if (i + MIN_PID > MAX_PID)
    return -1;
  b[i / cb] |= 1 << (i & (cb - 1));
  return i + MIN_PID;
}

/* Releases a pid */
void release_pid(int pid)
{
  if (pid < 300)
  {
    printf("\nInvalid PID: It should lie between 500 and 3000.");
    return;
  }
  int i = pid - MIN_PID;
  b[i / cb] &= ~(1 << (i & (cb - 1)));
}
void *runner(void *param)
{
  int pid = allocate_pid();
  printf("this is pid %d\n", pid);
  sleep(rand());
  pthread_exit(0);
}