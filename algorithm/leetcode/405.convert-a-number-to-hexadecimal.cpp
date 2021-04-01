/*
 * @lc app=leetcode id=405 lang=cpp
 *
 * [405] Convert a Number to Hexadecimal
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  string toHex(int num)
  {
    if (num == 0)
      return "0";
    string str;
    char a;
    unsigned u = num;
    while (u)
    {
      str = ((u & 0xf) > 9 ? char((u & 0xf) - 10 + 'a') : char((u & 0xf) + '0')) + str;
      u >>= 4;
    }
    return str;
  }
};
