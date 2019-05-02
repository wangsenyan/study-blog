/*
 * @lc app=leetcode id=205 lang=cpp
 *
 * [205] Isomorphic Strings
 *
 * https://leetcode.com/problems/isomorphic-strings/description/
 *
 * algorithms
 * Easy (36.91%)
 * Total Accepted:    196.6K
 * Total Submissions: 530.4K
 * Testcase Example:  '"egg"\n"add"'
 *
 * Given two strings s and t, determine if they are isomorphic.
 * 
 * Two strings are isomorphic if the characters in s can be replaced to get t.
 * 
 * All occurrences of a character must be replaced with another character while
 * preserving the order of characters. No two characters may map to the same
 * character but a character may map to itself.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "egg", t = "add"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "foo", t = "bar"
 * Output: false
 * 
 * Example 3:
 * 
 * 
 * Input: s = "paper", t = "title"
 * Output: true
 * 
 * Note:
 * You may assume both s and t have the same length.
 * 
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
  bool isIsomorphic(string s, string t)
  {
    vector<int> match(255, 0);
    vector<int> match1(255, 0);
    for (int i = 0; i < s.size(); i++)
    {
      if (!match[s[i]] && !match1[t[i]])
      {
        match[s[i]] = t[i];
        match1[t[i]] = s[i];
      }
      else if (match[s[i]] != t[i] || match1[t[i]] != s[i])
        return false;
    }
    return true;
  }
};
