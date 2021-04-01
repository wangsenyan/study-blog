/*
 * @lc app=leetcode id=290 lang=cpp
 *
 * [290] Word Pattern
 *
 * https://leetcode.com/problems/word-pattern/description/
 *
 * algorithms
 * Easy (34.64%)
 * Total Accepted:    136.8K
 * Total Submissions: 393.1K
 * Testcase Example:  '"abba"\n"dog cat cat dog"'
 *
 * Given a pattern and a string str, find if str follows the same pattern.
 * 
 * Here follow means a full match, such that there is a bijection between a
 * letter in pattern and a non-empty word in str.
 * 
 * Example 1:
 * 
 * 
 * Input: pattern = "abba", str = "dog cat cat dog"
 * Output: true
 * 
 * Example 2:
 * 
 * 
 * Input:pattern = "abba", str = "dog cat cat fish"
 * Output: false
 * 
 * Example 3:
 * 
 * 
 * Input: pattern = "aaaa", str = "dog cat cat dog"
 * Output: false
 * 
 * Example 4:
 * 
 * 
 * Input: pattern = "abba", str = "dog dog dog dog"
 * Output: false
 * 
 * Notes:
 * You may assume pattern contains only lowercase letters, and str contains
 * lowercase letters that may be separated by a single space.
 * 
 */
#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  bool wordPattern(string pattern, string str)
  {
    unordered_map<string, string> m1, m2;
    int i = 0, j = 0;
    for (int k = 0; i < pattern.size() && j < str.size(); i++)
    {
      string tmp;
      while (j < str.size() && str[j] != ' ')
        j++;
      tmp = str.substr(k, j - k);
      //cout << k << " " << j - k << " " << tmp << endl;
      j++;
      k = j;
      string b = to_string(pattern[i]);
      if (m1.find(b) == m1.end() && m2.find(tmp) == m2.end())
      {
        m1.insert(pair<string, string>{b, tmp});
        m2.insert(pair<string, string>{tmp, b});
      }
      else if (m1[b] != tmp || m2[tmp] != b)
        return false;
    }
    return i == pattern.size() && (j - 1) == str.size();
  }
};
