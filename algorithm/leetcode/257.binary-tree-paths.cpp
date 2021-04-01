/*
 * @lc app=leetcode id=257 lang=cpp
 *
 * [257] Binary Tree Paths
 *
 * https://leetcode.com/problems/binary-tree-paths/description/
 *
 * algorithms
 * Easy (45.31%)
 * Total Accepted:    219.7K
 * Total Submissions: 481.8K
 * Testcase Example:  '[1,2,3,null,5]'
 *
 * Given a binary tree, return all root-to-leaf paths.
 * 
 * Note: A leaf is a node with no children.
 * 
 * Example:
 * 
 * 
 * Input:
 * 
 * ⁠  1
 * ⁠/   \
 * 2     3
 * ⁠\
 * ⁠ 5
 * 
 * Output: ["1->2->5", "1->3"]
 * 
 * Explanation: All root-to-leaf paths are: 1->2->5, 1->3
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
#include <string>
using namespace std;
class Solution
{
private:
  vector<string> s;
  void concatString(TreeNode *root, string ss)
  {
    if (!root->left && !root->right)
      s.push_back(ss);
    else
    {
      if (root->left)
        concatString(root->left, ss + "->" + to_string(root->left->val));
      if (root->right)
        concatString(root->right, ss + "->" + to_string(root->right->val));
    }
  }

public:
  vector<string> binaryTreePaths(TreeNode *root)
  {
    string ss;
    if (!root)
      return s;
    concatString(root, ss + to_string(root->val));
    return s;
  }
};
