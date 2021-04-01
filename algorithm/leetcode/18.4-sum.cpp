/*
 * @lc app=leetcode id=18 lang=cpp
 *
 * [18] 4Sum
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<vector<int>> fourSum(vector<int> &nums, int target)
  {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++)
    {
      if (i > 0 && nums[i] == nums[i - 1])
        continue;
      for (int j = i + 1; j < nums.size(); j++)
      {
        if (j > i + 1 && nums[i] + nums[j] == nums[i] + nums[j - 1])
          continue;
        int k = j + 1, l = nums.size() - 1;
        while (k < l)
        {
          int tmp = nums[i] + nums[j] + nums[k] + nums[l];
          if (tmp < target)
            k++;
          else if (tmp > target)
            l--;
          else
          {
            if (l == nums.size() - 1 || (nums[k] != nums[k - 1] || nums[l] != nums[l + 1]))
              res.push_back(vector<int>{nums[i], nums[j], nums[k], nums[l]});
            k++;
            l--;
          }
        }
      }
    }
    return res;
  }
};
