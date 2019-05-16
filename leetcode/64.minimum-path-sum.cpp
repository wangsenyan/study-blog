/*
 * @lc app=leetcode id=64 lang=cpp
 *
 * [64] Minimum Path Sum
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int minPathSum(vector<vector<int>> &grid)
  {
    int m = grid.size(), n = m ? grid[0].size() : 0;
    if (m == 0)
      return 0;
    vector<int> dp(n, 0);
    for (int i = 0; i < m; i++)
    {
      for (int j = 0; j < n; j++)
      {
        if (i == 0 && j == 0)
          dp[j] = grid[i][j];
        else if (i == 0)
          dp[j] = dp[j - 1] + grid[i][j];
        else if (j == 0)
          dp[j] = dp[j] + grid[i][j];
        else
          dp[j] = min(dp[j - 1] + grid[i][j], dp[j] + grid[i][j]);
      }
    }
    return dp[n - 1];
  }
};
