/*
 * @lc app=leetcode id=345 lang=cpp
 *
 * [345] Reverse Vowels of a String
 */
class Solution
{
public:
  string reverseVowels(string s)
  {
    vector<int> index;
    set<char> voy = {'a', 'e', 'i', 'o', 'u', 'A', 'E', 'I', 'O', 'U'};
    for (int i = 0; i < s.length(); i++)
      if (voy.count(s[i]))
        index.push_back(i);
    int n = index.size();
    for (int i = 0; i < n / 2; i++)
    {
      char tmp = s[index[i]];
      s[index[i]] = s[index[n - 1 - i]];
      s[index[n - 1 - i]] = tmp;
    }
    return s;
  }
};
