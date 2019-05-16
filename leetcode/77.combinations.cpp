/*
 * @lc app=leetcode id=77 lang=cpp
 *
 * [77] Combinations
 */
#include <iostream>
#include <vector>
using namespace std;
// class Solution
// {
// public:
//   vector<vector<int>> combine(int n, int k)
//   {
//     vector<vector<int>> res;
//     vector<int> r;
//     combination(res, r, 0, 0, k, n);
//     return res;
//   }
//   void combination(vector<vector<int>> &res, vector<int> r, int i, int m, int k, int n)
//   {
//     if (m == k)
//       res.push_back(r);
//     else if (i < n)
//     {
//       r.push_back(i + 1);
//       combination(res, r, i + 1, m + 1, k, n);
//       r.pop_back();
//       combination(res, r, i + 1, m, k, n);
//     }
//   }
// };
class Solution
{
public:
  vector<vector<int>> combine(int n, int k)
  {
    vector<vector<int>> result;
    int i = 0;
    vector<int> p(k, 0);
    while (i >= 0)
    {
      p[i]++;
      if (p[i] > n)
        --i;
      else if (i == k - 1)
        result.push_back(p);
      else
      {
        ++i;
        p[i] = p[i - 1];
      }
    }
    return result;
  }
};
