/*
 * @lc app=leetcode id=283 lang=cpp
 *
 * [283] Move Zeroes
 *
 * https://leetcode.com/problems/move-zeroes/description/
 *
 * algorithms
 * Easy (53.86%)
 * Total Accepted:    449.5K
 * Total Submissions: 831.4K
 * Testcase Example:  '[0,1,0,3,12]'
 *
 * Given an array nums, write a function to move all 0's to the end of it while
 * maintaining the relative order of the non-zero elements.
 * 
 * Example:
 * 
 * 
 * Input: [0,1,0,3,12]
 * Output: [1,3,12,0,0]
 * 
 * Note:
 * 
 * 
 * You must do this in-place without making a copy of the array.
 * Minimize the total number of operations.
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  void moveZeroes(vector<int> &nums)
  {
    int k = 0, n = nums.size();
    int i = 0, j;
    while (i < n && nums[i] != 0)
      i++;
    j = i + 1;
    if (i < n - 1)
      k++;
    for (j = i + 1; j < n; j++)
    {
      if (nums[j] != 0)
      {
        nums[i++] = nums[j];
      }
      else
      {
        k++;
      }
    }
    for (i = n - 1; i >= n - k; i--)
      nums[i] = 0;
  }
};
