/*
 * @lc app=leetcode id=461 lang=cpp
 *
 * [461] Hamming Distance
 */
class Solution
{
public:
  int hammingDistance(int x, int y)
  {
    int r = x ^ y;
    int res = 0;
    while (r)
    {
      res += r & 0x1;
      r >>= 1;
    }
    return res;
  }
};
