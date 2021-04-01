/*
 * @lc app=leetcode id=504 lang=cpp
 *
 * [504] Base 7
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Solution
{
public:
  string convertToBase7(int num)
  {
    string str;
    int tmp = abs(num);
    while (tmp)
    {
      str += char(tmp % 7 + '0');
      tmp /= 7;
    }
    reverse(str.begin(), str.end());
    return num == 0 ? "0" : num > 0 ? str : "-" + str;
  }
};
