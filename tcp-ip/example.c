#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NLOOP 5000
int counter;
pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
void *doit(void *);
int main(int argc,char **argv)
{
	pthread_t tidA,tidB;
	pthread_create(&tidA,NULL,&doit,NULL);
	pthread_create(&tidB,NULL,&doit,NULL);
	pthread_join(tidA,NULL);
	pthread_join(tidB,NULL);
	exit(0);
}

void *doit(void *vptr)
{
	int i,val;
	for(i=0;i<NLOOP;i++){
		pthread_mutex_lock(&counter_mutex);
		val = counter;
		printf("%d: %d\n",pthread_self(),val+1);
		counter = val+1;
		pthread_mutex_unlock(&counter_mutex);
	}
	return(NULL);
}