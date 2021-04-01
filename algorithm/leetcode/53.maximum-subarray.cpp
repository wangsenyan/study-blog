/*
 * @lc app=leetcode id=53 lang=cpp
 *
 * [53] Maximum Subarray
 *
 * https://leetcode.com/problems/maximum-subarray/description/
 *
 * algorithms
 * Easy (43.07%)
 * Total Accepted:    503.5K
 * Total Submissions: 1.2M
 * Testcase Example:  '[-2,1,-3,4,-1,2,1,-5,4]'
 *
 * Given an integer array nums, find the contiguous subarray (containing at
 * least one number) which has the largest sum and return its sum.
 * 
 * Example:
 * 
 * 
 * Input: [-2,1,-3,4,-1,2,1,-5,4],
 * Output: 6
 * Explanation: [4,-1,2,1] has the largest sum = 6.
 * 
 * 
 * Follow up:
 * 
 * If you have figured out the O(n) solution, try coding another solution using
 * the divide and conquer approach, which is more subtle.
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int maxSubArray(vector<int> &nums)
  {
    int n = nums.size();
    int tmp = nums[0];
    int maxs = nums[0];
    for (size_t i = 1; i < n; i++)
    {
      if (nums[i] < tmp + nums[i])
        tmp = tmp + nums[i];
      else
        tmp = nums[i];
      if (tmp > maxs)
        maxs = tmp;
    }
    return maxs;
  }
};
