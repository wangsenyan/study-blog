/*
 * @lc app=leetcode id=492 lang=cpp
 *
 * [492] Construct the Rectangle
 */
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;
class Solution
{
public:
  vector<int> constructRectangle(int area)
  {
    int j = 0, m = sqrt(area);
    for (int i = m; i > 0; i--)
    {
      if (area % i == 0)
      {
        j = i;
        break;
      }
    }
    return vector<int>{area / j, j};
  }
};
