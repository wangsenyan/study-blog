/*
 * @lc app=leetcode id=557 lang=cpp
 *
 * [557] Reverse Words in a String III
 */
#include <iostream>
#include <string>
using namespace std;
class Solution
{
private:
  void rev(string &s, int p, int q) //反转p到q-1
  {
    for (int i = p, j = q - 1; i < j; i++, j--)
    {
      char t = s[i];
      s[i] = s[j];
      s[j] = t;
    }
  };

public:
  string reverseWords(string s)
  {
    string str = s;
    for (int i = 0, j = 0; i < s.size() && j < s.size(); i++)
    {
      if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
      {
        j = i;
      }
      else if (s[i] != ' ' && (i == s.size() - 1 || s[i + 1] == ' '))
      {
        //cout << i << " " << j << endl;
        rev(str, j, i + 1);
        //j = i + 1;
      }
      //cout<<i<<" "<<j<<endl;
    }
    return str;
  }
};
