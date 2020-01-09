#define _XOPEN_SOURCE
#define _GNU_SOURCE
#include "apue.h"
#include <errno.h>
#include <stdlib.h>
#include <fcntl.h>
#include <termios.h>
#if defined(SOLARIS)
#include <stropts.h>
#endif

//打开一个未被使用的 PTY主设备，并初始化对应的PTY从设备
int ptym_open(char *pts_name, int pts_namesz)
{
  char *ptr;
  int fdm, err;
  if ((fdm = posix_openpt(O_RDWR)) < 0)
    return (-1);
  if (grantpt(fdm) < 0)
    goto errout;
  if (unlockpt(fdm) < 0)
    goto errout;
  if ((ptr = ptsname(fdm)) == NULL)
    goto errout;

  strncpy(pts_name, ptr, pts_namesz);
  pts_name[pts_namesz - 1] = '\0';
  return (fdm);
errout:
  err = errno;
  close(fdm);
  errno = err;
  return (-1);
}

int ptys_open(char *pts_name)
{
  int fds;
#if defined(SOLARIS)
  int err, setup;
#endif
  if ((fds = open(pts_name, O_RDWR)) < 0)
    return (-1);
#if defined(SOLARIS)
  if ((setup = ioctl(fds, I_FIND, "ldterm")) < 0)
    goto errout;
  if (setup == 0)
  {
    //将3个STREAMS模块压入从设备的流中
    if (ioctl(fds, I_PUSH, "ptem") < 0) //伪终端仿真模块
      goto errout;
    if (ioctl(fds, I_PUSH, "ldpterm") < 0) //终端行规程模块
      goto errout;
    if (ioctl(fds, I_PUSH, "ttcompat") < 0) //对早期系统的ioctl调用的兼容
    {
    errout:
      err = errno;
      close(fds);
      errno = err;
      return (-1);
    }
  }
#endif
  return (fds);
}
