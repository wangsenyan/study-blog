/*
 * @lc app=leetcode id=485 lang=cpp
 *
 * [485] Max Consecutive Ones
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int findMaxConsecutiveOnes(vector<int> &nums)
  {
    int res = 0;
    for (int i = 0, j = 0; i < nums.size(); i++)
    {
      if (nums[i] == 1)
      {
        j++;
        if (res < j)
          res = j;
      }
      else
      {
        j = 0;
      }
    }
    return res;
  }
};
