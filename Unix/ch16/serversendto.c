#include "apue.h"
#include <netdb.h>
#include <errno.h>
#include <sys/socket.h>

#define BUFLEN 128
#define TIMEOUT 20

void sigalrm(int signo)
{
}

void print_uptime(int sockfd, struct addrinfo *aip)
{
  int n;
  char buf[BUFLEN];
  buf[0] = 0;
  if (sendto(sockfd, buf, 1, 0, aip->ai_addr, aip->ai_addrlen) < 0)
    err_sys("sendto error");
  alarm(TIMEOUT);
  if ((n = recvfrom(sockfd, buf, BUFLEN, 0, NULL, NULL)) < 0)
  {
    if (errno != EINTR)
      alarm(0);
    err_sys("recv error");
  }
  alarm(0);
  write(STDOUT_FILENO, buf, n);
}

int main(int argc, char *argv[])
{
  struct addrinfo *ailist, *aip;
  struct addrinfo hint;
  int sockfd, err;
  struct sigaction sa;
  if (argc != 2)
    err_quit("usage: rutime hostname");
  sa.sa_handler = sigalrm;
  sa.sa_flags = 0;
  sigemptyset(&sa.sa_mask);
  if (sigaction(SIGALRM, &sa, NULL) < 0)
    err_sys("sigaction error");
  memset(&hint, 0, sizeof(hint));
  hint.ai_socktype = SOCK_STREAM;
  hint.ai_canonname = NULL;
  hint.ai_addr = NULL;
  hint.ai_next = NULL;
  if ((err = getaddrinfo(argv[1], "ruptime", &hint, &ailist)) != 0)
    err_quit("getaddrinfo error: %s", gai_strerror(err));
  for (aip = ailist; aip != NULL; aip = aip->ai_next)
  {
    if ((sockfd = connect_retry(aip->ai_family, SOCK_STREAM, 0, aip->ai_addr, aip->ai_addrlen)) < 0)
    {
      err = errno;
    }
    else
    {
      print_uptime(sockfd);
      exit(0);
    }
  }
  err_exit(err, "can't connect to %s", argv[1]);
}