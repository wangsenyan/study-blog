#include <errno.h>
#include <stdlib.h> //exit
#include <stdio.h>  //peeor
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include "sock_ntop.h"
#include <netdb.h>
#include <syslog.h>
#include <fcntl.h>
#include <stdarg.h>
#include <sys/un.h>
#include <sys/unistd.h> //unlink
#include <arpa/inet.h> //inet_pton
#include <time.h>
#define HAVE_MSGHDR_MSG_CONTROL 1
#ifndef _UTIL_H_
#define MAXLINE 2047
#define LISTENQ 1024
#define INFTIM -1
#define OPEN_MAX 256
#define MAX(a, b) (((a) > (b)) ? (a) : (b))
#define MIN(a,b)  (((a) < (b)) ? (a) : (b))
#define NDG 2000
#define DGLEN 1400
#define MAXFD 64
#define UNIXSTR_PATH "/tmp/unix.str"
#define BUFSIZE 256
#define SERV_PORT 8000
#define CONTROL_LEN (sizeof(struct cmsghdr) + sizeof(struct cmsgcred))
typedef void Sigfunc(int);
void str_echo(int sockfd);
void str_cli(FILE *fp, int sockfd);
ssize_t writen(int fd, const void *vptr, size_t n);
ssize_t readn(int fd, void *vptr, size_t n);
ssize_t readline(int fd, void *vptr, size_t maxlen);
Sigfunc *signal(int signo, Sigfunc *func);
void sig_chld(int signal);
static void sig_alarm(int signo);
int readable_timeo(int fd, int sec);
void dg_echo(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);
void dg_cli(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_cli_pri(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_cli_conn(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_cli_bigdata(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_cli_select(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_cli_so(FILE *fp, int sockfd, const struct sockaddr *pservaddr, socklen_t servlen);
void dg_echo_calc(int sockfd, struct sockaddr *pcliaddr, socklen_t clilen);
int tcp_connect(const char *host, const char *serv);
int tcp_listen(const char *host, const char *serv, socklen_t *addrlenp);
int udp_client(const char *hostname, const char *service, struct sockaddr **saptr, socklen_t *lenp);
int udp_connect(const char *hostname, const char *service);
int udp_server(const char *hostname, const char *service, socklen_t *lenptr);
int deamon_init(const char *pname, int facility);
static void err_doit(int, int, const char *, va_list);
void err_exit(int error, const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);
static void connect_alarm(int signo);
int connect_timeo(int sockfd, const struct sockaddr *saptr, socklen_t salen, int nsec);
ssize_t write_fd(int fd, void *ptr, size_t nbytes, int sendfd);
ssize_t read_fd(int fd, void *ptr, size_t nbytes, int *recvfd);
int my_open(const char *pathname, int mode);
int connect_nonb(int sockfd, const struct sockaddr *saptr, socklen_t salen, int nsec);
struct addrinfo *host_serv(const char *host, const char *serv, int family, int socktype);
//ssize_t read_cred(int fd, void *ptr, size_t nbytes, struct cmsgcred *cmsgcredptr);
//void str_echo_cred(int sockfd);
//void str_cli_poll(FILE *fp, int sockfd);
void str_cli_unblock(FILE *fp, int sockfd);
char *gf_time(void);
static void recvfrom_int(int);
static int count;
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
