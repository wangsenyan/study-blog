/*
 * @lc app=leetcode id=40 lang=cpp
 *
 * [40] Combination Sum II
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
private:
  void search(vector<int> &num, int next, vector<int> &tmp, int target, vector<vector<int>> &result, int pre)
  {
    if (target == 0)
    {
      result.push_back(tmp);
      return;
    }
    if (next == num.size() || target - num[next] < 0)
      return;
    if (next > 0 && num[next] == num[next - 1] && pre == target)
      search(num, next + 1, tmp, target, result, target);
    else
    {
      tmp.push_back(num[next]);
      search(num, next + 1, tmp, target - num[next], result, target);
      tmp.pop_back();
      search(num, next + 1, tmp, target, result, target);
    }
  }

public:
  vector<vector<int>> combinationSum2(vector<int> &candidates, int target)
  {
    vector<vector<int>> result;
    sort(candidates.begin(), candidates.end());
    vector<int> tmp;
    search(candidates, 0, tmp, target, result, target);
    return result;
  }
};
