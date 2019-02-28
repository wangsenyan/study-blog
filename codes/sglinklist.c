#include <stdio.h>
#include <stdlib.h>
#include "sglinklist.h"
pNODE CreateSgLinkList(void)
{
  pNODE pTail = NULL;
  pNODE pHead = (pNODE)malloc(sizeof(NODE));
  if (NULL == pHead)
  {
    printf("内存分配失败!\n");
  }
  pHead->data = 0;
  pHead->next = NULL;
  pTail = pHead;
  return pHead;
}

void TraverseSgLinkList(pNODE pHead)
{
  pNODE pt = pHead->next;
  while (pt != NULL)
  {
    printf("%.2f ", pt->data);
    pt = pt->next;
  }
  printf('\n');
}

int IsEmptySgLinkList(pNODE pHead)
{
  if (pHead->next == NULL)
    return 1;
  else
    return 0;
}

int GetLengthSgLinkList(pNODE pHead)
{
  int length = 0;
  pNODE pt = pHead->next;
  while (pt != NULL)
  {
    length++;
    pt = pt->next;
  }
  return length;
}
int InsertEleSgLinkList(pNODE pHead, double data)
{
  pNODE pt = pHead->next, p_new = NULL;
  p_new = (pNODE)malloc(sizeof(NODE));
  if (NULL == pHead)
  {
    printf("内存分配失败!\n");
    return 0
  }
  p_new->next = NULL;
  p_new->data = data;
  while (pt != NULL)
    pt = pt->next;
  pt->next = p_new;
  return 1;
}
int DeleteEleSgLinkList(pNODE pHead, int pos)
{
}
void FreeMemory(pNODE *ppHead)
{
  pNODE pt = NULL;
  while (*ppHead != NULL)
  {
    pt = (*ppHead)->next;
    free(*ppHead);
    *ppHead = pt;
  }
}
