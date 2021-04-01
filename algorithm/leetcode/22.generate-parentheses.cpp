/*
 * @lc app=leetcode id=22 lang=cpp
 *
 * [22] Generate Parentheses
 */
#include <iostream>
#include <vector>
#include <string>
using namespace std;
class Solution
{
public:
  vector<string> generateParenthesis(int n)
  {
    vector<string> parens;
    string paren;
    generate(n, 0, 0, paren, parens);
    return parens;
  }

private:
  void generate(int n, int l, int r, string paren, vector<string> &parens)
  {
    if (l == n && r == n)
    {
      parens.push_back(paren);
    }
    else
    {
      if (l < n)
      {
        generate(n, l + 1, r, paren + '(', parens);
      }
      if (r < l)
      {
        generate(n, l, r + 1, paren + ')', parens);
      }
    }
  }
};

class Solution
{
public:
  void search(vector<int> &num, int next, vector<int> &pSol, int target, vector<vector<int>> &result)
  {
    if (target == 0)
    {
      result.push_back(pSol);
      return;
    }

    if (next == num.size() || target - num[next] < 0)
      return;

    pSol.push_back(num[next]);
    search(num, next, pSol, target - num[next], result);
    pSol.pop_back();

    search(num, next + 1, pSol, target, result);
  }

  vector<vector<int>> combinationSum(vector<int> &num, int target)
  {
    vector<vector<int>> result;
    sort(num.begin(), num.end());
    vector<int> pSol;
    search(num, 0, pSol, target, result);
    return result;
  }
};
