#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/tcp.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <errno.h>
#include <sys/time.h>
#include <stdlib.h>
#include <memory.h>
#include <ifaddrs.h>
#include <net/if.h>
#include <stdarg.h>
/* the next two includes probably aren't relevant for you, but I typically use them all anyway */
#include <math.h>
#include <sys/termios.h>
union val {
  int i_val;
  long l_val;
  struct linger linger_val;
  struct timeval timeval_val;
} val;

static char *sock_str_flag(union val *, int);
static char *sock_str_int(union val *, int);
static char *sock_str_linger(union val *, int);
static char *sock_str_timeval(union val *, int);
struct sock_opts
{
  const char *opt_str;
  int opt_level;
  int opt_name;
  char *(*opt_val_str)(union val *, int);
} sock_opts[] = {
    {"SO_BROADCAST", SOL_SOCKET, SO_BROADCAST, sock_str_flag},
    {"SO_DEBUG", SOL_SOCKET, SO_DEBUG, sock_str_flag},
    {"SO_DONTROUTE", SOL_SOCKET, SO_DONTROUTE, sock_str_flag},
    {"SO_ERROR", SOL_SOCKET, SO_ERROR, sock_str_int},
    {"SO_KEEPALIVE", SOL_SOCKET, SO_KEEPALIVE, sock_str_flag},
    {"SO_LINGER", SOL_SOCKET, SO_LINGER, sock_str_linger},
    {"SO_OOBINLINE", SOL_SOCKET, SO_OOBINLINE, sock_str_flag},
    {"SO_RCVBUF", SOL_SOCKET, SO_RCVBUF, sock_str_int},
    {"SO_SNDBUF", SOL_SOCKET, SO_SNDBUF, sock_str_int},
    {"SO_RCVLOWAT", SOL_SOCKET, SO_RCVLOWAT, sock_str_int},
    {"SO_SNDLOWAT", SOL_SOCKET, SO_SNDLOWAT, sock_str_int},
    {"SO_RCVTIMEO", SOL_SOCKET, SO_RCVTIMEO, sock_str_timeval},
    {"SO_SNDTIMEO", SOL_SOCKET, SO_SNDTIMEO, sock_str_timeval},
    {"SO_REUSEADDR", SOL_SOCKET, SO_REUSEADDR, sock_str_flag},
#ifdef SO_REUSEPORT
    {"SO_REUSEPORT", SOL_SOCKET, SO_REUSEPORT, sock_str_flag},
#else
    {"SO_REUSEPORT", 0, 0, NULL},
#endif
    {"SO_TYPE", SOL_SOCKET, SO_TYPE, sock_str_int},
// {"SO_USELOOPBACK", SOL_SOCKET, SO_USELOOPBACK, sock_str_flag},
#ifdef IP_TOS
    {"IP_TOS", IPPROTO_IP, IP_TOS, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef IP_TTL
    {"IP_TTL", IPPROTO_IP, IP_TTL, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef IPV6_DONTFRAG
    {"IPV6_DONTFRAG", IPPROTO_IPV6, IPV6_DONTFRAG, sock_str_flag},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef IPV6_UNICAST_HOPS
    {"IPV6_UNICAST_HOPS", IPPROTO_IPV6, IPV6_UNICAST_HOPS, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef IPV6_V6ONLY
    {"IPV6_V6ONLY", IPPROTO_IPV6, IPV6_V6ONLY, sock_str_flag},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef TCP_MAXSEG
    {"TCP_MAXSEG", IPPROTO_TCP, TCP_MAXSEG, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef TCP_NODELAY
    {"TCP_NODELAY", IPPROTO_TCP, TCP_NODELAY, sock_str_flag},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef SCTP_AUTOCLOSE
    {"SCTP_AUTOCLOSE", IPPROTO_SCTP, SCTP_AUTOCLOSE, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef SCTP_MAXBURST
    {"SCTP_MAXBURST", IPPROTO_SCTP, SCTP_MAXBURST, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef SCTP_MAXSEG
    {"SCTP_MAXSEG", IPPROTO_SCTP, SCTP_MAXSEG, sock_str_int},
#else
    {"NULL", 0, 0, NULL},
#endif
#ifdef SCTP_NODELAY
    {"SCTP_NODELAY", IPPROTO_SCTP, SCTP_NODELAY, sock_str_flag},
#else
    {"NULL", 0, 0, NULL},
#endif
    {"NULL", 0, 0, NULL},
};

int main(int argc, char **argv)
{
  int fd;
  socklen_t len;
  struct sock_opts *ptr;

  for (ptr = sock_opts; ptr->opt_str != NULL; ptr++)
  {
    printf("%s: ", ptr->opt_str);
    if (ptr->opt_val_str == NULL)
      printf("(undefined)\n");
    else
    {
      switch (ptr->opt_level)
      {
      case SOL_SOCKET:
      case IPPROTO_IP:
      case IPPROTO_TCP:
        fd = socket(AF_INET, SOCK_STREAM, 0);
        break;
#ifdef IPV6
      case IPPROTO_IPV6:
        fd = socket(AF_INET6, SOCK_STREAM, 0);
        break;
#endif
#ifdef IPPROTO_SCTP
      case IPPROTO_SCTP:
        fd = socket(AF_INET, SOCK_SEQPACKET, IPPROTO_SCTP);
        break;
#endif
      default:
        printf("can't create fd for level %d\n", ptr->opt_name);
        exit(1);
      }

      len = sizeof(val);
      if (getsockopt(fd, ptr->opt_level, ptr->opt_name, &val, &len) == -1)
      {
        perror("getsockopt error");
        exit(0);
      }
      else
      {
        printf("default = %s\n", (*ptr->opt_val_str)(&val, len));
      }
      close(fd);
    }
  }
}

static char strres[128];
static char *sock_str_flag(union val *ptr, int len)
{
  if (len != sizeof(int))
  {
    snprintf(strres, sizeof(strres), "size (%d) ont sizeof(int)", len);
  }
  else
  {
    snprintf(strres, sizeof(strres),
             "%s", (ptr->i_val == 0) ? "off" : "on");
  }
}