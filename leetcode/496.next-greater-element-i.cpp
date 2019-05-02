/*
 * @lc app=leetcode id=496 lang=cpp
 *
 * [496] Next Greater Element I
 */
#include <iostream>
#include <vector>
#include <map>
using namespace std;
class Solution
{
public:
  vector<int> nextGreaterElement(vector<int> &nums1, vector<int> &nums2)
  {
    map<int, int> idex;
    int max = 0;
    for (int i = 0; i < nums2.size(); i++)
    {
      idex[nums2[i]] = i; //位置匹配
      max = max > nums2[i] ? max : nums2[i];
    }
    for (int i = 0; i < nums1.size(); i++)
    {
      int j = idex[nums1[i]] + 1;
      for (; j < nums2.size(); j++)
      {
        if (nums2[j] > nums1[i])
        {
          nums1[i] = nums2[j];
          break;
        }
      }
      if (j == nums2.size())
        nums1[i] = -1;
    }
    return nums1;
  }
};
