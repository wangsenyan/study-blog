/*
 * @lc app=leetcode id=60 lang=cpp
 *
 * [60] Permutation Sequence
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
class Solution
{
public:
  string getPermutation(int n, int k)
  {
    vector<int> e(n, 0);
    string s;
    int a = 1, j, l, m = n;
    for (int i = 1; i <= n; i++)
      a *= i;
    k = k - 1;
    while (k > 0)
    {
      a /= n;
      n--;
      for (j = 0, l = 0; j < m && l <= k / a; j++)
      {
        if (e[j] == 0)
          l++;
      }
      s += char(j + '0');
      e[j - 1] = 1;
      k %= a;
    }
    for (int i = 0; i < m; i++)
      if (e[i] == 0)
        s += char(i + 1 + '0');
    return s;
  }
};
