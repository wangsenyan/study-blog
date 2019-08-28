#include<string.h> 
#include<stdio.h> //standard input/output
#include <stdlib.h> //standard library
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/tcp.h>
#include<arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include <errno.h>
#include "util.h"
#define SERV_TCP_PORT 8000
#define MAX_SIZE 80

int main(int argc,char *argv[])
{
    int sockfd,newsockfd,clilen;
    pid_t childpid;
    struct sockaddr_in cli_addr,serv_addr;
    int port;
    char string[MAX_SIZE];
    int len;

    if(argc==2)
        sscanf(argv[1],"%d",&port);
    else
        port = SERV_TCP_PORT;
    if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
    {
        perror("can't open stream socket");
        exit(1);
    }

    bzero((char *)&serv_addr,sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(port);

    if(bind(sockfd,(struct sockaddr *)&serv_addr,sizeof(serv_addr))<0)
    {
        perror("can't bind local address");
        exit(1);
    }

    listen(sockfd,5);
    signal(SIGCHLD,sig_chld);
    for(;;)
    {
        clilen = sizeof(cli_addr);
        newsockfd = accept(sockfd,(struct sockaddr *)&cli_addr,&clilen);
//        if(newsockfd<0)
//        {
//          if(errno==EINTR)
//	         continue;
//		  else{
//             perror("can't bind local address");
//             exit(1);
//		   } 
//		}
        if(newsockfd<0)
        {
            perror("can't bind local address");
            exit(1);
		}
        if((childpid = fork())==0)
        {
            close(sockfd);
            //do something
            str_echo(newsockfd);
            exit(0);
        }
//        printf("connection from %s,port %d\n",inet_ntop(AF_INET,&cli_addr.sin_addr,string,sizeof(string)),ntohs(cli_addr.sin_port));
//        len = read(newsockfd,string,MAX_SIZE);
//        printf("%d",len);
//        string[len]=0;
//        printf("%s\n",string);
        close(newsockfd);
    }
}
