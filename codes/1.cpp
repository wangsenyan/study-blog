//求n个不同的数可重复选m个数
#include <iostream>
#include <cmath>
unsigned int cr(int n);
int main(void)
{
  cr(10);
  return 0;
}
unsigned int cr(n)
{
  unsigned long int k = 0;
  for (int m1 = 0; m1 < n; m1++)
    for (int m2 = 0; m2 < m1; m2++)
      for (int m3 = 0; m3 < m2; m3++)
        for (int m4 = 0; m4 < m3; m4++)
          for (int m5 = 0; m5 < m4; m5++)
            for (int m6 = 0; m6 < m5; m6++)
              for (int m7 = 0; m7 < m6; m7++)
                k = k + 1;
  std::cout << "there id: " << k << std::end;
  return 0;
}

//计算整数n的b进制展开
int f(int b, int m)
{
  int q = n;
  int a;
  while (q != 0)
  {
    a = q % m;
    q = q / m;
    std::cout << a << std::end;
  }
  return 0;
}

//整数相加 a=(an-1an-2...a0) b=(bn-1bn-2...b1)
long f(int a[], int b[], n)
{
  int c = 0;
  int d = 0;
  int s[n];
  for (int j = 0; j < n; j++)
  {
    d = (a[j] + b[j] + c) / 2;
    s[j] = a[j] + b[j] + c - 2d;
    c = d;
  }
  s[n] = c;
}

//整合相乘O(n2)
long f(int a[], int b[], int n)
{
  int c[n] = {0};
  long p = 0;
  for (int i = 0; i < n; i++)
  {
    if (b[i] == 1)
      c[i] = a[i] << i;
    else
      c[i] = 0;
  }
  for (i = 0; i < n; i++)
  {
    p = p + c[i]
  }
  return p;
}

//计算div和mod
int f(int a, int b)
{
  int q = 0;
  int r = abs(a);
  while (r >= d)
  {
    r = r - d;
    q++;
  }
  if (a < 0 && r > 0)
  {
    r = d - r;
    q = -(q + 1);
  }
  std::cout << q << "=a div d"
            << "\n"
            << r << "=a mod d" << std::end;
  return 0;
}

//同余幂 b^n mod m,n=(ak-1ak-2..a2a1)2
long long int f(long b, long n, long m)
{
  int x = 1;
  long power = b % m;
  for (i = 0; i < k; i++)
  {
    if (a[i] == 1)
    {
      x = (x * power) mod m;
    }
    power = (power * power) mod m;
  }
  return x;
}
//欧几里得算法，辗转相除法
int f(long a, long b)
{
  long temp = b;
  while (b != 0)
  {
    b = a % b;
    a = temp;
    temp = b;
  }
  return a;
}

//调度讲座动态规划算法,讲座
//s[]讲座开始时间，e[]讲座结束时间，w[]参与人数，p[]兼容
(int *)f(int s *, int e *, int w *, int n)
{
  int T[n] = {0};
  int p[n] = {0};
  int i;
  for (i = 0; i < n; i++)
  {
    for (int j = 0; j < i; j++)
    {
      if (e[j] <= s[i])
        p[i] = j;
    }
  }
  for (i = 1; i <= n; i++)
  {
    T[i] = max(w[i] + T[p[i]], T[j - 1]);
  }
  return T;
}
