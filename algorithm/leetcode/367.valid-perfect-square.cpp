/*
 * @lc app=leetcode id=367 lang=cpp
 *
 * [367] Valid Perfect Square
 */
#include <iostream>
using namespace std;
// class Solution
// {
// public:
//   // bool isPerfectSquare(int num)
//   // {
//   //   int i = 0;
//   //   int tmp = num;
//   //   while (tmp > 0)
//   //   {
//   //     i++;
//   //     tmp >>= 1;
//   //   }
//   //   int n = 1 << (i / 2);
//   //   int low, high, mid;
//   //   if (n * n < num)
//   //   {
//   //     low = n;
//   //     high = 2 * n;
//   //   }
//   //   else if (n * n > num)
//   //   {
//   //     low = n / 2;
//   //     high = n;
//   //   }
//   //   else
//   //     return true;
//   //   unsigned long long mu;
//   //   while (low + 1 < high)
//   //   {
//   //     mid = (low + high) / 2;
//   //     mu = mid * mid;
//   //     if (mu > num)
//   //       high = mid;
//   //     else if (mu < num)
//   //       low = mid;
//   //     else
//   //       return true;
//   //   }
//   //   return false;
//   // }

// };
class Solution
{
public:
  bool isPerfectSquare(int num)
  {
    if (num < 1)
      return false;
    long long p = num;
    long long temp;
    long long diff = (p * p - num) / (2 * p); // be careful here;
    while (diff >= 1)
    {
      temp = p;
      p = (p * p + num) / (2 * p);
      diff = temp - p;
    }

    return (p * p == num) ? true : false;
  }
};
