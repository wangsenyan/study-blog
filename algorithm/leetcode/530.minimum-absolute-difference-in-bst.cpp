/*
 * @lc app=leetcode id=530 lang=cpp
 *
 * [530] Minimum Absolute Difference in BST
 */
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;
// struct TreeNode
// {
//   int val;
//   TreeNode *left;
//   TreeNode *right;
//   TreeNode(int x) : val(x), left(NULL), right(NULL) {}
// };
class Solution
{
private:
  int m = INT_MAX;
  vector<int> tmp;
  void MTT(TreeNode *root)
  {
    if (root)
    {
      if (root->left)
        MTT(root->left);
      tmp.push_back(root->val);
      if (root->right)
        MTT(root->right);
    }
  }

public:
  int getMinimumDifference(TreeNode *root)
  {
    MTT(root);
    for (int i = 0; i < tmp.size() - 1; i++)
    {
      m = min(m, (tmp[i + 1] - tmp[i]));
      if (m == 0)
        break;
    }
    return m;
  }
};
