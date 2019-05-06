#include <iostream>
#include <string>
#include<algorithm>
using namespace std;
//∏µ¿Ô“∂£ø£ø£ø
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
      cout<<product<<endl;
      carry /= 10;
    }
    reverse(begin(product), end(product));
    return product;
  }
};
int main()
{
  //	ListNode *l=new ListNode(0);
  //	ListNode *h=l;
  //	for(int i=1;i<6;i++)
  //	{
  //		ListNode *p=new ListNode(i);
  //		h->next=p;
  //		h=h->next;
  //	}
//  vector<vector<char>> e ={
//  {'8','3','.','.','7','.','.','.','.'},
//  {'6','.','.','1','9','5','.','.','.'},
//  {'.','9','8','.','.','.','.','6','.'},
//  {'8','.','.','.','6','.','.','.','3'},
//  {'4','.','.','8','.','3','.','.','1'},
//  {'7','.','.','.','2','.','.','.','6'},
//  {'.','6','.','.','.','.','2','8','.'},
//  {'.','.','.','4','1','9','.','.','5'},
//  {'.','.','.','.','8','.','.','7','9'}
//};

  vector<int>v = {10,1,2,7,6,1,5};
  Solution s;
  auto a = s.multiply("123","123423");
  cout<<a<<endl;
  //s.nextPermutation(v);
  //cout << a << endl;
  //    while(a)
  //    {
  //    	cout<<a->val<<endl;
  //    	a=a->next;
  //	}
//  	for(int i=0;i<a.size();i++)
//  	{
//  	   for(int j=0;j<a[i].size();j++)
//        cout<<a[i][j]<<'\t';
//       cout<<endl;
//	}
//  	  for(int j=0;j<a[i].size();j++)
//        cout<<a[i][j]<<'\t';
}
