#include <iostream>
using namespace std;
 
#define N 6
int x[N+1]={0,10,40,60,90,120,140},f[N+1]={0};//f用于标记某一站是否加油，x[i]表示第i个加油站距离起始点的距离
void Greedy_Select(int x[],int f[])//选择在哪一个加油站停车
{
	int n=30;//邮箱满的时候，能够跑的英里数
	for(int i=2;i<=N;++i)
	{
		if(x[i]>n)//如果起始点到某个加油站的距离大于汽车在邮箱满的时候能够走的公里数，则在前一站加油
		{
			f[i-1]=1;//标记前一站需要加油
			n=30;
			n=n+x[i-1];//改变当前的距离，因为在第i-1站已经加过油
		}
	}
}
 
void Construct_Opitimal_Solution(int x[],int f[])//输出需要在哪一站加油
{
	for(int i=1;i<=N;++i)
	{
		if(f[i]==1)
			cout<<"The gas station "<<i<<" is chosen! And its distance is "<<x[i]<<endl;
	}
}
 
int main()
{
	Greedy_Select(x,f);
	Construct_Opitimal_Solution(x,f);
	return 0;
}
