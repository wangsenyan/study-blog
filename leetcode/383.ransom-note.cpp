/*
 * @lc app=leetcode id=383 lang=cpp
 *
 * [383] Ransom Note
 */
// #include <iostream>
// #include <string>
// #include <vector>
// using namespace std;
// class Solution
// {
// public:
//   bool canConstruct(string ransomNote, string magazine)
//   {
//     int n = ransomNote.size(), m = magazine.size();
//     if (n > m)
//       return false;
//     vector<int> p(n, 0);
//     for (int i = 1, k = 0; i < n; i++)
//     {
//       while (k > 0 && ransomNote[k] != ransomNote[i])
//         k = p[k - 1];
//       if (ransomNote[k] == ransomNote[i])
//         k++;
//       p[i] = k;
//     }
//     for (int i = 0, k = 0; i < m; i++)
//     {
//       while (k > 0 && ransomNote[k] != magazine[i])
//         k = p[k - 1];
//       if (ransomNote[k] == magazine[i])
//         k = k + 1;
//       if (k == n)
//         return true;
//     }
//     return false;
//   }
// };
class Solution
{
public:
  bool canConstruct(string ransomNote, string magazine)
  {
    unordered_map<char, int> m;
    for (char c : magazine)
      ++m[c];
    for (char c : ransomNote)
    {
      if (--m[c] < 0)
        return false;
    }
    return true;
  }
};
