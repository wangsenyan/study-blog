#include <cstdio>
#include <climits>
#include <cstdlib>
#include <iostream>
#include <cstring>
#include  <vector>
#include  <fstream>
#include <set>
using namespace std;
//vector<vector<double>> Matrix;
typedef struct {
   vector<vector<double>> Matrix;
   set<int> N;
   set<int> B;
   vector<double> b;
   vector<double> c;
   double v;
} __pivot;
//double Z;
//set<int> P;
size_t m,n;
int find(vector<int> vet, int ele){
	int i,j=-1;
	for(i=0;i<vet.size();i++)
	{
		if(vet[i]==ele)
		  j=i;
	}
	return j;
}
void show(set<int> N,set<int> B,vector<vector<double>>a,vector<double> b,vector<double> c,double v)
{   
    size_t i,k;
    cout<<"set N: "<<endl;
	for(set<int>::iterator j=N.begin();j!=N.end();j++)
	{   
	    cout<<*j<<'\t';
	}
	cout<<endl;
	
	cout<<"set B: "<<endl;
	for(set<int>::iterator j=B.begin();j!=B.end();j++)
	{   
	    cout<<*j<<'\t';
	}
	cout<<endl;
	
	cout<<"matrix a: "<<endl;
	for(i=0;i<a.size();i++)
	{
		for(k=0;k<a[0].size();k++)
		{
			cout<<a[i][k]<<'\t';
		}
		cout<<endl;
	}
	cout<<endl;
	
	cout<<"vector b: "<<endl;
	for(i=0;i<b.size();i++)
	{
		cout<<b[i]<<'\t';
	}
	cout<<endl;
	
	cout<<"vector c: "<<endl;
	for(i=0;i<c.size();i++)
	{
		cout<<c[i]<<'\t';
	}
	cout<<endl;
	
	cout<<"property v=: "<<v<<endl;
}
__pivot Pivot(__pivot pt,int l,int e)
{   cout<<endl<<l<<'\t'<<e<<endl;
    //show(N,B,a,b,c,v);
    show(pt.N,pt.B,pt.Matrix,pt.b,pt.c,pt.v);
   // __pivot p;
	pt.b[e]=pt.b[l]/pt.Matrix[l][e];
	for(set<int>::iterator j=pt.N.begin();j!=pt.N.end();j++)
	{   
	    if(*j!=e){
	       pt.Matrix[e][*j]=pt.Matrix[l][*j]/pt.Matrix[l][e];
	      // cout<<"a["<<e<<"]["<<*j<<"]="<<a[e][*j]<<endl;
		}
	}
	pt.Matrix[e][l]=1/pt.Matrix[l][e];
	for(set<int>::iterator i=pt.B.begin();i!=pt.B.end();i++)
	{
		if(*i!=l)
		{
		  pt.b[*i]=pt.b[*i]-pt.Matrix[*i][e]*pt.b[e];
		  for(set<int>::iterator j=pt.N.begin();j!=pt.N.end();j++)
		  {
		  	if(*j!=e)
		  	{
		  	   pt.Matrix[*i][*j]=pt.Matrix[*i][*j]-pt.Matrix[*i][e]*pt.Matrix[e][*j];	
			}
		  }
		}
		pt.Matrix[*i][l]=-pt.Matrix[*i][e]*pt.Matrix[e][l];
	}
	
	pt.v=pt.v+pt.c[e]*pt.b[e];
	for(set<int>::iterator j=pt.N.begin();j!=pt.N.end();j++)
	{
		if(*j!=e)
		{
			pt.c[*j]=pt.c[*j]-pt.c[e]*pt.Matrix[e][*j];
		}
	}
	pt.c[l]=-pt.c[e]*pt.Matrix[e][l];
	pt.N.erase(e);
	pt.N.insert(l);
	pt.B.erase(l);
	pt.B.insert(e);
	//cout<<"____________________________________________"<<endl;
	return pt;
}
__pivot initialize_simplex(vector<vector<double>> &A,vector<double>&b,vector<double>&c)
{   
//    __pivot p;
//    int k=0;
//    for(i=1;i<b.size();i++)
//    {
//    	if(b[k]>b[i])
//    	  k=i;
//	}
//	if(b[k]>=0)
//	{
//		
//	}
   // cout<<A[0][0]<<" "<<A[0][1]<<" "<<A[1][0]<<" "<<A[1][1]<<endl;
	__pivot p;
	int k=m+n;
	size_t i,j;
	p.b.resize(k);
	p.c.resize(k);
	for(i=0;i<k;i++)
	{   
	    if(i<n)
	    {
	    	p.b[i]=0;
		}else{
			p.b[i]=b[i-n];
			p.B.insert(i); 
		}
	}
	for(i=0;i<k;i++)
	{   
	    if(i<n){
	    	p.c[i]=c[i];
	    	p.N.insert(i);
		}
	    else{
	    	p.c[i]=0;
		}
	}

    p.Matrix.resize(k);
    for(i=0;i<k;i++)
      p.Matrix[i].resize(k);
    //cout<<k<<"?????";
	for(i=0;i<k;i++)
	{  
		for(j=0;j<k;j++)
		{   
		    if(i>n-1&&j<=n-1){
		    	//cout<<i<<" "<<j<<endl;
		    	p.Matrix[i][j]=A[i-n][j];
			}else{
				p.Matrix[i][j]=0;
			}	
		}
	}
	p.v=0;
	//show(p.N,p.B,p.Matrix,p.b,p.c,p.v);
    return p;
}
vector<double> simplex(vector<vector<double>> A,vector<double>b,vector<double>c)
{
	__pivot pt=initialize_simplex(A,b,c);
	vector<double> d;
	vector<double> x;
	//show(pt.N,pt.B,pt.Matrix,pt.b,pt.c,pt.v);
	int n=pt.Matrix[0].size();
	d.resize(n);
	x.resize(n);
	size_t i,j,k;
	int l,e;
	for(i=0;i<n;i++)
	{
		d[i]=INT_MAX;
	}
	for(j=0;j<n;j++)
	{   
		if(pt.N.find(j)!=pt.N.end()&&pt.c[j]>0)
		{   
		    e=j;
			for(set<int>::iterator it=pt.B.begin();it!=pt.B.end();++it)
			{   
				if(pt.Matrix[*it][e]>0)
				{   
					d[*it]=pt.b[*it]/pt.Matrix[*it][e];
				}
			}
			double min=INT_MAX;
			for(i=0;i<n;i++)
		    {   
		        //cout<<"---------: "<<d[i]<<'\t';
				if(pt.B.find(i)!=pt.B.end()&&d[i]<min)
				{   
				    min=d[i];
					l=i;
				}
		    }
		    if(d[l]==INT_MAX)
			{   
			    cout<<"unbounded"<<endl;
				exit(1);
			}else{
			  pt=Pivot(pt,l,e);
			 //Pivot(pt.N,pt.B,pt.Matrix,pt.b,pt.c,l,e);
			  j=0;
	    	}	
		}
	}
	for(i=0;i<n;i++)
	{
		if(pt.B.find(i)==pt.B.end())
		{
			x[i]=b[i];
		}else
		{
			x[i]=0;
		}
	}
	show(pt.N,pt.B,pt.Matrix,pt.b,pt.c,pt.v);
	return x;

}
int main(int argc, char *argv[])
{  
    vector<vector<double>> A;
    vector<double> b={3,13,5};
    vector<double> c={1,1,-1};
    double v=-3;
    ifstream fin;
    fin.open("./test.txt");
    fin>>n>>m;
    for(size_t i = 0 ; i < m ; i++ )
    {   
        vector<double> vectmp;
        for( size_t j = 0 ; j < n ; j++)
        {
            double tmp = 0;
            fin>>tmp;
            vectmp.push_back(tmp);
        }
       A.push_back(vectmp);
    }
    __pivot pt=initialize_simplex(A,b,c);
    __pivot p=Pivot(pt,4,0);
    show(p.N,p.B,p.Matrix,p.b,p.c,p.v);
    
    //vector<double> x=simplex(A,b,c);
//    for(size_t i=0;i<x.size();i++)
//      cout<<x[i]<<'\t';
    //__pivot pt=initialize_simplex(A,b,c);
    //show(pt.N,pt.B,pt.Matrix,pt.b,pt.c,pt.v);
}

