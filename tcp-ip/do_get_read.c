#include "web.h"

void *do_get_read(void *vptr)
{
  int fd, n;
  char line[MAXLINE];
  struct file *fptr;
  fptr = (struct file *)vptr;

  fd = tcp_connect(fptr->f_host, SERV);
  fptr->f_fd = fd;

  printf("do_get_read for %s,fd %d, thread %d\n", fptr->f_name, fd, fptr->f_tid);

  write_get_cmd(fptr);

  for (;;)
  {
    if ((n = read(fd, line, MAXLINE)) == 0)
      break;
    printf("read %d bytes from %s\n", n, fptr->f_name);
  }
  printf("end-of-file on %s\n", fptr->f_name);
  close(fd);
  pthread_mutex_lock(&ndone_mutex);
  fptr->f_flags = F_DONE;
  ndone++;
  pthread_cond_signal(&ndone_cond);
  pthread_mutex_unlock(&ndone_mutex);
  return (fptr);
}