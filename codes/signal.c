#include "csapp.h"
#include <dirent.h>
void sigint_handler(int sig);
void handler1(int sig);

int main()
{
	int i,n;
	char buf[MAXBUF];
	if(signal(SIGCHLD,handler1)==SIG_ERR)
	  unix_error("signal error");
	for(i=0;i<3;i++)
	{
	   if(Fork()==0)
	    { 
	       printf("hello from child %d\n",(int)getpid());
		   exit(0);	
		}	
	} 
	if((n=read(STDIN_FILENO,buf,sizeof(buf)))<0)
	   unix_error("read");
	printf("Parent processing input\n");
	while(1)
	  ;
	exit(0);
}

//ssize_t sio_puts(char s[]) /* Put string */
//{
//    return write(STDOUT_FILENO, s, sio_strlen(s)); //line:csapp:siostrlen
//}

void sigint_handler(int sig)
{
    printf("Caught SIGINT!\n");
	exit(0);	
} 

void handler1(int sig)
{
	int olderrno=errno;
	while((waitpid(-1,NULL,0))>0)
    	Sio_puts("Handler reaped child\n");
    if(errno!=ECHILD)
        Sio_error("waitpid error");
	Sleep(1);
	errno=olderrno;
}
