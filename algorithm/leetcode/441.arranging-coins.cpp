/*
 * @lc app=leetcode id=441 lang=cpp
 *
 * [441] Arranging Coins
 */
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
  int arrangeCoins(int n)
  {
    long long m = n;
    return (-1 + sqrt(1 + 8 * m)) / 2;
  }
};
