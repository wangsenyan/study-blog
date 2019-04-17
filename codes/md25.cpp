#include<iostream>
#define N 6
using namespace std; 
//int **find_short_path(int** a,int n);
//void quik_find_short_path(int (*a)[N],int n);
int slow_find_short_path(int (*a)[N],int (*b)[N],int n);
static int m=0;
int main(){
	int a[N][N]={
	{0,INT_MAX,INT_MAX,INT_MAX,-1,INT_MAX},
	{1,0,INT_MAX,2,INT_MAX,INT_MAX},
	{INT_MAX,2,0,INT_MAX,INT_MAX,-8},
	{-4,INT_MAX,INT_MAX,0,3,INT_MAX},
	{INT_MAX,7,INT_MAX,INT_MAX,0,INT_MAX},
	{INT_MAX,5,10,INT_MAX,INT_MAX,0}
	};
	slow_find_short_path(a,a,N);
	return 0;
}

int slow_find_short_path(int (*a)[N],int (*b)[N],int n)
{
	m++;
	int i,j,k,min;
	int c[N][N];
	for(i=0;i<n;i++)
	   for(j=0;j<n;j++){
	   	 min=INT_MAX;
	   	 for(k=0;k<n;k++)
	   	 {  
	   	    if(a[i][k]<INT_MAX&&b[k][j]<INT_MAX)
	   	    {
	   	    	int tmp=a[i][k]+b[k][j];
	   	 	    if(tmp<min)
	   	 	      min=tmp;
		    }
		    c[i][j]=min;
	     }
	   }  
	for(i=0;i<n;i++)
	{
	  	for(j=0;j<n;j++)
	  	  cout<<c[i][j]<<"\t";
	    cout<<endl;
    }
    if(m<n)
      slow_find_short_path(c,b,n);
    return 0;
}
//void quik_find_short_path(int (*a)[N],int n)
//{   
//    m++;
//	int i,j,k,min;
//	//int **b=new int(*)[N];
//	int b[N][N];
//	for(i=0;i<n;i++)
//	   for(j=0;j<n;j++){
//	   	 min=INT_MAX;
//	   	 for(k=0;k<n;k++)
//	   	 {  
//	   	    if(a[i][k]<INT_MAX&&a[k][j]<INT_MAX)
//	   	    {
//	   	    	int tmp=a[i][k]+a[k][j];
//	   	 	    if(tmp<min)
//	   	 	      min=tmp;
//		    }
//		    b[i][j]=min;
//	     }
//	   }  
//	for(i=0;i<n;i++)
//	{
//	  	for(j=0;j<n;j++)
//	  	  cout<<b[i][j]<<"\t  ";
//	    cout<<endl;
//    }
//    if(m<n)
//      quik_find_short_path(b,n);
//   // return;
//}
