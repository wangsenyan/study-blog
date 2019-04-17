#include<iostream>
#define N 6
using namespace std;
void floyed_warshall(int (*a)[N]);
int main()
{   
int a[N][N]={
	{0,INT_MAX,INT_MAX,INT_MAX,-1,INT_MAX},
	{1,0,INT_MAX,2,INT_MAX,INT_MAX},
	{INT_MAX,2,0,INT_MAX,INT_MAX,-8},
	{-4,INT_MAX,INT_MAX,0,3,INT_MAX},
	{INT_MAX,7,INT_MAX,INT_MAX,0,INT_MAX},
	{INT_MAX,5,10,INT_MAX,INT_MAX,0}
	};
	floyed_warshall(a);
	return 0;
}

void floyed_warshall(int (*a)[N])
{
   //int n=N;
   int b[N][N];
   int i,j,k,tmp;
   for(k=0;k<=N;k++){
   	  memcpy(b,a,sizeof(b));
   	  for(i=0;i<N;i++){
        for(j=0;j<N;j++)
         {
         	if(a[i][j]==INT_MAX)
         	  cout<<">>"<<'\t';
         	else
         	  cout<<a[i][j]<<'\t';
		 }
        cout<<endl;
      }
     cout<<"---------------------------------"<<endl;
   	  for(i=0;i<N;i++){
     	for(j=0;j<N;j++)
	       {  
	          if(a[i][k]<INT_MAX&&a[k][j]<INT_MAX){
	          	  tmp=a[i][k]+a[k][j];
	       	      if(tmp<a[i][j])
	       	         a[i][j]=tmp;
			  }
		   }
	 }
   }
}
