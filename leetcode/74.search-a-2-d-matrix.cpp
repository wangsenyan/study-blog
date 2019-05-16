/*
 * @lc app=leetcode id=74 lang=cpp
 *
 * [74] Search a 2D Matrix
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  bool searchMatrix(vector<vector<int>> &matrix, int target)
  {
    int m = matrix.size(), n = m == 0 ? 0 : matrix[0].size();
    if (m == 0 || n == 0)
      return false;
    int i = 0, j = 0;
    while (i < m && matrix[i][j] <= target)
      i++;
    i--;
    if (i < 0)
      return false;
    while (j < n && matrix[i][j] < target)
      j++;
    if (j == n || matrix[i][j] != target)
      return false;
    return true;
  }
};
