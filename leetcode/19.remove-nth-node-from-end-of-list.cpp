/*
 * @lc app=leetcode id=19 lang=cpp
 *
 * [19] Remove Nth Node From End of List
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
  ListNode *removeNthFromEnd(ListNode *head, int n)
  {
    ListNode *fast = head, *slow = head;
    for (int i = 0; i < n; i++)
    {
      fast = fast->next;
    }
    if (!fast)
      return slow->next;
    while (fast->next)
    {
      slow = slow->next;
      fast = fast->next;
    }
    slow->next = slow->next->next;
    return head;
  }
};
