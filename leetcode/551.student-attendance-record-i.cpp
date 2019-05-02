#include <iostream>
#include <string>
using namespace std;
class Solution
{
public:
  bool checkRecord(string s)
  {
    int a = 0, l = 0;
    for (int i = 0; i < s.size(); i++)
    {
      if (s[i] == 'A')
        a++;
      else if (s[i] == 'L')
      {
        if (i == 0 || s[i] == s[i - 1])
          l++;
        else
          l = 1;
      }
      if (a > 1 || l > 2)
        return false;
    }
    return true;
  }
};
