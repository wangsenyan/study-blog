/*
 * @lc app=leetcode id=344 lang=cpp
 *
 * [344] Reverse String
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  void reverseString(vector<char> &s)
  {
    for (int i = 0; i < s.size() / 2; i++)
    {
      char tmp = s[i];
      s[i] = s[s.size() - i - 1];
      s[s.size() - i - 1] = tmp;
    }
  }
};
