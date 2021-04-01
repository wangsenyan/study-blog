/*
 * @lc app=leetcode id=589 lang=cpp
 *
 * [589] N-ary Tree Preorder Traversal
 */
/*
// Definition for a Node.
class Node {
public:
    int val;
    vector<Node*> children;

    Node() {}

    Node(int _val, vector<Node*> _children) {
        val = _val;
        children = _children;
    }
};
*/
#include <iostream>
#include <vector>
using namespace std;
// class Node
// {
// public:
//   int val;
//   vector<Node *> children;

//   Node() {}

//   Node(int _val, vector<Node *> _children)
//   {
//     val = _val;
//     children = _children;
//   }
// };
class Solution
{
private:
  void PTT(Node *root, vector<int> &v)
  {
    if (!root)
      return;
    v.push_back(root->val);
    for (Node *c : root->children)
      PTT(c, v);
  }

public:
  vector<int> preorder(Node *root)
  {
    vector<int> res;
    PTT(root, res);
    return res;
  }
};
