/*
 * @lc app=leetcode id=15 lang=cpp
 *
 * [15] 3Sum
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<vector<int>> threeSum(vector<int> &nums)
  {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    for (int i = 0; i < nums.size(); i++)
    {
      if (i > 0 && nums[i] == nums[i - 1])
        continue; //avoid repeat
      if (nums[i] > 0)
        break;
      int j = i + 1, k = nums.size() - 1;
      while (j < k)
      {
        int tmp = nums[i] + nums[j] + nums[k];
        if (tmp > 0)
          k--;
        else if (tmp < 0)
          j++;
        else
        {
          if (k == nums.size() - 1 || (nums[j] != nums[j - 1] || nums[k] != nums[k + 1]))
          {
            res.push_back(vector<int>{nums[i], nums[j], nums[k]});
          }
          j++;
          k--;
        }
      }
    }
    return res;
  }
};
