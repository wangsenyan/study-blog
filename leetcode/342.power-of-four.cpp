/*
 * @lc app=leetcode id=342 lang=cpp
 *
 * [342] Power of Four
 */
#include <iostream>
using namespace std;
class Solution
{
public:
  bool isPowerOfFour(int num)
  {
    int i = 0;
    while (num > 0)
    {
      i += num & 3;
      num >>= 2;
    }
    return i == 1;
  }
};
