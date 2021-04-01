/*
 * @lc app=leetcode id=541 lang=cpp
 *
 * [541] Reverse String II
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
private:
  void rev(string &s, int p, int q) //反转p到q-1
  {
    for (int i = p, j = q - 1; i < j; i++, j--)
    {
      char t = s[i];
      s[i] = s[j];
      s[j] = t;
    }
  }

public:
  string reverseStr(string s, int k)
  {
    for (int i = 0; i < s.size(); i += 2 * k)
    {
      if (s.size() < i + k)
        rev(s, i, s.size());
      else
        rev(s, i, i + k);
    }
    return s;
  }
};
