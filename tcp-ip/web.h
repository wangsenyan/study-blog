//#include <stdlib.h>
//#include <sys/select.h>
#include "util.h"
#define F_JOINED 8
#define MAXFILES 20
#define SERV "80"

struct file
{
  char *f_name;
  char *f_host;
  int f_fd;
  int f_flags;
  pthread_t f_tid;
} file[MAXFILES];

#define F_CONNECTING 1
#define F_READING 2
#define F_DONE 4

#define GET_CMD "GET %s HTTP/1.0\r\n\r\n"

int nconn, nfiles, nlefttoconn, nlefttoread;
fd_set rset, wset;
void *do_get_read(void *);
void home_page(const char *, const char *);
//void start_connect(struct file *);
void write_get_cmd(struct file *);