/*
 * @lc app=leetcode id=169 lang=cpp
 *
 * [169] Majority Element
 *
 * https://leetcode.com/problems/majority-element/description/
 *
 * algorithms
 * Easy (51.87%)
 * Total Accepted:    368.9K
 * Total Submissions: 707.3K
 * Testcase Example:  '[3,2,3]'
 *
 * Given an array of size n, find the majority element. The majority element is
 * the element that appears more than ⌊ n/2 ⌋ times.
 * 
 * You may assume that the array is non-empty and the majority element always
 * exist in the array.
 * 
 * Example 1:
 * 
 * 
 * Input: [3,2,3]
 * Output: 3
 * 
 * Example 2:
 * 
 * 
 * Input: [2,2,1,1,1,2,2]
 * Output: 2
 * 
 * 
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int majorityElement(vector<int> &nums)
  {
    if (nums.size() == 1)
      return nums[0];
    sort(nums.begin(), nums.end());
    return nums[(nums.size()) / 2];
  }
};
