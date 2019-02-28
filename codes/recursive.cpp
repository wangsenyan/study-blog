#include<algorithm>
#include<iostream>
#include <vector>
#include<cmath>
using namespace std;
void Recursive_Activity_Selector(int *s,int *f,int k,int n)
{   
	int m=k+1;
	while(m<=n&&s[m]<f[k])
	    m++;
	if(m<=n)
	{
		cout<<m<<endl;
		Recursive_Activity_Selector(s,f,m,n);
	}
}


void Greedy_Activity_Selector(int *s,int *f,int n)
{
	cout<<1<<endl;
	int k=1;
	for(int m=2;m<=n;m++)
	  if(s[m]>=f[k])
	  {
	  	cout<<m<<endl;
	  	k=m;
	  }
}

dp(int *s,int *f,int n)
{
	
}
int main()
{
	int s[12]={0,1,3,0,5,3,5,6,8,8,2,12};
	int f[12]={0,4,5,6,7,9,9,10,11,12,14,16};
	Greedy_Activity_Selector(s,f,11); 
	//Recursive_Activity_Selector(s,f,0,11);
	return 0; 
}
