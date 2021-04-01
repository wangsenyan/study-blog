/*
 * @lc app=leetcode id=202 lang=cpp
 *
 * [202] Happy Number
 *
 * https://leetcode.com/problems/happy-number/description/
 *
 * algorithms
 * Easy (44.54%)
 * Total Accepted:    225.1K
 * Total Submissions: 502.1K
 * Testcase Example:  '19'
 *
 * Write an algorithm to determine if a number is "happy".
 * 
 * A happy number is a number defined by the following process: Starting with
 * any positive integer, replace the number by the sum of the squares of its
 * digits, and repeat the process until the number equals 1 (where it will
 * stay), or it loops endlessly in a cycle which does not include 1. Those
 * numbers for which this process ends in 1 are happy numbers.
 * 
 * Example: 
 * 
 * 
 * Input: 19
 * Output: true
 * Explanation: 
 * 1^2 + 9^2 = 82
 * 8^2 + 2^2 = 68
 * 6^2 + 8^2 = 100
 * 1^2 + 0^2 + 0^2 = 1
 * 
 */
#include <iostream>
#include <set>
using namespace std;
class Solution
{
public:
  bool isHappy(int n)
  {
    set<int> s{4, 16, 37, 58, 89, 145, 42, 20};
    int h = n;
    int r = 0;
    int t = 0;
    while (h != 1)
    {
      n = h;
      h = 0;
      while (n)
      {
        r = n % 10;
        h += r * r;
        n = n / 10;
      }
      if (s.find(h) != s.end())
        return false;
    }
    return true;
  }
};
