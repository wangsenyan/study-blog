/*
 * @lc app=leetcode id=566 lang=cpp
 *
 * [566] Reshape the Matrix
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<vector<int>> matrixReshape(vector<vector<int>> &nums, int r, int c)
  {
    int m = nums.size(), n = nums[0].size();
    vector<vector<int>> res(r, vector<int>(c, 0));
    if (n * m != r * c)
      return nums;
    for (int i = 0; i < r; i++)
    {
      for (int j = 0; j < c; j++)
      {
        res[i][j] = nums[(i * c + j) / n][(i * c + j) % n];
      }
    }
    return res;
  }
};
