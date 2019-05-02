/*
 * @lc app=leetcode id=136 lang=cpp
 *
 * [136] Single Number
 *
 * https://leetcode.com/problems/single-number/description/
 *
 * algorithms
 * Easy (59.37%)
 * Total Accepted:    444.6K
 * Total Submissions: 745K
 * Testcase Example:  '[2,2,1]'
 *
 * Given a non-empty array of integers, every element appears twice except for
 * one. Find that single one.
 * 
 * Note:
 * 
 * Your algorithm should have a linear runtime complexity. Could you implement
 * it without using extra memory?
 * 
 * Example 1:
 * 
 * 
 * Input: [2,2,1]
 * Output: 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: [4,1,2,1,2]
 * Output: 4
 * 
 * 
 */
#include <iostream>
#include <vector>
#include <set>
using namespace std;
class Solution
{
public:
  int singleNumber(vector<int> &nums)
  {
    int res = 0;
    for (int i : nums)
    {
      res = res ^ i;
    }
    return res;
  }
};
