/*
 * @lc app=leetcode id=242 lang=cpp
 *
 * [242] Valid Anagram
 *
 * https://leetcode.com/problems/valid-anagram/description/
 *
 * algorithms
 * Easy (51.34%)
 * Total Accepted:    325.5K
 * Total Submissions: 629.4K
 * Testcase Example:  '"anagram"\n"nagaram"'
 *
 * Given two strings s and t , write a function to determine if t is an anagram
 * of s.
 * 
 * Example 1:
 * 
 * 
 * Input: s = "anagram", t = "nagaram"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: s = "rat", t = "car"
 * Output: false
 * 
 * 
 * Note:
 * You may assume the string contains only lowercase alphabets.
 * 
 * Follow up:
 * What if the inputs contain unicode characters? How would you adapt your
 * solution to such case?
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  bool isAnagram(string s, string t)
  {
    int n = s.size();
    if (n != t.size())
      return false;
    vector<int> ss('z' - 'a' + 1, 0);
    vector<int> tt('z' - 'a' + 1, 0);
    for (int i = 0; i < n; i++)
    {
      ss[s[i] - 'a'] += 1;
      tt[t[i] - 'a'] += 1;
    }
    for (int i = 0; i < ss.size(); i++)
    {
      if (ss[i] != tt[i])
        return false;
    }
    return true;
  }
};
