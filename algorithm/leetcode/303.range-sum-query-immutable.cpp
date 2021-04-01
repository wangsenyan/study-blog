/*
 * @lc app=leetcode id=303 lang=cpp
 *
 * [303] Range Sum Query - Immutable
 *
 * https://leetcode.com/problems/range-sum-query-immutable/description/
 *
 * algorithms
 * Easy (37.05%)
 * Total Accepted:    134.3K
 * Total Submissions: 358.5K
 * Testcase Example:  '["NumArray","sumRange","sumRange","sumRange"]\n[[[-2,0,3,-5,2,-1]],[0,2],[2,5],[0,5]]'
 *
 * Given an integer array nums, find the sum of the elements between indices i
 * and j (i ≤ j), inclusive.
 * 
 * Example:
 * 
 * Given nums = [-2, 0, 3, -5, 2, -1]
 * 
 * sumRange(0, 2) -> 1
 * sumRange(2, 5) -> -1
 * sumRange(0, 5) -> -3
 * 
 * 
 * 
 * Note:
 * 
 * You may assume that the array does not change.
 * There are many calls to sumRange function.
 * 
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class NumArray
{
public:
  vector<int> fDist;
  NumArray(vector<int> nums)
  {

    for (int i = 0; i < nums.size(); i++)
    {
      if (i == 0)
      {
        fDist.push_back(nums[i]);
      }
      else
      {
        fDist.push_back(nums[i] + fDist[i - 1]);
      }
    }
  }

  int sumRange(int i, int j)
  {

    int prev = i - 1;
    if (prev >= 0)
    {
      return fDist[j] - fDist[prev];
    }
    return fDist[j];
  }
};

/**
 * Your NumArray object will be instantiated and called as such:
 * NumArray* obj = new NumArray(nums);
 * int param_1 = obj->sumRange(i,j);
 */
