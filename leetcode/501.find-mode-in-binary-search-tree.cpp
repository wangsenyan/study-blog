#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int max = 0;
  vector<int> res;

  vector<int> findMode(TreeNode *root)
  {
    int num = 1;
    inorderTraversal(root, num);
    return res;
  }
  void inorderTraversal(TreeNode *root, int &num)
  {
    if (root)
    {
      if (root->left)
      {
        if (root->val == root->left->val)
          num++;
        else
          num = 1;
        inorderTraversal(root->left, num);
      }
      if (num > max) //中序遍历
      {
        max = num;
        res.clear();
        res.push_back(root->val);
      }
      else if (num == max)
        res.push_back(root->val);
      if (root->right)
      {
        if (root->val == root->right->val)
          num++;
        else
          num = 1;
        inorderTraversal(root->right, num);
      }
    }
  }
};
