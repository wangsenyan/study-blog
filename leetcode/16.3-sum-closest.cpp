/*
 * @lc app=leetcode id=16 lang=cpp
 *
 * [16] 3Sum Closest
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int threeSumClosest(vector<int> &nums, int target)
  {
    sort(nums.begin(), nums.end());
    long long tar = INT_MAX;
    for (int i = 0; i < nums.size(); i++)
    {
      int j = i + 1, k = nums.size() - 1;
      while (j < k)
      {
        long long tmp = nums[i] + nums[j] + nums[k];
        if (abs(target - tmp) < abs(target - tar))
        {
          tar = tmp;
        }
        if (tmp > target)
          k--;
        else if (tmp < target)
          j++;
        else
        {
          return target;
        }
      }
    }
    return tar;
  }
};
