/*
 * @lc app=leetcode id=83 lang=cpp
 *
 * [83] Remove Duplicates from Sorted List
 *
 * https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/
 *
 * algorithms
 * Easy (42.10%)
 * Total Accepted:    317.1K
 * Total Submissions: 749.9K
 * Testcase Example:  '[1,1,2]'
 *
 * Given a sorted linked list, delete all duplicates such that each element
 * appear only once.
 * 
 * Example 1:
 * 
 * 
 * Input: 1->1->2
 * Output: 1->2
 * 
 * 
 * Example 2:
 * 
 * 
 * Input: 1->1->2->3->3
 * Output: 1->2->3
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
// using namespace std;
// struct ListNode
// {
//   int val;
//   ListNode *next;
//   ListNode(int x) : val(x), next(NULL) {}
// };
class Solution
{
public:
  ListNode *deleteDuplicates(ListNode *head)
  {
    ListNode *curr = head;
    while (curr != nullptr && curr->next != nullptr)
    {
      if (curr->next->val == curr->val)
      {
        curr->next = curr->next->next;
      }
      else
      {
        curr = curr->next;
      }
    }
    return head;
  }
};
