/*
 * @lc app=leetcode id=48 lang=cpp
 *
 * [48] Rotate Image
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  void rotate(vector<vector<int>> &matrix) //a[i][j]->a[j][n-i-1]
  {
    int n = matrix.size();
    vector<vector<int>> temp = matrix;
    for (int i = 0; i < n; i++)
      for (int j = 0; j < n; j++)
        matrix[i][j] = temp[n - j - 1][i];
  }
};
