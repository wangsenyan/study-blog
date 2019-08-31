#include<stdlib.h>
#include<stdio.h>
#include <string.h> 
char * concat(const char *s1,const char *s2);
int main()
{
	char *p;
	p=concat("abc","def");
	printf("%s",p);
}

char * concat(const char *s1,const char *s2)
{
	char *result;
	result = (char *)malloc(sizeof(s1)+sizeof(s2)+1);
	if(result == NULL)
	{   
	    printf("malloc err");
		exit(EXIT_FAILURE);
	}
	strcpy(result,s1);
	strcpy(result,s2);
	return result;
}
