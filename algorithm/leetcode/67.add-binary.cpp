/*
 * @lc app=leetcode id=67 lang=cpp
 *
 * [67] Add Binary
 *
 * https://leetcode.com/problems/add-binary/description/
 *
 * algorithms
 * Easy (38.33%)
 * Total Accepted:    291.9K
 * Total Submissions: 755.6K
 * Testcase Example:  '"11"\n"1"'
 *
 * Given two binary strings, return their sum (also a binary string).
 * 
 * The input strings are both non-empty and contains only characters 1 or 0.
 * 
 * Example 1:
 * 
 * 
 * Input: a = "11", b = "1"
 * Output: "100"
 * 
 * Example 2:
 * 
 * 
 * Input: a = "1010", b = "1011"
 * Output: "10101"
 * 
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  string addBinary(string a, string b)
  {
    string s = "";
    int c = 0, i = a.size() - 1, j = b.size() - 1;
    while (i >= 0 || j >= 0 || c == 1)
    {
      c += i >= 0 ? a[i--] - '0' : 0;
      c += j >= 0 ? b[j--] - '0' : 0;
      s.insert(0, 1, char(c % 2 + '0'));
      c /= 2;
    }
    return s;
  }
};
