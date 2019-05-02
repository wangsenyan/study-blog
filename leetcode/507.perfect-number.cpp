/*
 * @lc app=leetcode id=507 lang=cpp
 *
 * [507] Perfect Number
 */
#include <iostream>
using namespace std;
class Solution
{
public:
  bool checkPerfectNumber(int num)
  {
    static unordered_set<int> n = {6, 28, 496, 8128, 33550336};
    return n.count(num);
  }
};
