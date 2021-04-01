/*
 * @lc app=leetcode id=350 lang=cpp
 *
 * [350] Intersection of Two Arrays II
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<int> intersect(vector<int> &nums1, vector<int> &nums2)
  {
    vector<int> result(nums1.size() + nums2.size());
    vector<int>::iterator it;
    sort(nums1.begin(), nums1.end());
    sort(nums2.begin(), nums2.end());
    it = set_intersection(nums1.begin(), nums1.end(), nums2.begin(), nums2.end(), result.begin());
    result.resize(it - result.begin());
    return result;
  }
};
