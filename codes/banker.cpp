#include<iostream>
using namespace std;
#define p 5
#define r 4

void input(int max[p][r],int allocation[p][r],int need[p][r],int available[r])
{
	int i,j;
	cout<<"* input max data:\n";
	for(i=0;i<p;i++)
	  for(j=0;j<r;j++)
	     cin>>max[i][j];
	
	cout<<"* input allocation data:\n";
	for(i=0;i<p;i++)
	  for(j=0;j<r;j++)
	     cin>>allocation[i][j];
    
    cout<<"* input need data:\n";
	for(i=0;i<p;i++)
	  for(j=0;j<r;j++)
	     cin>>need[i][j];

   	cout<<"* input available data:\n";
	for(j=0;j<r;j++)
	     cin>>available[j];
}

bool com(int m[r],int n[r])
{
	int i;
	for(i=0;i<r;i++)
	   if(m[i]<n[i])
	      return false;
	return true;
}

bool stest(int allocation[p][r],int need[p][r],int available[r] )
{
	int i,j,k,l,flag=0,flag1=0;
	int t[r],finish[p],work[r];
	for(i=0;i<p;i++)
	   finish[i]=0;
	for(i=0;i<r;i++)
	   work[i]=available[i];
	
	cout<<"分配序列:\n";
	for(k=0;k<p;k++)
	{
		for(i=0;i<p;i++)
		{
			
			if(finish[i]==1)
			{  
				continue;
			}
			else 
			{
				for(j=0;j<r;j++)
				  t[j]=need[i][j];
				if(com(work,t))
				{
					finish[i]=1;
					cout<<i+1<<"\t";
					flag=1;
					for(l=0;l<r;l++)
					   work[l]=work[l]+allocation[i][l];
					break;
				}
			}
			if(flag==1) break;
		}
	}
	cout<<"\n";
	for(l=0;l<p;l++)
	   if(finish[l]==0)
	      flag1=1;
	if(flag1==0)
	   return true;
	else 
	   return false;
}


void rtest(int allocation[p][r],int need[p][r],int available[r],int req[r],int n)
{
	int i,j;
	int t[r];
	n=n-1;
	for(i=0;i<r;i++)
	  t[i]=need[n][i];
	if(com(available,req)&&com(t,req))
	{
		for(j=0;j<r;j++)
		{
			allocation[n][j]=allocation[n][j]+req[j];
			need[n][j]=need[n][j]-req[j];
			available[j]=available[j]-req[j];
		}
		if(stest(allocation,need,available))
		   cout<<"允许"<<n+1<<"个进程申请资源！\n";
		else
		{
			cout<<"不允许"<<n+1<<"个进程申请资源！\n";
		    cout<<"恢复以前状态！\n";
		    for(j=0;j<r;j++)
			{
				allocation[n][j]=allocation[n][j]-req[j];
				need[n][j]=need[n][j]+req[j];
				available[j]=available[j]+req[j];
			}
		}
	}else
	{
	   cout<<"申请资源量出错！\n";
	}
}


int main()
{
	int j,n;                   //n-第n个资源申请
	int max[p][r],allocation[p][r],need[p][r];
	int available[r],request[r];
	input(max,allocation,need,available);
 
	if(stest(allocation,need,available)==1)cout<<"初始状态安全！\n";
	else cout<<"初始状态不安全！\n";
 
	cout<<" input request data:\n";
	for(j=0;j<r;j++)cin>>request[j];
    //此处多线程 互斥锁 
	cout<<"第n个进程申请资源——n的值\n";
	cin>>n;
	
	rtest(allocation,need,available,request,n);
	return 0;
}


