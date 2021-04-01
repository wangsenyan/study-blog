/*
 * @lc app=leetcode id=17 lang=cpp
 *
 * [17] Letter Combinations of a Phone Number
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
private:
  vector<vector<char>> s = {
      {'a', 'b', 'c'},
      {'d', 'e', 'f'},
      {'g', 'h', 'i'},
      {'j', 'k', 'l'},
      {'m', 'n', 'o'},
      {'p', 'q', 'r', 's'},
      {'t', 'u', 'v'},
      {'w', 'x', 'y', 'z'}};
  void component(string &digits, string str, int n, vector<string> &r) //n第n位
  {
    if (n == digits.size())
      r.push_back(str);
    else
    {
      int k = digits[n] - '0';
      if (k >= 2 && k <= 9)
      {
        for (int i = 0; i < s[k - 2].size(); i++)
        {
          component(digits, str + s[k - 2][i], n + 1, r);
        }
      }
      else
      {
        component(digits, str, n + 1, r);
      }
    }
  }

public:
  vector<string> letterCombinations(string digits)
  {
    vector<string> res;
    string s;
    if (digits.size() == 0)
      return res;
    component(digits, s, 0, res);
    return res;
  }
};
