/*
 * @lc app=leetcode id=29 lang=cpp
 *
 * [29] Divide Two Integers
 */
#include <iostream>
class Solution
{
public:
  int divide(int dividend, int divisor)
  {
    long long m = abs((long long)dividend), n = abs((long long)divisor), res = 0;
    if (m < n)
      return 0;
    while (m >= n)
    {
      long long l = n, p = 1;
      while (m > (l << 1))
      {
        l <<= 1;
        p <<= 1;
      }
      res += p;
      m -= l;
    }
    res = (dividend < 0) ^ (divisor < 0) ? -res : res;
    return res > INT_MAX ? INT_MAX : res;
  }
};
