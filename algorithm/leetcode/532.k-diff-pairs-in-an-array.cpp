/*
 * @lc app=leetcode id=532 lang=cpp
 *
 * [532] K-diff Pairs in an Array
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int findPairs(vector<int> &nums, int k)
  {
    sort(nums.begin(), nums.end());
    int sum = 0;
    for (int i = 0, j = 1; i < nums.size() && j < nums.size() && i < j;)
    {
      if (nums[j] - nums[i] == k && (i == 0 || nums[i] != nums[i - 1]))
      {
        sum++;
        i++;
        j++;
      }
      else if (nums[j] - nums[i] > k)
      {
        i++;
        if (i == j)
          j++;
      }
      else
        j++;
    }
    return sum;
  }
};
