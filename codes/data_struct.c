#include <stdlib.h>
#include <stdio.h>
#define ElementType int
#define MAXSIZE 100
typedef struct
{
  int head;
  int tail;
  int size;
  ElementType data[MAXSIZE];
} Queue;
typedef struct LIST
{
  ElementType key;
  struct LIST *prev;
  struct LIST *next;
} List, *LinkList;
typedef struct LISTNP
{
  ElementType key;
  int np;
} LISPnp, *LISTLINKnp;
typedef struct
{
  List *nil;
} ListHead, *LinkListHead;
typedef struct
{
  LISPnp *nil;
} ListNpHead, *LinkListNpHead;

Queue *CreateQueue();
void enqueue(Queue *q, ElementType item);
ElementType dequeue(Queue *q);
void showQueue(Queue *q);
LinkListHead initList();
LinkList LIST_SEARCH(LinkListHead L, ElementType k);
void showList(LinkListHead L);
void LIST_INSERT(LinkListHead L, ElementType k);
ElementType LIST_DELETE(LinkListHead L, LinkList x);
LinkListNpHead initListNp();
void ShowListNp(LinkListNpHead L);
int main()
{
  // LinkListHead p = initList();
  // LinkList l = LIST_SEARCH(p, 5);
  // LIST_INSERT(p, 12);
  // ElementType x = LIST_DELETE(p, l);
  // showList(p);
  LinkListNpHead p = initListNp();
  ShowListNp(p);
  return 0;
}
Queue *CreateQueue()
{
  Queue *q = (Queue *)malloc(sizeof(Queue));
  if (!q)
  {
    printf("空间不足!");
    return NULL;
  }
  q->head = 0;
  q->tail = 0;
  q->size = 0;
};
int isFullQueue(Queue *q)
{
  return (q->size == MAXSIZE);
};
int isEmptyQueue(Queue *q)
{
  return (q->size == 0);
}
void enqueue(Queue *q, ElementType item)
{
  if (q->head == q->tail + 1)
  {
    printf("队列已满");
    return;
  }
  q->data[q->tail] = item;
  if (q->tail == MAXSIZE - 1)
    q->tail = 0;
  else
    q->tail = q->tail + 1;
};
ElementType dequeue(Queue *q)
{
  if (q->head == q->tail)
  {
    printf("队列为空");
    return -1;
  }
  ElementType x = q->data[q->head];
  if (q->head == MAXSIZE - 1)
    q->head = 0;
  else
    q->head = q->head + 1;
  return x;
}
void showQueue(Queue *q)
{
  for (int i = q->head; i < q->tail; i++)
    printf("%d ", q->data[i]);
  printf("\n");
}

LinkListHead initList()
{
  ListHead *L;
  L = (ListHead *)malloc(sizeof(ListHead));
  if (L == NULL)
  {
    printf("申请内存失败");
    return NULL;
  }
  List *nil = (List *)malloc(sizeof(List));
  if (nil == NULL)
  {
    printf("申请内存失败");
    return NULL;
  }
  nil->next = nil;
  nil->prev = nil;
  nil->key = -1;
  L->nil = nil;
  ElementType x;
  while (scanf("%d", &x) != EOF)
  {
    List *p;
    p = (List *)malloc(sizeof(List));
    p->key = x;
    p->next = L->nil->next;
    p->prev = L->nil;
    L->nil->next->prev = p;
    L->nil->next = p;
  }
  return L;
}

LinkList LIST_SEARCH(LinkListHead L, ElementType k)
{
  LinkList x = L->nil->next;
  L->nil->key = k;
  while (x->key != k)
  {
    x = x->next;
  }
  L->nil->key = -1;
  return x;
}

void LIST_INSERT(LinkListHead L, ElementType k)
{
  List *p = (List *)malloc(sizeof(List));
  if (p == NULL)
  {
    printf("申请内存失败");
    return;
  }
  p->key = k;
  p->next = L->nil->next;
  p->prev = L->nil;
  L->nil->next->prev = p;
  L->nil->next = p;
  return;
}

ElementType LIST_DELETE(LinkListHead L, LinkList x)
{
  ElementType k = x->key;
  if (L->nil == x)
  {
    printf("链表为空");
    return -1;
  }
  x->next->prev = x->prev;
  x->prev->next = x->next;
  return k;
}
void showList(LinkListHead L)
{
  LinkList p = L->nil->next;
  while (p->key != -1)
  {
    printf("%d ", p->key);
    p = p->next;
  }
}

LinkListNpHead initListNp()
{
  ListNpHead *L;
  L = (ListNpHead *)malloc(sizeof(ListNpHead));
  if (L == NULL)
  {
    printf("申请内存失败");
    return NULL;
  }
  LISPnp *nil = (LISPnp *)malloc(sizeof(LISPnp));
  if (nil == NULL)
  {
    printf("申请内存失败");
    return NULL;
  }
  nil->np = 0 ^ 0;
  nil->key = -1;
  L->nil = nil;
  ElementType x;
  while (scanf("%d", &x) != EOF)
  {
    LISPnp *p;
    p = (LISPnp *)malloc(sizeof(LISPnp));
    p->key = x;
    LISPnp *next = (LISPnp *)(L->nil->np ^ 0);
    p->np = (int)(L->nil) ^ (int)next;
    L->nil->np = (int)p ^ 0;
    if (next != NULL)
    {
      next->np = (int)p ^ (next->np ^ (int)L->nil);
    }
  }
  return L;
}
void ShowListNp(LinkListNpHead L)
{
  LISTLINKnp frout = (LISTLINKnp)0;
  LISTLINKnp current = L->nil;
  LISTLINKnp next = (LISTLINKnp)(current->np ^ (int)frout);
  while (next->key != -1)
  {

    printf("%d ", next->key);
    frout = current;
    current = next;
    next = (LISTLINKnp)(current->np ^ (int)frout);
  }
  return;
}