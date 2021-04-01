/*
 * @lc app=leetcode id=500 lang=cpp
 *
 * [500] Keyboard Row
 */
#include <iostream>
#include <vector>
#include <set>
using namespace std;
class Solution
{
public:
  vector<string> findWords(vector<string> &words)
  {
    set<char> r1 = {'Q', 'q', 'W', 'w', 'E', 'e', 'R', 'r', 'T', 't', 'Y', 'y', 'U', 'u', 'I', 'i', 'O', 'o', 'P', 'p'};
    set<char> r2 = {'A', 'a', 'S', 's', 'D', 'd', 'F', 'f', 'G', 'g', 'H', 'h', 'J', 'j', 'K', 'k', 'L', 'l'};
    set<char> r3 = {'Z', 'z', 'X', 'x', 'C', 'c', 'V', 'v', 'B', 'b', 'N', 'n', 'M', 'm'};
    vector<string> res;
    for (int i = 0, j = 0; i < words.size(); i++)
    {
      if (r1.find(words[i][0]) != r1.end())
      {
        for (j = 0; j < words[i].size(); j++)
        {
          if (r1.find(words[i][j]) == r1.end())
            break;
        }
        if (j == words[i].size())
          res.push_back(words[i]);
      }
      if (r2.find(words[i][0]) != r2.end())
      {
        for (j = 0; j < words[i].size(); j++)
        {
          if (r2.find(words[i][j]) == r2.end())
            break;
        }
        if (j == words[i].size())
          res.push_back(words[i]);
      }
      if (r3.find(words[i][0]) != r3.end())
      {
        for (j = 0; j < words[i].size(); j++)
        {
          if (r3.find(words[i][j]) == r3.end())
            break;
        }
        if (j == words[i].size())
          res.push_back(words[i]);
      }
    }
    return res;
  }
};
