/*
 * @lc app=leetcode id=443 lang=cpp
 *
 * [443] String Compression
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
  int compress(vector<char> &chars)
  {
    int k = 0;
    for (int i = 0, j = 0, l = 0; i < chars.size(); i++)
    {
      if (i + 1 < chars.size() && chars[i] == chars[i + 1])
        l++;
      else if (l > 0)
      {
        string s = to_string(l + 1);
        chars[k++] = chars[i];
        for (j = 0; j < s.size(); j++)
        {
          chars[k++] = s[j];
        }
        l = 0;
      }
      else
        chars[k++] = chars[i];
    }
    return k;
  }
};
