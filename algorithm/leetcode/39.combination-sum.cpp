/*
 * @lc app=leetcode id=39 lang=cpp
 *
 * [39] Combination Sum
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
private:
  void search(vector<int> &num, int next, vector<int> &tmp, int target, vector<vector<int>> &result)
  {
    if (target == 0)
    {
      result.push_back(tmp);
      return;
    }

    if (next == num.size() || target - num[next] < 0)
      return;
    tmp.push_back(num[next]);
    search(num, next, tmp, target - num[next], result);
    tmp.pop_back();

    search(num, next + 1, tmp, target, result);
  }

public:
  vector<vector<int>> combinationSum(vector<int> &candidates, int target)
  {
    vector<vector<int>> result;
    sort(candidates.begin(), candidates.end());
    vector<int> tmp;
    search(candidates, 0, tmp, target, result);
    return result;
  }
};
