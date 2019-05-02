/*
 * @lc app=leetcode id=20 lang=cpp
 *
 * [20] Valid Parentheses
 *
 * https://leetcode.com/problems/valid-parentheses/description/
 *
 * algorithms
 * Easy (36.12%)
 * Total Accepted:    561.2K
 * Total Submissions: 1.5M
 * Testcase Example:  '"()"'
 *
 * Given a string containing just the characters '(', ')', '{', '}', '[' and
 * ']', determine if the input string is valid.
 * 
 * An input string is valid if:
 * 
 * 
 * Open brackets must be closed by the same type of brackets.
 * Open brackets must be closed in the correct order.
 * 
 * 
 * Note that an empty string is also considered valid.
 * 
 * Example 1:
 * 
 * 
 * Input: "()"
 * Output: true
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: "()[]{}"
 * Output: true
 * 
 * 
 * Example 3:
 * 
 * 
 * Input: "(]"
 * Output: false
 * 
 * 
 * Example 4:
 * 
 * 
 * Input: "([)]"
 * Output: false
 * 
 * 
 * Example 5:
 * 
 * 
 * Input: "{[]}"
 * Output: true
 * 
 * 
 */
#include <iostream>
#include <string>
#include <unordered_map>
#include <stack>
class Solution
{
public:
  bool isValid(std::string s)
  {
    std::unordered_map<char, char> map;
    map[')'] = '(';
    map['}'] = '{';
    map[']'] = '[';
    std::stack<char> ss;
    for (size_t i = 0; i < s.size(); i++)
    {
      if (!ss.empty() && ss.top() == map[s[i]])
        ss.pop();
      else
        ss.push(s[i]);
    }
    return ss.empty();
  }
};
