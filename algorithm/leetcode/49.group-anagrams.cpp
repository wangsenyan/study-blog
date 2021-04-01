/*
 * @lc app=leetcode id=49 lang=cpp
 *
 * [49] Group Anagrams
 */
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<vector<string>> groupAnagrams(vector<string> &strs)
  {
    unordered_map<string, int> map;
    vector<vector<string>> res;
    string tmp;
    for (int i = 0, k = 0; i < strs.size(); i++)
    {
      tmp = strs[i];
      sort(tmp.begin(), tmp.end());
      if (map.size() == 0 || map.find(tmp) == map.end())
      {
        map[tmp] = k++;
        res.push_back(vector<string>{strs[i]});
      }
      else
      {
        res[map[tmp]].push_back(strs[i]);
      }
    }
    return res;
  }
};
