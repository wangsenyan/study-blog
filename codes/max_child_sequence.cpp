#include<iostream>
using namespace std;
void printSequence(int *b,int* nums,int last);
int main()
{
	int n=8;
	int nums[9]={0,1,7,8,9,2,3,4,5};
	//b存储当前元素所在递增子序列中当前元素的前一个元素序号
	//c存储以当前元素结尾的递增子序列长度
	//last存储当前元素为止的序列中最长递增子序列的最后一个元素的序号
	//maxLen存储当前最长递增子序列的长度
	int b[9]={0},c[9]={0},last[9]={0},maxLen=0;
	c[1]=1,last[1]=1;
	for (int i=1;i<=n;i++)
	{
		for (int j=1;j<i;j++)
		{
			if(nums[j]<nums[i] && c[j]+1>c[i])
			{
				c[i]=c[j]+1;
				b[i]=j;
				last[i]=i;
				maxLen=c[i];
			}else if(c[j]>c[i]){
				maxLen=c[j];
				last[i]=last[j];
			}
		}
	}
	cout<<"原序列长度为"<<n<<"，如下："<<endl;
	for (int i=1;i<=n;i++)
	{
		cout<<nums[i]<<" ";
	}
	cout<<endl<<"最长递增子序列长度为"<<maxLen<<"，如下："<<endl;
	printSequence(b,nums,last[n]);
	cout<<endl;
	return 0;
}
 
void printSequence(int *b,int* nums,int last)
{
	if(b[last]>0)
		printSequence(b,nums,b[last]);
	cout<<nums[last]<<" ";
}
