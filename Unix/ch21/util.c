#include "apue.h"
#include "print.h"
#include <ctype.h>
#include <sys/select.h>

#define MAXCFGLINE 512 /* 打印机配置文件的行最大长度 */
#define MAXKWLEN 16    /* 配置文件中关键字的最大长度 */
#define MAXFMTLEN 16   /* 传给sscanf 的格式化字符串的最大长度 */

/**
 * LOCKING: none
 */
int getaddrlist(const char *host, const char *service, struct addrinfo **ailistpp)
{
  int err;
  struct addrinfo hint;
  hint.ai_flags = AI_CANONNAME;
  hint.ai_family = AF_INET;
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_protocol = 0;
  hint.ai_addrlen = 0;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  err = getaddrinfo(host, service, &hint, ailistpp);
  return (err);
}

/**
 * LOCKING: none
 */

static char *scan_configfile(char *keyword)
{
  int n, match;
  FILE *fp;
  char keybuf[MAXKWLEN], pattern[MAXFMTLEN];
  char line[MAXCFGLINE];
  static char valbuf[MAXCFGLINE]; //非重入
  if ((fp = fopen(CONFIG_FIFE, "r")) == NULL)
    log_sys("can't open %s", CONFIG_FIFE);
  sprintf(pattern, "%%%ds %%%ds", MAXKWLEN - 1, MAXCFGLINE - 1); //pattern %15s %511s
  match = 0;
  while (fgets(line, MAXCFGLINE, fp) != NULL)
  {
    n = sscanf(line, pattern, keybuf, valbuf); //返回格式化参数个数
    if (n == 2 && strcmp(keyword, keybuf) == 0)
    {
      match = 1;
      break;
    }
  }
  fclose(fp);
  if (match != 0)
    return (valbuf);
  else
    return (NULL);
}

char *get_printserver(void)
{
  return (scan_configfile("printserver"));
}

struct addrinfo *get_printaddr(void)
{
  int err;
  char *p;
  struct addrinfo *ailist;
  if ((p = scan_configfile("printer")) != NULL)
  {
    if ((err = getaddrlist(p, "ipp", &ailist)) != 0)
    {
      log_msg("no addrerss information for %s", p);
      return (NULL);
    }
    return (ailist);
  }
  log_msg("no printer address specified");
  return (NULL);
}

ssize_t tread(int fd, void *buf, size_t nbytes, unsigned int timeout)
{
  int nfds;
  fd_set readfds;
  struct timeval tv;

  tv.tv_sec = timeout;
  tv.tv_usec = 0;
  FD_ZERO(&readfds);
  FD_SET(fd, &readfds);
  nfds = select(fd + 1, &readfds, NULL, NULL, &tv); //防止拒绝服务攻击
  if (nfds <= 0)
  {
    if (nfds == 0)
      errno = ETIME;
    return (-1);
  }
  return (read(fd, buf, nbytes));
}

/**
 * 读取指定字节数
 */
ssize_t treadn(int fd, void *buf, size_t nbytes, unsigned int timeout)
{
  size_t nleft;
  ssize_t nread;
  nleft = nbytes;
  while (nleft > 0)
  {
    if ((nread = tread(fd, buf, nleft, timeout)) < 0)
    {
      if (nleft == nbytes)
        return (-1); /* error,retrun -1*/
      else
        break; /* error,return amount read so far */
    }
    else if (nread == 0)
      break; /*EOF*/
    nleft -= nread;
    buf += nread;
  }
  return (nbytes - nleft);
}