class Solution
{
public:
  bool isPalindrome(string s)
  {
    int i = 0, j = s.size() - 1;
    while (i < j)
    {
      while (!isalnum(s[i]) && i < j)
        ++i;
      while (!isalnum(s[j]) && i < j)
        --j;

      if (s[i] >= 65 && s[i] <= 90)
        s[i] += 32;
      if (s[j] >= 65 && s[j] <= 90)
        s[j] += 32;

      if (s[i] != s[j])
        return false;
      i++;
      j--;
    }
    return true;
  }
};
