/*
 * @lc app=leetcode id=581 lang=cpp
 *
 * [581] Shortest Unsorted Continuous Subarray
 */
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int findUnsortedSubarray(vector<int> &nums)
  {
    int n = nums.size(), start = -1, end = -2;
    int mn = nums[n - 1], mx = nums[0];
    for (int i = 1; i < n; ++i)
    {
      if (mx <= nums[i])
      {
        mx = nums[i];
      }
      else
      {
        end = i;
      }
      if (mn >= nums[n - 1 - i])
      {
        mn = nums[n - 1 - i];
      }
      else
      {
        start = n - 1 - i;
      }
    }
    return end - start + 1;
  }
};
