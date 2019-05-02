/*
 * @lc app=leetcode id=414 lang=cpp
 *
 * [414] Third Maximum Number
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int thirdMax(vector<int> &nums)
  {
    int n = nums.size();
    if (n == 1)
      return nums[0];
    if (n == 2)
      return nums[0] > nums[1] ? nums[0] : nums[1];
    long long fir = LLONG_MIN;
    long long sec = LLONG_MIN;
    long long thr = LLONG_MIN;
    for (int i = 0; i < n; i++)
    {
      if (fir < nums[i])
      {
        thr = sec;
        sec = fir;
        fir = nums[i];
      }
      else if (fir != nums[i] && sec < nums[i])
      {
        thr = sec;
        sec = nums[i];
      }
      else if (fir != nums[i] && sec != nums[i] && thr < nums[i])
      {
        thr = nums[i];
      }
    }
    return (thr != LLONG_MIN && thr != sec) ? thr : fir;
  }
};
