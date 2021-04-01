/*
 * @lc app=leetcode id=520 lang=cpp
 *
 * [520] Detect Capital
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  bool detectCapitalUse(string word)
  {
    for (int i = 1; i < word.size(); i++)
    {
      if (word[0] <= 'Z')
      {
        if (word[1] <= 'Z')
        {
          if (word[i] >= 'a')
            return false;
        }
        else
        {
          if (word[i] <= 'Z')
            return false;
        }
      }
      else
      {
        if (word[i] <= 'Z')
          return false;
      }
    }
    return true;
  }
};
