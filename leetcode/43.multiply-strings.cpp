#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
//can multiply with ftt ???
/*
            123456
          X  11111
          ----------
            123456
           123456
          123456
         123456
        123456
each bit equal to i+j=k,  i is first string's char position,j is second's,k is answer's
*/
class Solution
{
public:
  string multiply(string num1, string num2)
  {
    if (num1 == "0" || num2 == "0")
      return "0";
    int m = num1.size() - 1, n = num2.size() - 1, carry = 0;
    string product;
    for (int i = 0; i <= m + n || carry; ++i)
    {
      for (int j = max(0, i - n); j <= min(i, m); ++j)
        carry += (num1[m - j] - '0') * (num2[n - i + j] - '0');
      product += carry % 10 + '0';
      carry /= 10;
    }
    reverse(begin(product), end(product));
    return product;
  }
};
