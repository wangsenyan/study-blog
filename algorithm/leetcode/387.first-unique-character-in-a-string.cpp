/*
 * @lc app=leetcode id=387 lang=cpp
 *
 * [387] First Unique Character in a String
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
  int firstUniqChar(string s)
  {
    vector<int> str(26, 0);
    for (auto c : s)
      str[c - 'a']++;
    for (int i = 0; i < s.size(); i++)
      if (str[s[i] - 'a'] == 1)
        return i;
    return -1;
  }
};
