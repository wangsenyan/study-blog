/*
 * @lc app=leetcode id=118 lang=cpp
 *
 * [118] Pascal's Triangle
 *
 * https://leetcode.com/problems/pascals-triangle/description/
 *
 * algorithms
 * Easy (45.02%)
 * Total Accepted:    242.6K
 * Total Submissions: 534.5K
 * Testcase Example:  '5'
 *
 * Given a non-negative integer numRows, generate the first numRows of Pascal's
 * triangle.
 * 
 * 
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 * 
 * Example:
 * 
 * 
 * Input: 5
 * Output:
 * [
 * ⁠    [1],
 * ⁠   [1,1],
 * ⁠  [1,2,1],
 * ⁠ [1,3,3,1],
 * ⁠[1,4,6,4,1]
 * ]
 * 
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<vector<int>> generate(int numRows)
  {
    vector<vector<int>> ans;
    ans.resize(numRows);
    for (int i = 0; i < numRows; i++)
    {
      ans[i].resize(i + 1);
    }
    for (int i = 0; i < numRows; i++)
    {
      ans[i][0] = 1;
      ans[i][i] = 1;
      for (int j = 1; j < i; j++)
      {
        ans[i][j] = ans[i - 1][j - 1] + ans[i - 1][j];
      }
    }
    return ans;
  }
};
