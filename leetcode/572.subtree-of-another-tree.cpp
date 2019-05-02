/*
 * @lc app=leetcode id=572 lang=cpp
 *
 * [572] Subtree of Another Tree
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
public:
  bool isSubtree(TreeNode *s, TreeNode *t)
  {
    return !t || s && (isSameTree(s, t) || isSubtree(s->left, t) || isSubtree(s->right, t));
  }

private:
  bool isSameTree(TreeNode *s, TreeNode *t)
  {
    return !s ? !t : t && s->val == t->val && isSameTree(s->left, t->left) && isSameTree(s->right, t->right);
  }
};
