#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <arpa/inet.h> //inet_aton
#include "util.h"
#include "sock_ntop.h"

int main(int argc, char **argv)
{
  int sockfd, n;
  char recvline[MAXLINE + 1];
  struct sockaddr_in servaddr;
  struct sockaddr_in6 servaddr6;
  struct sockaddr *sa;
  socklen_t salen;
  struct in_addr **pptr;
  struct hostent *hp;
  struct servent *sp;

  if (argc != 3)
  {
    perror("usage: daytimetcpcli1 <hostname> <service>");
    exit(0);
  }
  if ((hp = gethostbyname(argv[1])) == NULL)
  {
    printf("hostname error for %s: %s\n", argv[1], hstrerror(h_errno));
    exit(0);
  }
  if ((sp = getservbyname(argv[2], "tcp")) == NULL)
  {
    printf("getservbyname error for %s\n", argv[2]);
    exit(0);
  }
  pptr = (struct in_addr **)&hp->h_addr_list;
  for (; *pptr != NULL; pptr++;)
  {
    sockfd = socket(hp->h_addrtype, SOCK_STREAM, 0);
    if (hp->h_addrtype == AF_INET)
    {
      sa = (struct sockaddr *)&servaddr;
      salen = sizeof(servaddr);
    }
    else if (hp->h_addrtype == AF_INET6)
    {
      sa = (struct sockaddr *)&servaddr6;
      salen = sizeof(servaddr6);
    }
    else
    {
      printf("unkown addrtype %d", hp->h_addrtype);
      exit(0);
    }
    bzero(&sa, salen);
    sa->sa_family = hp->h_addrtype;
    sock_set_port(sa, salen, sp->s_port);
    sock_set_addr(sa, salen, *pptr);

    printf("trying %s\n", sock_ntop(sa, salen));
    // char host[NI_MAXHOST], serv[NI_MAXSERV];
    // getnameinfo(sa, salen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
    if (connect(sockfd, sa, salen) == 0)
      break;
    perror("connect error");
    close(sockfd);
  }
  if (*pptr == NULL)
  {
    perror("unable to connect");
    exit(0);
  }
  while ((n = read(sockfd, recvline, MAXLINE)) > 0)
  {
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
  exit(0);
}