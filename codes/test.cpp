#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
  int gcd(int a, int b)
  {
    return b == 0 ? a : gcd(b, a % b);
  }

public:
  int div(int a, int b, int c)
  {
    a /= gcd(b, c);
    if (a & 1)
      return -1;
    else
      return a - 1;
  }
};
int main()
{
  Solution s;
  cout << s.div(7, 4, 3);
  return 0;
}
Int (*f(int, void (*)()))(int, int);