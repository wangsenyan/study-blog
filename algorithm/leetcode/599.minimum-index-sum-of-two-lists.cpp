/*
 * @lc app=leetcode id=599 lang=cpp
 *
 * [599] Minimum Index Sum of Two Lists
 */
#include <iostream>
#include <string>
#include <vector>
#include <unordered_map>
using namespace std;
class Solution
{
public:
  vector<string> findRestaurant(vector<string> &l1, vector<string> &l2)
  {
    unordered_map<string, int> map;
    vector<string> res;
    int mn = l1.size() + l2.size();
    for (int i = 0; i < l1.size(); i++)
    {
      map.insert(pair<string, int>{l1[i], i});
    }
    for (int i = 0; i < l2.size(); i++)
    {
      if (map.find(l2[i]) != map.end())
      {
        if (map[l2[i]] + i < mn)
        {
          res.clear();
          mn = map[l2[i]] + i;
          res.push_back(l2[i]);
        }
        else if (map[l2[i]] + i == mn)
          res.push_back(l2[i]);
      }
    }
    return res;
  }
};
