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
  struct in_addr **pptr;
  struct in_addr *inetaddrp[2];
  struct in_addr inetaddr;
  struct hostent *hp;
  struct servent *sp;

  if (argc != 3)
  {
    perror("usage:daytimetcpcli <hostname> <service>");
    exit(0);
  }
  if ((hp = gethostbyname(argv[1])) == NULL)
  {
    if (inet_aton(argv[1], &inetaddr) == 0)
    {
      printf("hostname error for %s: %s\n", argv[1], hstrerror(h_errno));
      exit(1);
    }
    else
    {
      inetaddrp[0] = &inetaddr;
      inetaddrp[1] = NULL;
      pptr = inetaddrp;
    }
  }
  else
  {
    pptr = (struct in_addr **)hp->h_addr_list;
  }
  if ((sp = getservbyname(argv[2], "tcp")) == NULL)
  {
    printf("getservbyname error for %s\n", argv[2]);
    exit(1);
  }
  for (; *pptr != NULL; pptr++)
  {
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = sp->s_port;
    memcpy(&servaddr.sin_addr, *pptr, sizeof(struct in_addr));
    printf("trying %s\n", sock_ntop((struct sockaddr *)&servaddr, sizeof(servaddr)));

    if (connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) == 0)
      break;
    perror("connect error\n");
    close(sockfd);
  }
  if (*pptr == NULL)
  {
    perror("unable to connect\n");
    exit(1);
  }
  while ((n = read(sockfd, recvline, MAXLINE)) > 0)
  {
    recvline[n] = 0;
    fputs(recvline, stdout);
  }
  exit(0);
}