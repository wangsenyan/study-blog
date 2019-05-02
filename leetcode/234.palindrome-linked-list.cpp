/*
 * @lc app=leetcode id=234 lang=cpp
 *
 * [234] Palindrome Linked List
 *
 * https://leetcode.com/problems/palindrome-linked-list/description/
 *
 * algorithms
 * Easy (35.54%)
 * Total Accepted:    248.4K
 * Total Submissions: 694.4K
 * Testcase Example:  '[1,2]'
 *
 * Given a singly linked list, determine if it is a palindrome.
 * 
 * Example 1:
 * 
 * 
 * Input: 1->2
 * Output: false
 * 
 * Example 2:
 * 
 * 
 * Input: 1->2->2->1
 * Output: true
 * 
 * Follow up:
 * Could you do it in O(n) time and O(1) space?
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
#include <vector>
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
  bool isPalindrome(ListNode *head)
  {
    ListNode *fast = head;
    ListNode *slow = head;
    while (fast && fast->next)
    {
      slow = slow->next;
      fast = fast->next->next;
    }
    ListNode *p;
    if (fast)
    {
      slow = slow->next;
      p = reverseList(slow);
    }
    else
    {
      p = reverseList(slow);
    }
    while (head && p)
    {
      if (p->val != head->val)
        return false;
      head = head->next;
      p = p->next;
    }
    return true;
  }
  ListNode *reverseList(ListNode *head)
  {
    ListNode *h = 0, *next;
    while (head)
    {
      next = head->next;
      head->next = h;
      h = head;
      head = next;
    }
    return h;
  }
};
