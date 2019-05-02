/*
 * @lc app=leetcode id=453 lang=cpp
 *
 * [453] Minimum Moves to Equal Array Elements
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int minMoves(vector<int> &nums)
  {
    int minimum = INT_MAX, sum = 0;
    for (auto i : nums)
      minimum = min(minimum, i);
    for (int i = 0; i < nums.size(); i++)
      sum += nums[i] - minimum;
    return sum;
  }
};
