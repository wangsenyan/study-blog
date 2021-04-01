/*
 * @lc app=leetcode id=427 lang=cpp
 *
 * [427] Construct Quad Tree
 */
/*
// Definition for a QuadTree node.
class Node {
public:
    bool val;
    bool isLeaf;
    Node* topLeft;
    Node* topRight;
    Node* bottomLeft;
    Node* bottomRight;

    Node() {}

    Node(bool _val, bool _isLeaf, Node* _topLeft, Node* _topRight, Node* _bottomLeft, Node* _bottomRight) {
        val = _val;
        isLeaf = _isLeaf;
        topLeft = _topLeft;
        topRight = _topRight;
        bottomLeft = _bottomLeft;
        bottomRight = _bottomRight;
    }
};
*/
// class Node
// {
// public:
//   bool val;
//   bool isLeaf;
//   Node *topLeft;
//   Node *topRight;
//   Node *bottomLeft;
//   Node *bottomRight;

//   Node() {}

//   Node(bool _val, bool _isLeaf, Node *_topLeft, Node *_topRight, Node *_bottomLeft, Node *_bottomRight)
//   {
//     val = _val;
//     isLeaf = _isLeaf;
//     topLeft = _topLeft;
//     topRight = _topRight;
//     bottomLeft = _bottomLeft;
//     bottomRight = _bottomRight;
//   }
// };
class Solution
{
private:
  Node *buildNode(vector<vector<int>> &grid, int x, int y, int length)
  {
    if (length == 1)
    {
      return new Node(grid[x][y] == 1, true, nullptr, nullptr, nullptr, nullptr);
    }
    int newLength = length / 2;
    Node *topLeft = buildNode(grid, x, y, newLength);
    Node *topRight = buildNode(grid, x, y + newLength, newLength);
    Node *botLeft = buildNode(grid, x + newLength, y, newLength);
    Node *botRight = buildNode(grid, x + newLength, y + newLength, newLength);

    if (topLeft->isLeaf && topRight->isLeaf && botRight->isLeaf && botLeft->isLeaf &&
        ((topLeft->val && topRight->val && botLeft->val && botRight->val) ||
         !(topLeft->val || topRight->val || botLeft->val || botRight->val)))
    {
      bool val = topLeft->val;
      delete topLeft;
      topLeft = nullptr;
      delete topRight;
      topRight = nullptr;
      delete botLeft;
      botLeft = nullptr;
      delete botRight;
      botRight = nullptr;
      return new Node(val, true, nullptr, nullptr, nullptr, nullptr);
    }
    return new Node(true, false, topLeft, topRight, botLeft, botRight);
  }

public:
  Node *construct(vector<vector<int>> &grid)
  {
    int N = grid.size();
    if (N == 0)
    {
      return nullptr;
    }
    return buildNode(grid, 0, 0, N);
  }
};
