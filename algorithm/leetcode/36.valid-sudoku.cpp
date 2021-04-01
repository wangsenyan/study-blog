#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;
class Solution
{
private:
  bool eachRow(vector<vector<char>> &board)
  {
    int i, j;
    for (i = 0; i < 9; i++)
    {
      vector<int> tmp(10, 0);
      for (j = 0; j < 9; j++)
      {
        if (board[i][j] != '.')
        {
          if (tmp[board[i][j] - '0'] == 1)
            return false;
          tmp[board[i][j] - '0'] = 1;
        }
      }
    }
    return true;
  }
  bool eachCol(vector<vector<char>> &board)
  {
    int i, j;
    for (i = 0; i < 9; i++)
    {
      vector<int> tmp(10, 0);
      for (j = 0; j < 9; j++)
      {
        if (board[j][i] != '.')
        {
          if (tmp[board[j][i] - '0'] == 1)
            return false;
          tmp[board[j][i] - '0'] = 1;
        }
      }
    }
    return true;
  }
  bool eachMatrix(vector<vector<char>> &board, int l, int r)
  {
    int i, j;
    vector<int> tmp(10, 0);
    for (i = l; i < l + 3; i++)
    {
      for (j = r; j < r + 3; j++)
      {
        if (board[i][j] != '.')
        {
          if (tmp[board[i][j] - '0'] == 1)
            return false;
          tmp[board[i][j] - '0'] = 1;
        }
      }
    }
    return true;
  }

public:
  bool isValidSudoku(vector<vector<char>> &board)
  {
    int i, j;
    for (i = 0; i < 9; i += 3)
    {
      for (j = 0; j < 9; j += 3)
      {
        if (!eachMatrix(board, i, j))
          return false;
      }
    }
    return eachCol(board) && eachRow(board);
  }
};
