#include <unistd.h>
#include <errno.h>
#include <stdlib.h> //exit
#include <stdio.h> //peeor
#include <string.h>
#include <signal.h>
#include <sys/wait.h>
#include "util.h"
void str_echo(int sockfd)
{
	ssize_t n;
	char buf[MAXLINE];
	again:
		while((n=read(sockfd,buf,MAXLINE))>0)
		   write(sockfd,buf,n);
		if(n<0&&errno==EINTR)
		   goto again;
		else if((n<0)){
		   perror("str_echo:read error");
		   exit(1);
		}
}

void str_cli(FILE *fp,int sockfd)
{
	char sendline[MAXLINE],recvline[MAXLINE];
	while(fgets(sendline,MAXLINE,fp)!=NULL){
		writen(sockfd,sendline,1);
		sleep(1);
		writen(sockfd,sendline+1,strlen(sendline)-1);
		if(readline(sockfd,recvline,MAXLINE)==0)
		{
			perror("str_cli:server terminated prematurely");
			exit(0);
		}
		fputs(recvline,stdout);
	}
}

ssize_t writen(int fd,const void *vptr,size_t n)
{
	size_t nleft;
	ssize_t nwritten;
	const char *ptr;
	ptr = vptr;
	nleft = n;
	while(nleft>0)
	{
		if((nwritten=write(fd,ptr,nleft))<=0){
			if(nwritten<0 && errno==EINTR)
		    	nwritten=0;
		    else 
		        return (-1);
		}
		nleft-=nwritten;
		ptr+=nwritten;
	}
	return(n);
}

ssize_t readn(int fd,void *vptr,size_t n)
{
	size_t nleft;
	ssize_t nread;
	char *ptr;
	ptr=vptr;
	nleft = n;
	while(nleft>0){
	    if((nread=read(fd,ptr,nleft))<0){
	       if(errno==EINTR)
	          nread=0;
	        else 
	          return(-1);
     	}else if(nread==0)
     	    break;//EOF        
     	nleft-=nread;
     	ptr+=nread;
	}
	return (n-nleft);
}

ssize_t readline(int fd,void *vptr,size_t maxlen)
{
	ssize_t n,rc;
	char c,*ptr;
	ptr = vptr;
	for(n=1;n<maxlen;n++){
		again:
		  if((rc=read(fd,&c,1))==1){
		  	  *ptr++ = c;
		  	  if(c=='\n')
		  	     break;
		  }else if(rc==0){
		  	*ptr = 0;
		  	return(n-1);
		  }else{
		  	 if(errno==EINTR)
		  	   goto again;
		  	 return (-1);
		  }
	}
	*ptr=0;
	return(n);
}

Sigfunc *signal(int signo,Sigfunc *func)
{
	struct sigaction act;
	struct sigaction oact;
	act.sa_handler = func;
	sigemptyset(&act.sa_mask);//设置为空集，在信号处理函数运行期间不阻塞额外的信号
	act.sa_flags = 0;
	if(signo==SIGALRM){
		#ifdef SA_INTERRUPT
		   act.sa_flags |=SA_INTERRUPT;
		#endif
	}else{
		#ifdef SA_RESTART
		   act.sa_flags |=SA_RESTART;
		#endif
	}
	if(sigaction(signo,&act,&oact)<0)
		return (SIG_ERR);
	return (oact.sa_handler);
}

void sig_chld(int signal)
{
	pid_t pid;
	int stat;
	//pid = wait(&stat);//wait取到子进程的pid和终止状态 
	while((pid=waitpid(-1,&stat,WNOHANG))>0)
	  printf("child %d terminated\n",pid);
	return;
}


