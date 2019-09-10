#include <syslog.h>
#include <signal.h>
#define MAXFD 64
extern int daemon_proc;

int deamon_init(const char *pname, int facility)
{
  int i;
  pid_t pid;

  if ((pid = fork()) < 0)
    return (-1);
  else if (pid)
    _exit(0);

  if (setsid() < 0)
    return (-1);

  signal(SINHUP, SIG_IGN);
  //再次fork目的:确保本守护进程将来即使打开一个终端，也不会自动获得控制终端
  if ((pid = fork()) < 0)
    return (-1);
  else if (pid)
    _exit(0);

  daemon_proc = 1;
  chdir("/");
  for (i = 0; i < MAXFD; i++)
    close(i);
  open("/dev/null", O_RDONLY);
  open("/dev/null", O_RDWR);
  open("/dev/null", O_RDWR);
  openlog(pname, LOG_PID, facility);
  return (0);
}