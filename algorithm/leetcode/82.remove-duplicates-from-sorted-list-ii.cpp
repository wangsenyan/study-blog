/*
 * @lc app=leetcode id=82 lang=cpp
 *
 * [82] Remove Duplicates from Sorted List II
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
struct ListNode
{
  int val;
  ListNode *next;
  ListNode(int x) : val(x), next(NULL) {}
};
class Solution
{
public:
  ListNode *deleteDuplicates(ListNode *head)
  {
    ListNode *ptr = head;
    while (ptr && ptr->next)
    {
    }

    while (ptr && ptr->next)
      if (ptr->val == ptr->next->val)
        ptr = ptr->next;
      else
        break;

    while (ptr)
    {
      if (ptr->next && ptr->next->val == head->val)
        ptr->next = ptr->next->next;
      else
        ptr = ptr->next;
    }
    return head;
  }
};
