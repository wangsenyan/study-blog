#ifndef _OPEND_H
#define _OPEND_H
#include "apue.h"
#include <errno.h>
#define CS_OPEN "/tmp/opend.socket"
#define CL_OPEN "open"

extern int debug;
extern char errmsg[];
extern int oflag;
extern char *pathname;

typedef struct
{
  int fd;
  uid_t uid;
} Client;

extern Client *client;
extern int client_size;
int buf_args(char *buf, int (*optfunc)(int, char **));
int cli_args(int, char **);
int client_add(int, uid_t);
void client_del(int);
void handle_request(char *, int, int, uid_t);
void loop(void);
#endif