// 用链表实现可合并堆,最小堆
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct ListNodeType
{
  int key;
  int ord;
  struct ListNodeType *next;
  struct ListNodeType *pre;
} ListNode, *pListNode;

typedef struct
{
  pListNode head;
  pListNode tail;
  int len;
} Heap, *pHeap;

void makeHeap(pHeap *p)
{
  (*p) = (pHeap)malloc(sizeof(Heap));
  (*p)->head = (*p)->tail = NULL;
  (*p)->len = 0;
}

void swap(int *a, int *b)
{
  int temp = (*a);
  (*a) = (*b);
  (*b) = temp;
}

pListNode getNodeByOrd(pListNode start, int ord)
{
  pListNode p;
  if (ord == start->ord)
    return start;
  else if (ord < start->ord)
  {
    p = start->pre;
    while (p && p->ord != ord)
    {
      p = p->pre;
    }
    return p;
  }
  else
  {
    p = start->next;
    while (p && p->ord != ord)
    {
      p = p->next;
    }
    return p;
  }
}

void descreaseKey(pListNode n, int key)
{
  n->key = key;
  pListNode p = n, pp;
  while (1)
  {
    pp = getNodeByOrd(p, p->ord / 2);
    if (pp && pp->key > p->key)
    {
      swap(&(pp->key), &(p->key));
      p = pp;
    }
    else
    {
      break;
    }
  }
}

void insert(pHeap h, int key)
{
  if (h->head == NULL)
  {
    h->head = (pListNode)malloc(sizeof(ListNode));
    h->tail = h->head;
    h->head->key = key;
    h->head->ord = 1;
    h->head->pre = NULL;
    h->tail->next = NULL;
    h->len++;
  }
  else
  {
    pListNode newN = (pListNode)malloc(sizeof(ListNode));
    newN->key = INT_MAX;
    newN->ord = h->tail->ord + 1;
    h->tail->next = newN;
    newN->pre = h->tail;
    newN->next = NULL;
    h->tail = newN;
    h->len++;
    descreaseKey(newN, key);
  }
}

void heapMinify(pListNode n)
{
  pListNode left = getNodeByOrd(n, n->ord * 2);
  pListNode right = getNodeByOrd(n, n->ord * 2 + 1);
  int min = n->key;
  pListNode pMin = n;
  if (left && left->key < min)
  {
    min = left->key;
    pMin = left;
  }
  if (right && right->key < min)
  {
    min = right->key;
    pMin = right;
  }
  if (min == n->key)
    return;
  swap(&(n->key), &(pMin->key));
  heapMinify(pMin);
}

int extractMin(pHeap h)
{
  int x = h->head->key;
  if (h->len == 1)
  {
    h->len--;
    free(h->head);
    h->head = h->tail = NULL;
    return x;
  }
  else
  {
    pListNode tPre = h->tail->pre;
    int tKey = h->tail->key;
    free(h->tail);
    h->tail = tPre;
    h->tail->next = NULL;
    h->len--;
    h->head->key = tKey;
    heapMinify(h->head);
    return x;
  }
}

pHeap buildHeap(pListNode head)
{
  pHeap h;
  makeHeap(&h);
  if (head == NULL)
    return h;
  int len = 1;
  pListNode p = head, t = head->pre;
  while (p)
  {
    len++;
    p = p->next;
    if (p)
      t = p->pre;
  }
  h->len = len;
  h->head = head;
  h->tail = t;
  p = getNodeByOrd(head, len / 2);
  while (p)
  {
    heapMinify(p);
    p = p->pre;
  }
}

void printH(pHeap h)
{
  pListNode p = h->head;
  while (p)
  {
    printf("%d ", p->key);
    p = p->next;
  }
  printf("\n");
}

pHeap heapUnion(pHeap h1, pHeap h2)
{
  if (h1->len <= h2->len)
  {
    pListNode p = h1->head;
    while (p)
    {
      insert(h2, p->key);
      p = p->next;
    }
    return h2;
  }
  else
  {
    pListNode p = h2->head;
    while (p)
    {
      insert(h1, p->key);
      p = p->next;
    }
    return h1;
  }
}

void main()
{
  pHeap h1;
  makeHeap(&h1);
  insert(h1, 15);
  insert(h1, 30);
  insert(h1, 2);
  insert(h1, 60);
  insert(h1, 55);
  printH(h1);
  int x = extractMin(h1);
  printf("x=%d\n", x);
  printH(h1);
  pHeap h2;
  makeHeap(&h2);
  insert(h2, 66);
  insert(h2, 59);
  insert(h2, 6);
  insert(h2, 50);
  insert(h2, 67);
  printH(h2);
  pHeap h = heapUnion(h1, h2);
  printH(h);
  getchar();
}
