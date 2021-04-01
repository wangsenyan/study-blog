/*
 * @lc app=leetcode id=476 lang=cpp
 *
 * [476] Number Complement
 */
#include <iostream>
using namespace std;
class Solution
{
public:
  int findComplement(int num)
  {
    int i = 0;
    int r = 0;
    while (num)
    {

      r += ((~(num & 0x1)) & 0x1) << i;
      i++;
      num >>= 1;
    }
    return r;
  }
};
