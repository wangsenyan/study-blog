/*
 * @lc app=leetcode id=75 lang=cpp
 *
 * [75] Sort Colors
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  //类似快排
  void sortColors(vector<int> &nums)
  {
    int n = nums.size();
    vector<int> eh(3, 0);
    for (int i = 0; i < n; i++)
      eh[nums[i]]++;
    for (int i = 0; i < n; i++)
      nums[i] = eh[0]-- > 0 ? 0 : eh[1]-- > 0 ? 1 : 2;
  }
};
