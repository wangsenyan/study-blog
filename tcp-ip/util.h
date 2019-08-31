#ifndef _UTIL_H_
#define MAXLINE 2047
#define LISTENQ 1024
#define MAX(a, b) ((a > b) ? a : b)
typedef void Sigfunc(int);
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t readline(int fd, void *vptr, size_t maxlen);
Sigfunc *signal(int signo, Sigfunc *func);
void sig_chld(int signal);
struct args
{
  long arg1;
  long arg2;
};
struct result
{
  long sum;
};

#endif
