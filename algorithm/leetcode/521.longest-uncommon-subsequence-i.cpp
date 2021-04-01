/*
 * @lc app=leetcode id=521 lang=cpp
 *
 * [521] Longest Uncommon Subsequence I 
 */
class Solution
{
public:
  int findLUSlength(string a, string b)
  {
    return a == b ? -1 : max(a.size(), b.size());
  }
};
