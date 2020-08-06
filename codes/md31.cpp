
#include <iostream>
#include <math.h>
#include <vector>
using namespace std;
//位运算的乘法
int bit_Multiplication(int a, int b)
{
  int ans = 0;
  for (int i = 1; i; i <<= 1, a <<= 1)
  {
    if (b & i)
    {
      ans += a;
    }
  }
  return ans;
}
//位运算的除法
int bit_Division1(int x, int y)
{
  int ans = 0;
  for (int i = 31; i >= 0; i--)
  {
    if ((x >> i) >= y)
    {
      ans += (1 << i);
      x -= (y << i);
    }
  }
  return ans;
}
//计算整数的二进制位数
int bit_num(int d)
{
  int i = 0;
  while (d)
  {
    d >>= 1;
    i++;
  }
  return i;
}
//位运算的除法 计算商
int bit_Division2_quotient(int x, int y)
{
  int c2 = bit_num(x), c1 = bit_num(y), quotient = 0;
  for (int i = c2 - c1; i >= 0; i--) //i=c2-c1防止除数y移位后超过无符号整数最大值 时间复杂度O(c2-c1)
  {
    unsigned int a = (y << i); //有了i=c2-c1保证了y<<i不会溢出 a有c1+c2-c1=c2位
    if (a <= x)
    {
      quotient += (1 << i);
      x -= a;
    }
  }
  //总的时间复杂度为 O(c2)=O(x的二进制位数)=O(b^2) b为除数的十进制位数
  return quotient;
}
//位运算的除法 计算余数 与计算商一样，只是返回值不同
int bit_Division2_Remainder(int x, int y)
{
  int c2 = bit_num(x), c1 = bit_num(y), quotient = 0;
  for (int i = c2 - c1; i >= 0; i--) //i=c2-c1防止除数y移位后超过无符号整数最大值 时间复杂度O(c2-c1)
  {
    unsigned int a = (y << i); //有了i=c2-c1保证了y<<i不会溢出 a有c1+c2-c1=c2位
    cout << i << '\t' << a << '\t' << x << endl;
    if (a <= x)
    {
      //quotient+=(1<<i);
      x -= a;
    }
  }
  //总的时间复杂度为 O(c2)=O(x的二进制位数)=O(b^2) b为除数的十进制位数
  return x;
}

vector<int> EXTENDED_EUCLID(int a, int b)
{
  std::vector<int> ans;
  int tmp;
  if (b == 0)
  {
    ans.push_back(a);
    ans.push_back(1);
    ans.push_back(0);
  }
  else
  {
    ans = EXTENDED_EUCLID(b, a % b);
    tmp = ans[1] - (a / b) * ans[2];
    ans[1] = ans[2];
    ans[2] = tmp;
  }
  cout << a << '\t' << b << '\t' << '\t' << ans[0] << '\t' << ans[1] << '\t' << ans[2] << endl;
  return ans;
}

void EXTENDED_EUCLID_MULTIPLE(vector<int> a)
{
  int n = a.size();
  if (n == 1)
  {
    cout << a[0] << '\t' << 0 << endl;
  }
  else
  {
    int g = a[n - 1];
    vector<int> x(n, 1);
    vector<int> y(n, 0);
    vector<int> s;
    for (int i = n - 2; i >= 0; i--)
    {
      s = EXTENDED_EUCLID(a[i], g);
      cout << a[i] << '\t' << g << endl;
      cout << s[0] << '\t' << s[1] << '\t' << s[2] << endl;
      g = s[0];
      x[i] = s[1];
      y[i + 1] = s[2];
    }
    int m = 1;
    for (int i = 1; i <= n; i++)
    {
      m *= y[i];
      x[i] *= m;
    }
    for (int i = 0; i <= n; i++)
    {
      cout << x[i] << '\t' << y[i] << endl;
    }
  }
}

int gcd(int a, int b)
{
  if (b == 0)
    return a;
  return gcd(b, a % b);
}

int lcm(int a, int b)
{
  return a / gcd(a, b) * b;
}

int lcm_multiple(vector<int> a)
{
  int l = a[0];
  int n = a.size();
  for (int i = 1; i < n; i++)
    l = lcm(l, a[i]);
  return l;
}

int modular_exponentiation(int a, int b, int n)
{
  int c = 0;
  int d = 1;
  vector<int> B;
  while (b > 0)
  {
    B.push_back(b & 1);
    b >>= 1;
  }
  for (int i = B.size() - 1; i >= 0; i--)
  {
    c = 2 * c;
    d = (d * d) % n;
    if (B[i] == 1)
    {
      c = c + 1;
      d = (d * a) % n;
    }
  }
  return d;
}

int modular_exponentiation_reverse(int a, int b, int n)
{
  int c = 0;
  int d = 1;
  int s = a;
  vector<int> B;
  while (b > 0)
  {
    B.push_back(b & 1);
    b >>= 1;
  }
  for (int i = 0; i < B.size(); i++)
  {
    if (B[i] == 1)
    {
      d = (d * s) % n;
    }
    s = s * s % n;
  }
  return d;
}
int main()
{
  //	cout<<bit_Multiplication(789,43)<<endl;
  //	cout<<bit_Division1(789,43)<<endl;
  //	cout<<"商："<<bit_Division2_quotient(350,43)<<endl;
  //	cout<<"余数："<<bit_Division2_Remainder(789,43)<<endl;
  //EXTENDED_EUCLID(35,50);
  int a = modular_exponentiation_reverse(33, 340, 341);
  cout << a << endl;
  //vector<int> a={8,12,16,24};
  //EXTENDED_EUCLID_MULTIPLE(a);
  //int l=lcm_multiple(a);
  //cout<<l<<endl;
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
