/*
 * @lc app=leetcode id=203 lang=cpp
 *
 * [203] Remove Linked List Elements
 *
 * https://leetcode.com/problems/remove-linked-list-elements/description/
 *
 * algorithms
 * Easy (35.44%)
 * Total Accepted:    218K
 * Total Submissions: 612.2K
 * Testcase Example:  '[1,2,6,3,4,5,6]\n6'
 *
 * Remove all elements from a linked list of integers that have value val.
 * 
 * Example:
 * 
 * 
 * Input:  1->2->6->3->4->5->6, val = 6
 * Output: 1->2->3->4->5
 * 
 * 
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
  ListNode *removeElements(ListNode *head, int val)
  {
    ListNode *ph = head;
    ListNode *pre = head;
    while (ph && ph->val == val)
    {
      ph = ph->next;
    }
    pre = ph;
    if (pre)
    {
      head = pre->next;
      while (head)
      {
        if (head->val != val)
        {
          pre = pre->next;
          head = head->next;
        }
        else
        {
          pre->next = head->next;
          head = head->next;
        }
      }
    }
    return ph;
  }
};
