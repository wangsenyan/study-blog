/*
 * @lc app=leetcode id=563 lang=cpp
 *
 * [563] Binary Tree Tilt
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
using namespace std;
//这道题讲的不明不白的，真是垃圾
class Solution
{
public:
  int findTilt(TreeNode *root)
  {
    int res = 0;
    postorder(root, res);
    return res;
  }
  int postorder(TreeNode *node, int &res)
  {
    if (!node)
      return 0;
    int leftSum = postorder(node->left, res);
    int rightSum = postorder(node->right, res);
    res += abs(leftSum - rightSum);
    return leftSum + rightSum + node->val;
  }
};
