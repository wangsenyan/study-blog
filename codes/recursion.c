#include<stdio.h>
int recursion(int b,int n,int m);
int gcd(int a,int b);
int search(int i,int j,int x);
unsigned int fibonacci(int n);
int main(void)
{
   unsigned int a=fibonacci(100);
   printf("%u\n",a );
   return 0;
}
int recursion(int b,int n,int m){
  int ans=0;
  if(n==0)
   ans=1;
  else if(n%2==0)
   ans=(recursion(b,n/2,m)*recursion(b,n/2,m))%m;
  else 
   ans=(((recursion(b,n/2,m)*recursion(b,n/2,m))%m)*b%m)%m;
  return ans;
}
int gcd(int a,int b){
   if(a==0)
   	 return b;
   else
   	 return gcd(b%a,a);
}
int search(int i,int j,int x){
	int a[10]={2,4,6,7,4,8,9,4,3,5};
	if(a[i]==x)
	   return i;
	else if(i==j)
	   return 0;
	else
	   return search(i+1,j,x);
}

unsigned int fibonacci(int n){
	int y,x,z;
	if(n==0)
      y=0;
    else{
      x=0;
      y=1;
      for(int i=1;i<n;i++){
      	z=x+y;
      	x=y;
      	y=z;
      }
    }
    return y;
}

float *mergesort(float *list,int n){
   if(n>1){
   	  int temp=n/2-1;
   	  float L1[temp]={0};
   	  float L2[temp]={0};
   	  memcpy(L1,list,temp*sieof(float));
   	  memcpy(L2,list+temp+1,(n-temp)*sieof(float));
   	  return merge(mergesort(L1,temp),mergesort(L2,n-temp));
   }
   return list;
}
