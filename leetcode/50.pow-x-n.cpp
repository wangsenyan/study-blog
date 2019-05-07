/*
 * @lc app=leetcode id=50 lang=cpp
 *
 * [50] Pow(x, n)
 */
#include <iostream>
#include <bitset>
using namespace std;
/*
let n=a0+a1*2^1+a2*2^2+...+an*2^n(n<=32),
    x^n=x^a0*x^(a1*2^1)*...*x^(an*2^n)
    x^2^i=(x^2^(i-1))^2
*/
class Solution
{
public:
  double myPow(double x, int n)
  {
    bitset<32> bit(abs((long long)n));
    double result = 1;
    for (int i = bit.size() - 1; i >= 0; i--)
    {
      result *= result;
      if (bit[i] == 1)
        result *= x;
    }
    return (n >= 0) ? result : 1 / result;
  }
};
