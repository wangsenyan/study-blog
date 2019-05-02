/*
 * @lc app=leetcode id=107 lang=cpp
 *
 * [107] Binary Tree Level Order Traversal II
 *
 * https://leetcode.com/problems/binary-tree-level-order-traversal-ii/description/
 *
 * algorithms
 * Easy (45.98%)
 * Total Accepted:    218.9K
 * Total Submissions: 473K
 * Testcase Example:  '[3,9,20,null,null,15,7]'
 *
 * Given a binary tree, return the bottom-up level order traversal of its
 * nodes' values. (ie, from left to right, level by level from leaf to root).
 * 
 * 
 * For example:
 * Given binary tree [3,9,20,null,null,15,7],
 * 
 * ⁠   3
 * ⁠  / \
 * ⁠ 9  20
 * ⁠   /  \
 * ⁠  15   7
 * 
 * 
 * 
 * return its bottom-up level order traversal as:
 * 
 * [
 * ⁠ [15,7],
 * ⁠ [9,20],
 * ⁠ [3]
 * ]
 * 
 * 
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
//#include <algorithm>
#include <queue>
using namespace std;
class Solution
{
public:
  vector<vector<int>> levelOrderBottom(TreeNode *root)
  {
    vector<vector<int>> res;
    if (!root)
      return res;
    queue<TreeNode *> cur;
    cur.push(root);
    while (!cur.empty())
    {
      vector<int> temp;
      int size = cur.size();
      for (int i = 0; i < size; i++)
      {
        TreeNode *top = cur.front();
        cur.pop();
        temp.push_back(top->val);
        if (top->left)
          cur.push(top->left);
        if (top->right)
          cur.push(top->right);
      }
      res.push_back(temp);
    }
    reverse(res.begin(), res.end());
    return res;
  }
};
