/*
 * @lc app=leetcode id=415 lang=cpp
 *
 * [415] Add Strings
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  string addStrings(string num1, string num2)
  {
    string str;
    int i = num1.size() - 1, j = num2.size() - 1, tmp = 0;
    while (i >= 0 || j >= 0 || tmp)
    {
      tmp += (i >= 0 ? num1[i] - '0' : 0);
      i--;
      tmp += (j >= 0 ? num2[j] - '0' : 0);
      j--;
      str = char(tmp % 10 + '0') + str;
      tmp /= 10;
    }
    return str;
  }
};
