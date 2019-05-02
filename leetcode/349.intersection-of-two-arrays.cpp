/*
 * @lc app=leetcode id=349 lang=cpp
 *
 * [349] Intersection of Two Arrays
 */
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<int> intersection(vector<int> &nums1, vector<int> &nums2)
  {
    vector<int> ret;
    sort(nums2.begin(), nums2.end());
    sort(nums1.begin(), nums1.end());
    for (int i = 0, j = 0; i < nums1.size() && j < nums2.size();)
    {
      if (nums1[i] == nums2[j])
      {
        if (i == 0 || nums1[i] != nums1[i - 1])
        {
          ret.push_back(nums1[i]);
        }
        ++i;
        ++j;
      }
      else if (nums1[i] < nums2[j])
      {
        ++i;
      }
      else
      {
        ++j;
      }
    }

    return ret;
  }
};
