/*
 * @lc app=leetcode id=559 lang=cpp
 *
 * [559] Maximum Depth of N-ary Tree
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
public:
  int maxDepth(Node *root)
  {
    if (!root)
      return 0;
    int max = 0;
    for (int i = 0; i < root->children.size(); i++)
    {
      int dep = maxDepth(root->children[i]);
      max = max > dep ? max : dep;
    }
    return max + 1;
  }
};
