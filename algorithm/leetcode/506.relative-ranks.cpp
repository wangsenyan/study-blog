/*
 * @lc app=leetcode id=506 lang=cpp
 *
 * [506] Relative Ranks
 */
#include <iostream>
#include <vector>
#include <string>
#include <map>
using namespace std;
class Solution
{
public:
  vector<string> findRelativeRanks(vector<int> &nums)
  {
    int n = nums.size();
    vector<string> res(n, "0");
    map<int, int> seq;
    int max = 0;
    for (int i = 0; i < n; i++)
    {
      seq[nums[i]] = i;
      max = max > nums[i] ? max : nums[i];
    }
    map<int, int>::iterator it;
    for (it = seq.begin(); it != seq.end(); ++it)
    {
      res[it->second] = to_string(n--);
    }
    if (nums.size() > 0)
      res[(--it)->second] = "Gold Medal";
    if (nums.size() > 1)
      res[(--it)->second] = "Silver Medal";
    if (nums.size() > 2)
      res[(--it)->second] = "Bronze Medal";
    return res;
  }
};
