/*
 * @lc app=leetcode id=217 lang=cpp
 *
 * [217] Contains Duplicate
 *
 * https://leetcode.com/problems/contains-duplicate/description/
 *
 * algorithms
 * Easy (51.18%)
 * Total Accepted:    322.6K
 * Total Submissions: 626.3K
 * Testcase Example:  '[1,2,3,1]'
 *
 * Given an array of integers, find if the array contains any duplicates.
 * 
 * Your function should return true if any value appears at least twice in the
 * array, and it should return false if every element is distinct.
 * 
 * Example 1:
 * 
 * 
 * Input: [1,2,3,1]
 * Output: true
 * 
 * Example 2:
 * 
 * 
 * Input: [1,2,3,4]
 * Output: false
 * 
 * Example 3:
 * 
 * 
 * Input: [1,1,1,3,3,4,3,2,4,2]
 * Output: true
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  bool containsDuplicate(vector<int> &nums)
  {
    if (nums.empty())
      return false;
    if (nums.size() == 1)
      return false;
    sort(nums.begin(), nums.end());
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i] == nums[i - 1])
        return true;
    }
    return false;
  }
};
