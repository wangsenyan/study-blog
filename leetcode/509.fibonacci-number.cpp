/*
 * @lc app=leetcode id=509 lang=cpp
 *
 * [509] Fibonacci Number
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{

public:
  int fib(int N)
  {
    if (N < 0)
      return 0;
    if (N < 2)
      return N;
    else
    {
      int f = 0, s = 1, r = 0;
      for (int i = 2; i <= N; i++)
      {
        r = f + s;
        f = s;
        s = r;
      }
      return r;
    }
  }
};
