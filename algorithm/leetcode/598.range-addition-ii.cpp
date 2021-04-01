/*
 * @lc app=leetcode id=598 lang=cpp
 *
 * [598] Range Addition II
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int maxCount(int m, int n, vector<vector<int>> &ops)
  {
    int mnc = 40001, mnr = 40001;
    for (int i = 0; i < ops.size(); i++)
    {
      mnc = min(mnc, ops[i][0] > 0 ? ops[i][0] : mnc);
      mnr = min(mnr, ops[i][1] > 0 ? ops[i][1] : mnr);
    }
    return min(mnc, m) * min(mnr, n);
  }
};
