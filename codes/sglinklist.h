#ifndef _SINGLY_LINKED_LIST_H_H
#define _SINGLY_LINKED_LIST_H_H

typedef struct Node
{
  double data;
  struct Node *next;
} NODE, *pNODE;
pNODE CreateSgLinkList(void);
void TraverseSgLinkList(pNODE pHead);
int IsEmptySgLinkList(pNODE pHead);
int GetLengthSgLinkList(pNODE pHead);
int InsertEleSgLinkList(pNODE pHead, double data);
int DeleteEleSgLinkList(pNODE pHead, int pos);
void FreeMemory(pNODE *ppHead);

#endif