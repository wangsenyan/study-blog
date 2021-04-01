/*
 * @lc app=leetcode id=225 lang=cpp
 *
 * [225] Implement Stack using Queues
 *
 * https://leetcode.com/problems/implement-stack-using-queues/description/
 *
 * algorithms
 * Easy (38.40%)
 * Total Accepted:    125.6K
 * Total Submissions: 323.9K
 * Testcase Example:  '["MyStack","push","push","top","pop","empty"]\n[[],[1],[2],[],[],[]]'
 *
 * Implement the following operations of a stack using queues.
 * 
 * 
 * push(x) -- Push element x onto stack.
 * pop() -- Removes the element on top of the stack.
 * top() -- Get the top element.
 * empty() -- Return whether the stack is empty.
 * 
 * 
 * Example:
 * 
 * 
 * MyStack stack = new MyStack();
 * 
 * stack.push(1);
 * stack.push(2);  
 * stack.top();   // returns 2
 * stack.pop();   // returns 2
 * stack.empty(); // returns false
 * 
 * Notes:
 * 
 * 
 * You must use only standard operations of a queue -- which means only push to
 * back, peek/pop from front, size, and is empty operations are valid.
 * Depending on your language, queue may not be supported natively. You may
 * simulate a queue by using a list or deque (double-ended queue), as long as
 * you use only standard operations of a queue.
 * You may assume that all operations are valid (for example, no pop or top
 * operations will be called on an empty stack).
 * 
 * 
 */
#include <iostream>
#include <queue>
using namespace std;
class MyStack
{
private:
  queue<int> q1, q2;

public:
  /** Initialize your data structure here. */
  MyStack(){};

  /** Push element x onto stack. */
  void push(int x)
  {
    if (!q1.empty())
      q1.push(x);
    else
      q2.push(x);
  };
  /** Removes the element on top of the stack and returns that element. */
  int pop()
  {
    int q;
    if (q1.empty())
    {
      while (q2.size() > 1)
      {
        q1.push(q2.front());
        q2.pop();
      }
      q = q2.front();
      q2.pop();
      return q;
    }
    else
    {
      while (q1.size() > 1)
      {
        q2.push(q1.front());
        q1.pop();
      }
      q = q1.front();
      q1.pop();
      return q;
    }
  };

  /** Get the top element. */
  int top()
  {
    if (q1.empty())
      return q2.back();
    else
      return q1.back();
  };

  /** Returns whether the stack is empty. */
  bool empty()
  {
    if (q1.empty() && q2.empty())
      return true;
    return false;
  }
};
/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
