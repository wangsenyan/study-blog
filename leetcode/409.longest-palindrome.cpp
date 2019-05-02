/*
 * @lc app=leetcode id=409 lang=cpp
 *
 * [409] Longest Palindrome
 */
#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int longestPalindrome(string s)
  {
    sort(s.begin(), s.end());
    int k = 0;
    for (int i = 0; i < s.size() - 1; i++)
    {
      if (s[i] == s[i + 1])
      {
        k++;
        i++;
      }
    }
    if (2 * k < s.size())
      return 2 * k + 1;
    else
      return 2 * k;
  }
};
