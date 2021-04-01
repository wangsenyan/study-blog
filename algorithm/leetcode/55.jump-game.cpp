/*
 * @lc app=leetcode id=55 lang=cpp
 *
 * [55] Jump Game
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  bool canJump(vector<int> &nums)
  {
    int n = nums.size();
    if (n <= 1)
      return true;
    int pre = 0;
    for (int i = 0; i < n - 1; i++)
    {
      if (nums[i] == 0 && pre <= i)
        return false;
      pre = max(pre, i + nums[i]);
      if (pre >= n - 1)
        return true;
    }
    return false;
  }
};
