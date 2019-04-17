#include<iostream>
#include<vector>
#include<string> 
using namespace std;

int modular_exponentiation(int a,int b,int n)
{
	int c=0;
	int d=1;
	vector<int>B;
	while(b>0)
	{  
	   B.push_back(b&1);
	   b>>=1;
	}
	for(int i=B.size()-1;i>=0;i--)
	{
		c=2*c;
		d=(d*d)%n;
		if(B[i]==1)
		{
			c=c+1;
			d=(d*a)%n;
		}
	}
	return d;
}

bool is_equal(vector<int>P,vector<int>T,int p,int t,int m)
{
	if(P.size()<m+p-1||T.size()<t+m-1)
	{
		return false;
	}
	for(size_t i=0;i<m;i++)
	{
		if(T[p+i]!=T[t+i])
		   return false;
	}
	return true;
}
//基于模的字符匹配算法 
void rabin_karp_matcher(vector<int>T,vector<int>P,int d,int q)
{
    int n=T.size();
	int m=P.size();
	int h=modular_exponentiation(d,m-1,q);
	cout<<n<<'\t'<<m<<'\t'<<h<<endl;
	int p=0;
	int t=0;
	for(size_t i=0;i<m;i++)
	{
		p=(d*p+P[i])%q;
		t=(d*t+T[i])%q;
	}
	for(size_t s=0;s<=n-m;s++)
	{   
		if(p==t)
		{   
			if(is_equal(T,P,0,s,m))
			   cout<<"Pattern occurs with shift"<<s<<endl;
		    else
			   cout<<"fake!"<<s<<endl; 
		}
		if(s<n-m)
		{
		  t= (d*(t-T[s]*h)+T[s+m]) % q;	
		  t=t>0?t:t+q;
		}
	}
}

//KMP算法，生成模式匹配
vector<int> compute_perfix_function(string P)
{  
   int m=P.size();
   cout<<m<<endl;
   vector<int>p(m,0);
   int k=0;
   for(size_t q=1;q<m;q++)
   {
   	   while(k>0 &&P[k]!=P[q])
   	      k=p[k-1];
   	   if(P[k]==P[q])
   	      k++;
   	   p[q]=k;
   } 
   return p;
} 
//KMP算法主体
void kmp_matcher(string T,string P)
{
	int n=T.size();
	int m=P.size();
	vector<int> pi=compute_perfix_function(P);
	int q=-1;
	for(size_t i=0;i<n;i++)
	{
		while(q>=0&&P[q+1]!=T[i])
		   q=pi[q];
	    if(P[q+1]==T[i])
	       q=q+1;
	    if(q==m-1){
	    	cout<<"Pattern occurs with shift: "<<i-m+1<<endl;
	    	q=pi[q];//如果T.length<P.length，这个会出错 
		}   
	}
} 
int main()
{   
    //vector<int> T={3,1,4,1,5,9,2,6,5,3,5,8,9,7,9,3};
    //vector<int> P={2,6};
    //rabin_karp_matcher(T,P,10,11);
    vector<int> ans=compute_perfix_function("pwwkew");
    for(size_t i=0;i<ans.size();i++)
    {
    	cout<<ans[i]<<",";
	}
    //kmp_matcher("abcabcbb","abcabcbb");
	return 0;
}
