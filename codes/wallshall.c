#include<stdio.h>
#include <stdlib.h>
#include<string.h>
#define N 3
int wallshall(int a[N][N],int n);
int main(void){
   //int a[N][N]={{0,0,0,1},{1,0,1,0},{1,0,0,1},{0,0,1,0}};
   int a[N][N]={{1,0,1},{0,1,0},{1,1,0}};
   wallshall(a,N);
   return 0;	
}
int wallshall(int a[N][N],int n){
    int W[n][n];
    memcpy(W,a,n*n*sizeof(int));
	int i,j,k;
	for(k=0;k<n;k++)
		for(i=0;i<n;i++)
			for(j=0;j<n;j++)
               W[i][j]=W[i][j]||(W[i][k]&&W[k][j]);
    for(i=0;i<n;i++){
    	for(j=0;j<n;j++){
    		printf("%d", W[i][j]);
    	}
    	printf("\n");
    }
}