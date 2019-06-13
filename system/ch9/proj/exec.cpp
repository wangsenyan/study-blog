//2,0,-1,0
//+,3,*,3
#include <iostream>
#define N 6
using namespace std;
int a[N] = {-1, 0,0,0,1,1};
int b[N] = {'+','*',2, 3,0,7};
int add(int i);
int exec();
int main()
{
  int n = N;
  int s = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == -1)
    {
      s = i;
      break;
    }
  cout<<s<<endl;
  cout<<exec();
}

int exec()
{
  int n = N;
  int s = 0;
  for (int i = 0; i < n; i++)
    if (a[i] == -1)
    {
      s = i;
      break;
    }
  return add(s);
}

int add(int i)
{
  int ans = 0;
  if (b[i] == '*')
  {
    ans = 1;
    for (int j = 0; j < N; j++)
    {
      if (a[j] == i)
        ans *= add(j);
    }
  }else if (b[i] == '+')
  {
    for (int j = 0; j < N; j++)
    {
      if (a[j] == i)
        ans += add(j);
    }
  }else
    return b[i];
  return ans;
}
