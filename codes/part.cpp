#include<stdio.h>
#define SIZE 2
int main(int argc,char *argv[])
{
	unsigned char buf[SIZE];
	FILE * f;
	f=fopen(argv[1],"rb");
	while(!feof(f))
	{
		fread(buf,1,2,f);
		printf("0x%x%x\n",buf[0],buf[1]);
	}
	fclose(f);
	return 0;
}
