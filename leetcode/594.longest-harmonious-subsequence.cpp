/*
 * @lc app=leetcode id=594 lang=cpp
 *
 * [594] Longest Harmonious Subsequence
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int findLHS(vector<int> &nums)
  {
    if (nums.size() == 0)
      return 0;
    sort(nums.begin(), nums.end());
    //记录前面最小j个，最大k个
    int mn = nums[0], res = 0, j = 1, k = 0;
    for (int i = 1; i < nums.size(); i++)
    {
      if (nums[i] - mn == 0)
      {
        j++;
      }
      else if (nums[i] - mn == 1)
      {
        k++;
      }
      else if (nums[i] - mn == 2)
      {
        j = k;
        k = 1;
        mn = mn + 1;
      }
      else
      {
        j = 1;
        k = 0;
        mn = nums[i];
      }
      res = res > (k == 0 || j == 0 ? 0 : k + j) ? res : (k == 0 || j == 0 ? 0 : k + j);
    }
    return res;
  }
};
