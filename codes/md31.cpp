
#include <iostream>
#include <math.h>
using namespace std;
//位运算的乘法
int bit_Multiplication(int a,int b)
{
     int ans=0;
	 for (int i=1;i;i<<=1,a<<=1)
	 {
		 if (b&i)
		 {
			 ans+=a;
		 }
	 }
	 return ans;
}
//位运算的除法
int bit_Division1(int x,int y)
{
    int ans=0;
	for (int i=31;i>=0;i--)
	{   
		if ((x>>i)>=y)
		{
			ans+=(1<<i);
			x-=(y<<i);
		}
	}
	return ans;
}
//计算整数的二进制位数
int bit_num(int d)
{
   int i=0;
   while (d)
   {
	   d>>=1;
	   i++;
   }
   return i;
}
//位运算的除法 计算商
int bit_Division2_quotient(int x,int y)
{
	int c2=bit_num(x),c1=bit_num(y),quotient=0;
	for (int i=c2-c1;i>=0;i--)//i=c2-c1防止除数y移位后超过无符号整数最大值 时间复杂度O(c2-c1)
	{
		unsigned int a=(y<<i);//有了i=c2-c1保证了y<<i不会溢出 a有c1+c2-c1=c2位
		if (a<=x)
		{
			quotient+=(1<<i);
			x-=a;
		}
	}
	//总的时间复杂度为 O(c2)=O(x的二进制位数)=O(b^2) b为除数的十进制位数
	return quotient;
}
//位运算的除法 计算余数 与计算商一样，只是返回值不同
int bit_Division2_Remainder(int x,int y)
{
	int c2=bit_num(x),c1=bit_num(y),quotient=0;
	for (int i=c2-c1;i>=0;i--)//i=c2-c1防止除数y移位后超过无符号整数最大值 时间复杂度O(c2-c1)
	{   
		unsigned int a=(y<<i);//有了i=c2-c1保证了y<<i不会溢出 a有c1+c2-c1=c2位
		cout<<i<<'\t'<<a<<'\t'<<x<<endl;
		if (a<=x)
		{
			//quotient+=(1<<i);
			x-=a;
		}
	}
	//总的时间复杂度为 O(c2)=O(x的二进制位数)=O(b^2) b为除数的十进制位数
	return x;
}
int main()
{
	cout<<bit_Multiplication(789,43)<<endl;
	cout<<bit_Division1(789,43)<<endl;
	cout<<"商："<<bit_Division2_quotient(350,43)<<endl;
	cout<<"余数："<<bit_Division2_Remainder(789,43)<<endl;
	return 0;
}
//int main()
//{
//    long long  n;
//	int flag=1;
//    cout<<"enter:"<<endl;
//    cin>>n;
//	//O(√nlgn)
//    for (int i=2;i<=sqrt(n);i++)//O(a=√n)
//	{
//		int m=n,k=0;
//		while (m%i==0)//O(k=lgn)
//		{
//			m=m/i;
//			k++;
//		}
//		if (m==1&&k>1)
//		{
//			cout<<n<<"是非平凡幂,存在一个整数"<<i<<"它的"<<k<<"次幂="<<n<<endl;
//			flag=0;
//			break;
//		}
//	}
//	if (flag)
//	{
//		cout<<"n="<<n<<"不存在非平凡幂"<<endl;
//	}
//	return 0;
//}

