/*
 * @lc app=leetcode id=47 lang=cpp
 *
 * [47] Permutations II
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
private:
  bool nextMax(vector<int> &nums)
  {
    int n = nums.size();
    int j = n - 2;
    while (j >= 0 && nums[j] >= nums[j + 1])
      j--;
    if (j < 0)
      return false;
    int k = n - 1;
    while (k > j && nums[j] >= nums[k])
      k--;
    swap(nums[j], nums[k]);
    int r = n - 1, s = j + 1;
    while (r > s)
    {
      swap(nums[r], nums[s]);
      r--;
      s++;
    }
    return true;
  }

public:
  vector<vector<int>> permuteUnique(vector<int> &nums)
  {
    sort(nums.begin(), nums.end());
    vector<vector<int>> res;
    res.push_back(nums);
    while (nextMax(nums))
      res.push_back(nums);
    return res;
  }
};
