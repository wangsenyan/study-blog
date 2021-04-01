/*
 * @lc app=leetcode id=31 lang=cpp
 *
 * [31] Next Permutation
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  void nextPermutation(vector<int> &nums)
  {
    int n = nums.size();
    if (n < 2)
      return;
    int i = n - 1, mx = INT_MIN;
    for (; i >= 0; i--)
    {
      if (nums[i] >= mx)
      {
        mx = nums[i];
        continue;
      }
      int j = i + 1;
      while (j < n && nums[j] > nums[i])
        j++;
      j--;
      if (j < n)
      {
        int tmp = nums[i];
        nums[i] = nums[j];
        nums[j] = tmp;
        //sort(nums.begin() + i + 1, nums.end());
      }
      break;
    }
    sort(nums.begin() + i + 1, nums.end());
  }
};
