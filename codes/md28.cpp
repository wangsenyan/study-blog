#include<iostream>
#include <math.h>
#include <Eigen3>
#define N 5
#define M 1
using namespace std;
void Lu_decomposition(int (*a)[N]);
void showMatries(double (*a)[N]);
void Lup_decomposition(double (*a)[N]);
double abs(double x);
void matrix_multi(double (*a)[N],double (*b)[M],int r,int c);
int main()
{   
    //double A[5][3]={{1,-1,1},{1,1,1},{1,2,4},{1,3,9},{1,5,25}};
    double B[3][5]={{0.5,0.3,0.2,0.1,-0.1},
	{-0.388,0.093,0.190,0.193,-0.088},
	{0.060,-0.036,-0.048,-0.036,0.060}};
    double A[5][1]={2,1,1,0,3};
    matrix_multi(B,A,3,1);
	//Lu_decomposition(A);
    //Lup_decomposition(B);
	return 0;
}

void Lu_decomposition(int (*a)[N])
{
	int n=N;
	int i,j,k;
	int l[N][N],u[N][N];
	for(i=0;i<n;i++)
	{
		l[i][i]=u[i][i]=1;
		for(j=0;j<i;j++)
        {
        	l[i][j]=1;
        	u[i][j]=0;
		}
		for(j=i+1;j<n;j++)
		{
			l[i][j]=0;
        	u[i][j]=1;
		}
	}
	
    for(k=0;k<n;k++)
    {   
        //showMatries(a);
    	u[k][k]=a[k][k];
    	for(i=k+1;i<n;i++)
    	{
    		l[i][k]=a[i][k]/u[k][k];
    		u[k][i]=a[k][i];
		}
		for(i=k+1;i<n;i++)
		{
			for(j=k+1;j<n;j++)
			{
				a[i][j]=a[i][j]-l[i][k]*u[k][j];
			}
		}
	}
    //showMatries(l);
    //showMatries(u);
    //showMatries(a);
}

void Lup_decomposition(double (*a)[N])
{
	int n=N;
	int pi[n];
	int i,j,k,ki,itmp;
	for(i=0;i<n;i++)
	  pi[i]=i;
	for(k=0;k<n;k++)
	{
		double p=0;
		for(i=k;i<n;i++)
		{
			if(abs(a[i][k])>p)
			{
				p=abs(a[i][k]);
				ki=i;
			}
		}
		if(p==0)
	    {
	    	cout<<"singular matrix"<<endl;
		}
		itmp=pi[k];
		pi[k]=pi[ki];
		pi[ki]=itmp;
		double dtmp;
		for(i=0;i<n;i++)
		{
		  dtmp=a[k][i];
		  a[k][i]=a[ki][i];
		  a[ki][i]=dtmp;
		}
		for(i=k+1;i<n;i++)
		{
			a[i][k]=a[i][k]/a[k][k];
			for(j=k+1;j<n;j++)
			{
				a[i][j]=a[i][j]-a[i][k]*a[k][j];
			}
		}
	} 
	showMatries(a);
}


void showMatries(double (*a)[N])
{
	int i,j;
	for(i=0;i<N;i++){
	  for(j=0;j<N;j++)
	  {
	  	cout<<a[i][j]<<'\t';
	  }	
	cout<<endl;
	}
	cout<<endl;
}

double abs(double x)
{
	if(x<0)
	  return -x;
	else
	  return x;
}

void matrix_multi(double (*a)[N],double (*b)[M],int r,int c)
{
	double T[r][M];
	int i,j,k;
	for(i=0;i<r;i++)
	{
		for(j=0;j<M;j++)
		{
			T[i][j]=0;
			for(k=0;k<M;k++)
			  T[i][j]=a[i][k]*b[k][j];
		}
	}
	for(i=0;i<r;i++){
	  for(j=0;j<M;j++)
	  {
	  	cout<<a[i][j]<<'\t';
	  }	
	cout<<endl;
	}
	cout<<endl;
}

