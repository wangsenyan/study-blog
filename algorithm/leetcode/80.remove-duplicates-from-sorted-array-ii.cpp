/*
 * @lc app=leetcode id=80 lang=cpp
 *
 * [80] Remove Duplicates from Sorted Array II
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int removeDuplicates(vector<int> &nums)
  {
    int n = nums.size(), count = 0;
    for (int i = 2; i < n; i++)
      if (nums[i] == nums[i - 2 - count])
        count++;
      else
        nums[i - count] = nums[i];
    return n - count;
  }
};
