/*
 * @lc app=leetcode id=61 lang=cpp
 *
 * [61] Rotate List
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
  ListNode *rotateRight(ListNode *head, int k)
  {
    if (!head)
      return nullptr;
    ListNode *cur = head;
    int n = 0;
    while (cur)
    {
      n++;
      if (!cur->next)
      {
        cur->next = head;
        break;
      }
      cur = cur->next;
    }
    k = n - k % n;
    while (k > 0)
    {
      cur = cur->next;
      k--;
    }
    head = cur->next;
    cur->next = nullptr;
    return head;
  }
};
