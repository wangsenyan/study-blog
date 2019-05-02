/*
 * @lc app=leetcode id=231 lang=cpp
 *
 * [231] Power of Two
 *
 * https://leetcode.com/problems/power-of-two/description/
 *
 * algorithms
 * Easy (41.72%)
 * Total Accepted:    222.1K
 * Total Submissions: 531K
 * Testcase Example:  '1'
 *
 * Given an integer, write a function to determine if it is a power of two.
 * 
 * Example 1:
 * 
 * 
 * Input: 1
 * Output: true 
 * Explanation: 2^0 = 1
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 16
 * Output: true
 * Explanation: 2^4 = 16
 * 
 * Example 3:
 * 
 * 
 * Input: 218
 * Output: false
 * 
 */
#include <iostream>
#include <algorithm>
using namespace std;
class Solution
{
public:
  bool isPowerOfTwo(int n)
  {
    int m = 0;
    while (n > 0)
    {
      m += n & 0x1;
      n >>= 1;
    }
    if (m == 1)
      return true;
    return false;
  }
};
