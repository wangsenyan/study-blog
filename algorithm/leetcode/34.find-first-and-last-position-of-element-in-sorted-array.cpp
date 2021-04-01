/*
 * @lc app=leetcode id=34 lang=cpp
 *
 * [34] Find First and Last Position of Element in Sorted Array
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  vector<int> searchRange(vector<int> &nums, int target)
  {
    int idx1 = lower_bound(nums, target);
    int idx2 = lower_bound(nums, target + 1) - 1;
    if (idx1 < nums.size() && nums[idx1] == target)
      return {idx1, idx2};
    else
      return {-1, -1};
  }

  int lower_bound(vector<int> &nums, int target)
  {
    int l = 0, r = nums.size() - 1;
    while (l <= r)
    {
      int mid = (r - l) / 2 + l;
      if (nums[mid] < target)
        l = mid + 1;
      else
        r = mid - 1;
    }
    return l;
  }
};

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
      vector<int> tmp(9, 0);
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
      vector<int> tmp(9, 0);
      for (j = 0; j < 9; j++)
      {
        if (board[i][j] != '.')
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
    int i, j, k = 1;
    vector<int> tmp(9, 0);
    for (i = l; i < l + 3; i++)
    {
      for (j = r; j < r + 3; j++)
      {
        if (tmp[board[j][i] - '0'] == 1)
          return false;
        tmp[board[j][i] - '0'] = 1;
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
      vector<int> tmp(9, 0);
      for (j = 0; j < 9; j += 3)
      {
        if (!eachMatrix(board, i, j))
          return false;
      }
    }
    return eachCol(board) && eachRow(board);
  }
};
int main()
{
  //	ListNode *l=new ListNode(0);
  //	ListNode *h=l;
  //	for(int i=1;i<6;i++)
  //	{
  //		ListNode *p=new ListNode(i);
  //		h->next=p;
  //		h=h->next;
  //	}
  vector<vector<char>> e = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                            {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                            {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                            {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                            {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                            {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                            {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                            {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                            {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};
  vector<int>
      v = {1, 2, 2};
  Solution s;
  auto a = s.isValidSudoku(e);
  //s.nextPermutation(v);
  cout << a << endl;
  //    while(a)
  //    {
  //    	cout<<a->val<<endl;
  //    	a=a->next;
  //	}
  //	for(int i=0;i<a.size();i++)
  //      cout<<a[i]<<'\t';
}