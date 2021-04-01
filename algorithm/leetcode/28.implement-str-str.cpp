/*
 * @lc app=leetcode id=28 lang=cpp
 *
 * [28] Implement strStr()
 *
 * https://leetcode.com/problems/implement-strstr/description/
 *
 * algorithms
 * Easy (31.50%)
 * Total Accepted:    409.1K
 * Total Submissions: 1.3M
 * Testcase Example:  '"hello"\n"ll"'
 *
 * Implement strStr().
 * 
 * Return the index of the first occurrence of needle in haystack, or -1 if
 * needle is not part of haystack.
 * 
 * Example 1:
 * 
 * 
 * Input: haystack = "hello", needle = "ll"
 * Output: 2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: haystack = "aaaaa", needle = "bba"
 * Output: -1
 * 
 * 
 * Clarification:
 * 
 * What should we return when needle is an empty string? This is a great
 * question to ask during an interview.
 * 
 * For the purpose of this problem, we will return 0 when needle is an empty
 * string. This is consistent to C's strstr() and Java's indexOf().
 * 
 */
#include <iostream>
#include <string>
#include <vector>
using namespace std;
// class Solution
// {
// public:
//   vector<int> cmf(string &needle)
//   {
//     int m = needle.size();
//     vector<int> p(m, 0);
//     int k = 0;
//     for (size_t q = 1; q < m; q++)
//     {
//       while (k > 0 && needle[k] != needle[q])
//         k = p[k - 1];
//       if (needle[k] == needle[q])
//         k++;
//       p[q] = k;
//     }
//     return p;
//   }
//   int strStr(string haystack, string needle)
//   {
//     int m = needle.size(), n = haystack.size();
//     if (m == 0)
//       return 0;
//     if (m > n)
//       return -1;
//     vector<int> pi = cmf(needle);
//     int k = 0;
//     cout << n << endl;
//     for (size_t i = 0; i < n; i++)
//     {
//       while (k > 0 && needle[k] != haystack[i])
//       {
//         cout << k << endl;
//         k = pi[k - 1];
//       }
//       if (needle[k] == haystack[i])
//       {
//         k = k + 1;
//       }

//       if (k == m)
//       {
//         return i - m + 1;
//       }
//     }
//     return -1;
//   }
// };
class Solution
{
public:
  int strStr(string haystack, string needle)
  {
    if (needle.length() == 0)
      return 0;
    int l1 = haystack.length();
    int l2 = needle.length();
    int j = 0, m = 0;
    if (l1 == l2)
    {
      if (haystack.compare(needle) == 0)
        return 0;
      else
        return -1;
    }
    for (int i = 0; i <= l1 - l2; i++)
    {
      if (haystack[i] == needle[0])
      {
        for (j = i, m = 0; j < i + l2 && m < l2; j++, m++)
        {
          if (haystack[j] != needle[m])
          {
            j = 0;
            m = 0;
            break;
          }
        }
        if (m == l2 && haystack[j - 1] == needle[l2 - 1])
          return i;
      }
    }
    return -1;
  }
};
