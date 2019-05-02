/*
 * @lc app=leetcode id=400 lang=cpp
 *
 * [400] Nth Digit
 */
#include <iostream>
#include <vector>
using namespace std;
class Solution
{
public:
  int findNthDigit(int num)
  {
    if (num < 10)
      return num;
    int flag = 1, i = 0, pl = num, coun = 0, ac;
    while (flag)
    {
      pl = pl - (i + 1) * 9 * pow(10, i);
      if (pl < 0)
        flag = 0;
      else
      {
        ac = pl;
        coun += (9 * pow(10, i));
      }
      i++;
    }
    cout << coun << " " << ac << " " << i << endl;
    int numb = coun + ceil((double)ac / i);
    string res = to_string(numb);
    if (ac % i == 0)
      return (int)(res[res.length() - 1] - '0');
    return (int)(res[ac % i - 1] - '0');
  }
};
