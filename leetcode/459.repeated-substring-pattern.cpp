/*
 * @lc app=leetcode id=459 lang=cpp
 *
 * [459] Repeated Substring Pattern
 */

class Solution
{
  static inline bool eval(const string &s, int i)
  {
    if (s[i - 1] != s.back() || 0 != s.size() % i)
      return false;

    for (int j = i, k = 0; j < s.size(); ++j, k = (k + 1) % i)
    {
      if (s[j] != s[k])
        return false;
    }
    return true;
  }

public:
  bool repeatedSubstringPattern(string s)
  {
    for (int i = s.size() / 2; i >= 1; --i)
    {
      if (eval(s, i))
        return true;
    }
    return false;
  }
};
// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
// class Solution
// {
// public:
//   bool repeatedSubstringPattern(string s)
//   {
//     int k = 0, j = 0;
//     vector<int> p(s.size(), 0);
//     for (int i = 1; i < s.size(); i++)
//     {
//       while (k > 0 && s[i] != s[k])
//         k = p[k - 1];
//       if (s[i] == s[k])
//         k = k + 1;
//       p[i] = k;
//     }
//     k = 0;
//     for (; j < s.size(); j++)
//     {
//       if (p[j] == 0)
//         k++;
//       else
//         break;
//     }
//     for (j = k; j < s.size(); j++)
//     {
//       if (s[j % k] != s[j])
//         return false;
//     }
//     return (j % k == 0 && j > 1) ? true : false;
//   }
// };
