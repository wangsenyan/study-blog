#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
#define pi 3.1415926535
struct Complex
{
	double imag;
	double real;
	Complex(double r=0,double i=0){
		if(i<0.000001)
		  i=0;
		if(r<0.000001)
		  r=0;
		imag=i;
		real=r;
	}
};
vector<Complex>a;
Complex operator*(Complex const &lhs,Complex const &rhs)
{
	Complex temp;
	temp.real=lhs.real*rhs.real-lhs.imag*rhs.imag;
	temp.imag=lhs.real*rhs.imag+lhs.imag*rhs.real;
	return temp;
}
Complex operator+(Complex const &lhs,Complex const &rhs)
{
	Complex temp;
	temp.real=lhs.real+rhs.real;
	temp.imag=lhs.imag+rhs.imag;
	return temp;
}
Complex operator-(Complex const &lhs,Complex const &rhs)
{
	Complex temp;
	temp.real=lhs.real-rhs.real;
	temp.imag=lhs.imag-rhs.imag;
	return temp;
}
void show(vector<Complex>A)
{    
	for(int t=0;t<A.size();t++)
	{
		cout<<A[t].real;
		if(fabs(A[t].imag)<0.001)
		{
			cout<<endl;
			continue;
		}else{
			if(A[t].imag<0)
			{
				cout<<A[t].imag<<"i";
			}else{
				cout<<"+"<<A[t].imag<<"i";
			}
		}
		cout<<endl;
	}
}
vector<Complex> BIT_REVERSE_COPY(vector<Complex>&a,vector<Complex>&A)
{
	//show(a);
	unsigned n=a.size();
	for(unsigned i=0,j=0;i<n;i++)
	{
		A[j]=a[i];
		unsigned bit=~i&(i+1);
		unsigned rev=(n/2)/bit;
		j^=(n-1)&~(rev-1);
	}
	//show(A);
	return A;
}

int Log(int n)
{
	int temp=0;
	while(n>>=1) 
	  temp++;
	return temp;
}

vector<Complex>ITERATIVE_FFT(vector<Complex>&a,vector<Complex>&A)
{  
	BIT_REVERSE_COPY(a,A);
	
	size_t n=a.size();
	for(int s=1;s<=Log(n);s++)
	{   show(A);
		int m=pow(2,s);
		Complex wm(cos(2*pi/m),sin(2*pi/m));
		cout<<wm.real<<'\t'<<wm.imag<<endl;
		for(int k=0;k<=n-1;k+=m)
		{   
			Complex w(1,0),t,u;
			for(int j=0;j<=m/2-1;j++)
			{
				t=w*A[k+j+m/2];
				u=A[k+j];
				A[k+j]=u+t;
				A[k+j+m/2]=u-t;
				w=w*wm;
			}
		}
	}
	return A;
}

int main()
{
	Complex x,y;
	int i;
	while(cin>>x.real>>x.imag)
	{   
	    cout<<"continue:"<<endl;
		a.push_back(x);
		i++;
	}
	vector<Complex>A(i,y);
	vector<Complex>ans=ITERATIVE_FFT(a,A);
	show(A);
	return 0;
}































