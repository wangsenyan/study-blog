/*
 * @lc app=leetcode id=24 lang=cpp
 *
 * [24] Swap Nodes in Pairs
 */
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

#include <iostream>
using namespace std;
// struct ListNode
// {
//   int val;
//   ListNode *next;
//   ListNode(int x) : val(x), next(NULL) {}
// };
class Solution
{
public:
  ListNode *swapPairs(ListNode *head)
  {
    ListNode *pre = nullptr, *next, *cur = head;
    if (head && head->next)
      head = head->next;
    while (cur && cur->next)
    {
      next = cur->next;
      cur->next = next->next;
      next->next = cur;
      if (pre)
        pre->next = next;
      pre = cur;
      cur = pre->next;
    }
    return head;
  }
};
