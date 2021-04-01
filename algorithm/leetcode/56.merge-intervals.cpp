/*
 * @lc app=leetcode id=56 lang=cpp
 *
 * [56] Merge Intervals
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<vector<int>> merge(vector<vector<int>> &intervals)
  {
    int n = intervals.size();
    vector<vector<int>> res;
    sort(intervals.begin(), intervals.end());
    for (int i = 0, k = 0; i < n; i++)
    {
      if (i == 0 || res[k - 1][1] < intervals[i][0])
      {
        res.push_back(intervals[i]);
        k++;
      }
      else
        res[k - 1][1] = max(intervals[i][1], res[k - 1][1]);
    }
    return res;
  }
};
