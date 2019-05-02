/*
 * @lc app=leetcode id=590 lang=cpp
 *
 * [590] N-ary Tree Postorder Traversal
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
  void post(Node *root, vector<int> &v)
  {
    if (!root)
      return;
    for (Node *c : root->children)
      post(c, v);
    v.push_back(root->val);
  }

public:
  vector<int> postorder(Node *root)
  {
    vector<int> res;
    post(root, res);
    return res;
  }
};
