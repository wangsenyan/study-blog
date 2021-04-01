/*
 * @lc app=leetcode id=79 lang=cpp
 *
 * [79] Word Search
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  bool exist(vector<vector<char>> &board, string word)
  {
    int i = 0, j = 0, k = 0;
    bool r = true;
    int m = board.size(), n = m == 0 ? 0 : board[0].size();
    vector<vector<int>> bt(m, vector<int>(n, 0));
    while (i < m)
    {
      while (j < n)
      {
        if (bt[i][j] == 0 && board[i][j] == word[k])
        {
          bt[i][j] = 1;
          k++;
          if (j < n - 1 && board[i][j + 1] == word[k])
          {
            r = true;
            j++;
          }
          else if (i < n - 1 && board[i + 1][j] == word[k])
            i++;
          else
        }
        else
        {
        }
      }
    }
  }
};
