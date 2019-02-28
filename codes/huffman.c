#include <stdio.h>
#include <stdlib.h>
#define N 50
#define M 2*N-1
int main(){

}
typedef struct 
{
	char data[10];
	double weight;
	int parent;
	int lchild;
	int rchild;
}HTnode;

typedef struct
{
	char cd[N];
	int start;
}HCode;

void createHT(HTnode ht[],int n0)
{
	int i,k,lnode,rnode;
	double min1,min2;
	for(i=0;i<2*n0-1;i++)
		ht[i].parent=ht[i].lchild=ht[i].rchild=-1;
	for(i=n0;i<2*n0-2;i++){
		min1=min2=32767;
		lnode=rnode=-1;
		for(k=0;k<=i-1;k++)
			if(ht[k].parent==-1)
			{
				if(ht[k].weight<min1)
				{
					min2=min1;
					rnode=lnode;
					min1=ht[k].weight;
					lnode=k;
				}else if(ht[k].weight<min2)
				{
					min2=ht[k].weight;
					rnode=k;
				}
			}
			ht[i].weight=ht[lnode].weight+ht[rnode].weight;
			ht[i].lchild=lnode;
			ht[i].rchild=rnode;
			ht[lnode].parent=i;
			ht[rnode].parent=i;
	}
}

void createHCode(HTnode ht[],HCode hcd[],int n0)
{
	int i,f,c;
	HCode hc;
	for(i=0;i<n0;i++)
	{
		ht.start=n0;c=i;
		f=ht[i].parent;
		while(f!=-1){
			if(ht[f].lchild==c)
				hc.cd[hc.start--]='0';
			else
				hc.cd[hc.start--]='1';
			c=f;
			f=ht[f].parent;
		}
		hc.start++;
		hcd[i]=hc;
	}
}