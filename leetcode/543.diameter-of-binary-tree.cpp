/*
 * @lc app=leetcode id=543 lang=cpp
 *
 * [543] Diameter of Binary Tree
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
  int m = 0;

public:
  int diameterOfBinaryTree(TreeNode *root) //计算每个结点左子树与右子树最大深度和
  {
    if (!root)
      return 0;
    BSTSearch(root);
    return m;
  };
  int BSTSearch(TreeNode *root)
  {
    if (!root)
      return 0;
    int l = 1 + BSTSearch(root->left);
    int r = 1 + BSTSearch(root->right);
    m = max(m, l + r - 2);
    return max(l, r);
  }
};
