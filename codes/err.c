#include "csapp.h" 
#include <unistd.h>
#include <errno.h>
#include<pthread.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>// int execve(const char *filename,cosnt char *argv[],const char *envp[]);char *getenv(const char *name);
                   // int setenv(const char *name,const char *newvalue,int overwrite); void unsetenv(const char *name);
#include <sys/types.h>
#include <sys/wait.h> //pid_t waitpid(pid_t pid,int *statusp,int options); wait(&status)==waitpid(-1,&status,0)
#include <unistd.h> //pid_t getpid(void) ;pid_t getppid(void) ; pid_t fork(void); unsigned int sleep(unsigned int secs); int pause(void);
                    //int execve(const char *filename,const char *argv[],const char *envp[]);
                    //pid_t getpgrp(void); int setpgid(pid_t pid,pid_t pgid); int kill(pid_t pid,int sig);
                    //unsigned int alarm(unsigned int secs);
                    //typedef void (*sighandler_t)(int)
                    //sighandler_t signal(int signum,sighandler_t handler);
#define N 2
#define MAXARGS 128
//#define MAXLINE 225
//void unix_error(char *msg);
//pid_t Fork(void);
void eval(char *cmdline);
int parseline(char *buf,char **argv);
int builtin_command(char **argv);
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
//-------------------------------------------------
//   sigset_t mask,prev_mask;
//   Sigemptyset(&mask);
//   Sigaddset(&mask,SIGINT);
//   
//   Sigprocmask(SIG_BLOCK,&mask,&prev_mask);
//   
//   Sigprocmask(SIG_SETMASK,&mask,&prev_mask);
//-------------------------------------------------
//    if(signal(SIGINT,sigint_handler)==SIG_ERR)
//       unix_error("signal error");
//    pause();
//    return 0;

//-------------------------------------------------
//    pid_t pid;
//    if((pid=Fork())==0)
//    {
//    	Pause();
//    	printf("control should never reach here!\n");
//    	exit(0);
//	}
//	Kill(pid,SIGKILL);
//	exit(0);
//---------------------------------------------------- 
//   char cmdline[MAXLINE];
//   while(1)
//   {
//   	   printf("> ");
//   	   Fgets(cmdline,MAXLINE,stdin);
//   	   if(feof(stdin))
//          exit(0);
//        eval(cmdline);
//   }

//--------------------------------------------------
//     int i;
//     printf("Command-line arguments:\n");
//     for(i=0;argv[i]!=NULL;i++)
//        printf("    argv[%2d]: %s\n",i,argv[i]);
//     printf("\n");
//     printf("Enviroment variables:\n");
//     for(i=0;envp[i]!=NULL;i++)
//        printf("    envp[%2d]: %s\n",i,envp[i]);
//     exit(0);

// --------------------------------------------------------
//     int status,i;
//     pid_t pid[N],retpid;
//     for(i=0;i<N;i++)
//        if((pid[i]=Fork())==0)
//           exit(100+i);
//     i=0;
//     while((retpid=waitpid(pid[i++],&status,0))>0)
//     {
//     	if(WIFEXITED(status))
//     	   printf("child %d terminated normally with exit status=%d\n",retpid,WEXITSTATUS(status));
//     	else 
//     	   printf("child %d terminated abnormally\n",retpid);
//	 }
//	 if(errno!=ECHILD)
//	    unix_error("waitpif error");
//	 exit(0);
//------------------------------------------------------------
//     int status,i;
//     pid_t pid;
//     for(i=0;i<N;i++)
//        if((pid=Fork())==0)
//           exit(100+i);
//     while((pid=waitpid(-1,&status,0))>0)
//     {
//     	if(WIFEXITED(status))
//     	   printf("child %d terminated normally with exit status=%d\n",pid,WEXITSTATUS(status));
//     	else 
//     	   printf("child %d terminated abnormally\n",pid);
//	 }
//	 if(errno!=ECHILD)
//	    unix_error("waitpif error");
//	 exit(0);
//----------------------------------------------------------
//    pid_t pid;
//    int x =1 ;
//
//    pid=Fork();
//    if(pid==0)
//    {
//    	printf("child : x=%d\n",++x);
//    	exit(0);
//    }
//	printf("parent: x=%d\n",--x);
//	exit(0);
//  write(1,"hello,world\n",13);
//  _exit(0); 
//	if(Fork()==0)
//	{
//		printf("a");
//		fflush(stdout);
//	}else{
//		printf("b");
//		fflush(stdout);
//		waitpid(-1,NULL,0);
//	}
//	printf("c");
//	fflush(stdout);
//	exit(0);
}
sort(b.end(),a.begin());
int i=0;j=1,k=0;
int t=0;
while(j<n)
{
   if(i+1==j)
     j++;
   else if(a[i]+a[j+1]<a[i+1]+a[j])
   {
        i++;
        j=i+1;
   }
   else 
     j++;
   if(j>=n)
     break;
   t+=a[i]+a[j];
   k++;
}

void sigint_handler(int sig)
{
    printf("Caught SIGINT!\n");
	exit(0);	
} 

void handler1(int sig)
{
	int olderrno=errno;
	if((waitpid(-1,NULL,0))<0)
	   sio_error("waitpid error");
	Sio_puts("Handler reaped child\n");
	Sleep(1);
	errno=olderrno;
}
//void eval(char *cmdline)
//{
//	char *argv[MAXARGS];
//	char buf[MAXLINE];
//	int bg;
//	pid_t pid;
//	strcpy(buf,cmdline);
//	bg=parseline(buf,argv);
//	if(argv[0]==NULL)
//	   return;
//	if(!builtin_command(argv)){
//		if((pid=Fork())==0)
//		{
//			if(execve(argv[0],argv,environ)<0){
//				printf("%s: Command not found.\n",argv[0]);
//				exit(0);
//			}
//		}
//		if(!bg){
//			int status;
//			if(waitpid(pid,&status,0)<0)
//			   unix_error("waitfg: waitpid error");
//		}else 
//		    printf("%d  %s",pid,cmdline);
//	}
//	return;
//}
//
//int builtin_command(char **argv)
//{
//	if(!strcmp(argv[0],"quit"))
//	   exit(0);
//	if(!strcmp(argv[0],"&"))
//	   return 1;
//	return 0;
//}
//
//int parseline(char *buf,char **argv)
//{
//	char *delim;
//	int argc;
//	int bg;
//	buf[strlen(buf)-1]=' ';
//	while(*buf&&(*buf==' '))
//	     buf++;
//	argc=0;
//	while((delim=strchr(buf,' '))){
//		argv[argc++]=buf;
//		*delim='\0';
//		buf=delim+1;
//		while(*buf&&(*buf==' '))
//		  buf++;
//	} 
//	argv[argc]=NULL;
//	if(argc==0)
//	   return 1;
//	if((bg=(*argv[argc-1]=='&'))!=0)
//	   argv[--argc]=NULL;
//	return bg;
//}
//unsigned int snooze(unsigned int secs)
//{
//	unsigned int s=sleep(secs);
//	printf("Slept for %d of %d secs",secs-s,secs);
//	return s;
//}
//
//void unix_error(char *msg)
//{
//	fprintf(stderr,"%s: %s\n",msg,strerror(errno));
//	exit(0);
//}
//
//pid_t Fork(void)
//{
//	pid_t pid;
//	if((pid=fork())<0)
//	  unix_error("Fork error");
//	return pid; 
//}
