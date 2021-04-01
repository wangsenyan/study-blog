/*
 * @lc app=leetcode id=8 lang=cpp
 *
 * [8] String to Integer (atoi)
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  int myAtoi(string str)
  {
    int n = str.size();
    if (n == 0 || ((str[0] < '0' || str[0] > '9') && (str[0] != '+' && str[0] != ' ' && str[0] != '-')))
      return 0;
    int i = 0;
    bool tag = false; //是否负数
    long long num = 0;
    while (str[i] == ' ')
      i++;
    if (str[i] == '-')
    {
      tag = true;
      i++;
    }
    else if (str[i] == '+')
    {
      tag = false;
      i++;
    }
    while (str[i] >= '0' && str[i] <= '9')
    {
      num = num * 10 + str[i] - '0';
      i++;
      if (num > INT_MAX)
        break;
    }
    num = tag ? -num : num;
    if (num > INT_MAX)
      num = INT_MAX;
    if (num < INT_MIN)
      num = INT_MIN;
    return num;
  }
};
