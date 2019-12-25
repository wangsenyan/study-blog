#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <unistd.h> //read write
#include <errno.h>
#include "util.h"
#define SERV_TCP_PORT 8000

int main(int argc, char *argv[])
{
  int sockfd;
  //int i,sockfd[5];
  struct sockaddr_in serv_addr;
  char *serv_host = "localhost";
  struct hostent *host_ptr;
  int port;
  int buff_size = 0;
  char *msg;
  if (argc >= 2)
    serv_host = argv[1];
  if (argc >= 3)
    sscanf(argv[2], "%d", &port);
  if (argc > 3)
    msg = argv[3];
  else
    port = SERV_TCP_PORT;

  //printf("%s %d %s",serv_host,port,msg);
  if ((host_ptr = gethostbyname(serv_host)) == NULL)
  {
    perror("gethostbyname error");
    exit(1);
  }
  if (host_ptr->h_addrtype != AF_INET)
  {
    perror("unknown address type");
    exit(1);
  }
  //    for(i=0;i<5;i++){
  //        if((sockfd[i]=socket(AF_INET,SOCK_STREAM,0))<0)
  //	      //if((sockfd=socket(9999,SOCK_STREAM,0))<0)
  //	    {
  //	      printf("%d", errno);
  //	      perror("can't open stream socket");
  //	      exit(0);
  //	    }
  //	    bzero((char*)&serv_addr,sizeof(serv_addr));
  //	    serv_addr.sin_family = AF_INET;
  //	    //serv_addr.sin_addr.s_addr = ((struct in_addr*)host_ptr->h_addr_list[0])->s_addr;
  //	    inet_pton(AF_INET,argv[1],&serv_addr.sin_addr);
  //	    serv_addr.sin_port=htons(port);
  //
  //	     if(connect(sockfd[i], (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
  //	       perror("can't connect to server");
  //	       exit(1);
  //	     }
  //	 }
  bzero((char *)&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = ((struct in_addr *)host_ptr->h_addr_list[0])->s_addr;
  serv_addr.sin_port = htons(port);

  if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  //if((sockfd=socket(9999,SOCK_STREAM,0))<0)
  {
    printf("%d", errno);
    perror("can't open stream socket");
    exit(0);
  }
  if (connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    perror("can't connect to server");
    exit(1);
  }
  //  printf("%d",(int)sizeof(msg));
  //write(sockfd,msg,strlen(msg));
  //str_cli(stdin,sockfd);
  //str_cli_poll(stdin,sockfd);
  printf("connected success");
  str_cli_pthread(stdin, sockfd);
  exit(0);
  //close(sockfd);
}
