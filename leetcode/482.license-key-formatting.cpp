/*
 * @lc app=leetcode id=482 lang=cpp
 *
 * [482] License Key Formatting
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  string licenseKeyFormatting(string S, int K)
  {
    string str;
    for (int i = S.size() - 1, j = 0; i >= 0 && K > 0; i--)
    {
      if (j < K && S[i] != '-')
      {
        str = char(S[i] >= 'a' ? S[i] - 32 : S[i]) + str;
        j++;
      }
      else if (S[i] != '-')
      {
        str = '-' + str;
        str = char(S[i] >= 'a' ? S[i] - 32 : S[i]) + str;
        j = 1;
      }
      //cout << j << " " << S[i] << " " << str << endl;
    }
    return str;
  }
};
