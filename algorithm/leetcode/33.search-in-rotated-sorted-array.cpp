/*
 * @lc app=leetcode id=33 lang=cpp
 *
 * [33] Search in Rotated Sorted Array
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int search(vector<int> &nums, int target)
  {
    int n = nums.size();
    int i = 0, j = n - 1, mid;
    while (i <= j)
    {
      mid = (i + j) / 2;
      if (nums[mid] == target)
        return mid;
      else if ((nums[mid] <= nums[i] && target > nums[mid] && nums[j] >= target) || (nums[mid] > nums[j] && (target > nums[mid] || target < nums[i])) || (nums[i] <= nums[mid] && nums[j] > nums[mid] && target > nums[mid]))
      {
        i = mid + 1;
      }
      else
      {
        j = mid - 1;
      }
    }
    return -1;
  }
};
