/*
 * @lc app=leetcode id=88 lang=cpp
 *
 * [88] Merge Sorted Array
 *
 * https://leetcode.com/problems/merge-sorted-array/description/
 *
 * algorithms
 * Easy (35.15%)
 * Total Accepted:    350.5K
 * Total Submissions: 990.9K
 * Testcase Example:  '[1,2,3,0,0,0]\n3\n[2,5,6]\n3'
 *
 * Given two sorted integer arrays nums1 and nums2, merge nums2 into nums1 as
 * one sorted array.
 * 
 * Note:
 * 
 * 
 * The number of elements initialized in nums1 and nums2 are m and n
 * respectively.
 * You may assume that nums1 has enough space (size that is greater or equal to
 * m + n) to hold additional elements from nums2.
 * 
 * 
 * Example:
 * 
 * 
 * Input:
 * nums1 = [1,2,3,0,0,0], m = 3
 * nums2 = [2,5,6],       n = 3
 * 
 * Output: [1,2,2,3,5,6]
 * 
 * 
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  void merge(vector<int> &nums1, int m, vector<int> &nums2, int n)
  {
    int t = nums1.size(), i, j, k;
    for (i = m - 1, j = n - 1, k = t - 1; i >= 0 && j >= 0; k--)
    {
      if (nums1[i] >= nums2[j])
      {
        nums1[k] = nums1[i];
        i--;
      }
      else
      {
        nums1[k] = nums2[j];
        j--;
      }
    }
    for (; j >= 0; j--, k--)
    {
      nums1[k] = nums2[j];
    }
  }
};
