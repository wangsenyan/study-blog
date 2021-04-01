/*
 * @lc app=leetcode id=58 lang=cpp
 *
 * [58] Length of Last Word
 *
 * https://leetcode.com/problems/length-of-last-word/description/
 *
 * algorithms
 * Easy (32.19%)
 * Total Accepted:    258.8K
 * Total Submissions: 803.2K
 * Testcase Example:  '"Hello World"'
 *
 * Given a string s consists of upper/lower-case alphabets and empty space
 * characters ' ', return the length of last word in the string.
 * 
 * If the last word does not exist, return 0.
 * 
 * Note: A word is defined as a character sequence consists of non-space
 * characters only.
 * 
 * Example:
 * 
 * Input: "Hello World"
 * Output: 5
 * 
 * 
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  int lengthOfLastWord(string s)
  {
    int j = 0, i = s.size() - 1;
    cout << i << endl;
    while (i >= 0 && s[i] == ' ')
      i--;
    cout << i << endl;
    while (i >= 0 && s[i] != ' ')
    {
      i--;
      j++;
    }
    return j;
  }
};
