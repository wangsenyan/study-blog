#include <stdio.h>
#include <stdlib.h>
#define ElementType int
typedef struct INTER
{
  ElementType low;
  ElementType high;
} inter, *interLink;
typedef struct ITREE
{
  ElementType max;
  struct ITREE *p;
  struct ITREE *left;
  struct ITREE *right;
  interLink inters;
} iTree, *iTreeLink;
typedef struct IHEAD
{
  iTreeLink root;
  iTreeLink tail;
  iTreeLink nil;
} iHead, *iHeadLink;

iTreeLink INTERVAL_TREE(iHeadLink T, interLink i)
{
  iTreeLink x = T->root;
  while (x != T->nil && (x->inters->high < i->low || x->inters->low > i->high))
  {
    if (x->inters->high > i->low)
      x = x->left;
    else
      x = x->right;
  }
  //找出重叠的最小低端点
  iTreeLink y = x->left;
  while (y != T->nil && (y->inters->high > i->low && y->inters->low < i->high))
  {
    x = y;
    y = x->left;
  }
  return x;
}
//找出所有重叠的
iTreeLink INTERVAL_TREE(iTreeLink x, interLink i)
{

  if (x != NULL && x->inters->high > i->low && x->inters->low < i->high)
  {
    printf("%p", x);
  }
  if (x->left != NULL && x->left->max >= i->low)
  {
    INTERVAL_TREE(x->left, i);
  }
  if (x->right != NULL && x->right->max >= i->low && x->right->inters->low <= i->high)
  {
    INTERVAL_TREE(x->right, i);
  }
}

iTreeLink INTERVAL_TREE(iTreeLink x, interLink i)
{
  if (x != NULL && x->inters->high == i->high && x->inters->low == i->low)
    printf("%p", x);
  if (x->left != NULL && x->left->max >= i->high && x->left->inters->low >= i->low)
    INTERVAL_TREE(x->left, i);
  if (x->right != NULL && x->right->max >= i->high && x->right->inters->low <= i->low)
    INTERVAL_TREE(x->right, i);
}