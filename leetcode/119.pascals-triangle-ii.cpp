/*
 * @lc app=leetcode id=119 lang=cpp
 *
 * [119] Pascal's Triangle II
 *
 * https://leetcode.com/problems/pascals-triangle-ii/description/
 *
 * algorithms
 * Easy (42.54%)
 * Total Accepted:    195.8K
 * Total Submissions: 456.1K
 * Testcase Example:  '3'
 *
 * Given a non-negative index k where k ≤ 33, return the k^th index row of the
 * Pascal's triangle.
 * 
 * Note that the row index starts from 0.
 * 
 * 
 * In Pascal's triangle, each number is the sum of the two numbers directly
 * above it.
 * 
 * Example:
 * 
 * 
 * Input: 3
 * Output: [1,3,3,1]
 * 
 * 
 * Follow up:
 * 
 * Could you optimize your algorithm to use only O(k) extra space?
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<int> getRow(int rowIndex)
  {
    vector<int> ans(rowIndex + 1, 0);
    long long tmp = 1;
    for (int i = 0; i <= rowIndex; i++)
    {
      ans[i] = (int)tmp;

      tmp = tmp * (rowIndex - i) / (i + 1);
    }
    return ans;
  }
};
