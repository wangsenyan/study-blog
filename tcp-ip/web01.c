#include "web.h"

int main(int argc, char **argv)
{
  int i, n, maxnconn;
  pthread_t tid;
  struct file *fptr;

  if (argc < 5)
    err_quit("usage: web <#conns><IPaddr><homepage> file1 ...");
  maxnconn = atoi(argv[1]);
  nfiles = MIN(argc - 4, MAXFILES);
  for (i = 0; i < nfiles; i++)
  {
    file[i].f_name = argv[i + 4];
    file[i].f_host = argv[2];
    file[i].f_flags = 0;
  }
  printf("nfiles = %d\n", nfiles);
  home_page(argv[2], argv[3]);
  nlefttoread = nlefttoconn = nfiles;
  nconn = 0;
  while (nlefttoread > 0)
  {
    while (nconn < maxnconn && nlefttoconn > 0)
    {
      for (i = 0; i < nfiles; i++)
        if (file[i].f_flags == 0)
          break;
      if (i == nfiles)
        err_quit("nlefttoconn = %d but nothing found", nlefttoconn);
      file[i].f_flags = F_CONNECTING;
      pthread_create(&tid, NULL, &do_get_read, &file[i]);
      file[i].f_tid = tid;
      nconn++;
      nlefttoconn--;
    }
    pthread_mutex_lock(&ndone_mutex);
    while (ndone == 0)
      pthread_cond_wait(&ndone_cond, &ndone_mutex);
    for (i = 0; i < nfiles; i++)
    {
      if (file[i].f_flags & F_DONE)
      {
        pthread_join(file[i].f_tid, (void **)&fptr);
        if (&file[i] != fptr)
          err_quit("file[i]!=fptr");
        fptr->f_flags = F_JOINED;
        ndone--;
        nconn--;
        nlefttoread--;
        printf("thread %d for %s done\n", fptr->f_tid, fptr->f_name);
      }
    }
    pthread_mutex_unlock(&ndone_mutex);
  }
  exit(0);
}