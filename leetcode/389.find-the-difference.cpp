/*
 * @lc app=leetcode id=389 lang=cpp
 *
 * [389] Find the Difference
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  char findTheDifference(string s, string t)
  {
    int tmp = 0, i = 0;
    for (i = 0; i < s.size(); i++)
    {
      tmp = tmp ^ s[i];
      tmp = tmp ^ t[i];
    }
    return char(tmp ^ t[i]);
  }
};
