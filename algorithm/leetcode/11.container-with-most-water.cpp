/*
 * @lc app=leetcode id=11 lang=cpp
 *
 * [11] Container With Most Water
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int maxArea(vector<int> &height)
  {
    int i = 0, j = height.size() - 1;
    int mx = 0;
    int tmp = 0;
    while (i < j)
    {
      tmp = height[i] < height[j] ? (j - i) * height[i++] : (j - i) * height[j--];
      mx = tmp > mx ? tmp : mx;
    }
    return mx;
  }
};
