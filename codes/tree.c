#include <stdlib.h>
#include <stdio.h>
#define ElementType int
#define MAXSIZE 100
typedef struct MUTILIST
{
  int freeI;
  int L;
  int next[MAXSIZE];
  ElementType key[MAXSIZE];
  int prev[MAXSIZE];
} MutiList, *MutiLinkList;

typedef struct TREE
{
  struct TREE *p;
  struct TREE *lchild;
  struct TREE *rchild;
  ElementType key;
} tree, *treeLink;
typedef struct TREEHEAD
{
  tree *head;
} treeHead, *treeLinkHead;
typedef struct STACK
{
  int top;
  tree *data[MAXSIZE];
} Stacks, *StackLinks;
void TraversingTreeLoop(treeLink T);
void TraversingTreeAhead(treeLink T);
treeLink CreateBTree(treeLink P);
StackLinks InitStack();
void push(StackLinks S, treeLink T);
treeLink pop(StackLinks S);
MutiLinkList initMList();
void ShowMList(MutiLinkList ML);
int Allocate_Object(MutiLinkList ML);
void Free_Object(MutiLinkList ML, int x);
void Set_Key(MutiLinkList ML, int x, ElementType k);
void INORDER_PRINT(treeLink T);
void FreeTreeAhead(treeLink T);
void TraversingTreeMedium(treeLink T);
void TraversingTreeAfter(treeLink T);
treeLink BinarySearchTree(treeLink P);
treeLink TreeSearch(treeLink T, int k);
int main()
{
  // MutiLinkList ml = initMList();
  // ShowMList(ml);
  // int index = Allocate_Object(ml);
  // Set_Key(ml, index, 888);
  // ShowMList(ml);
  treeLink T = BinarySearchTree(NULL);
  TraversingTreeAfter(T);
  printf("\n");
  TraversingTreeMedium(T);
  printf("\n");
  TraversingTreeAhead(T);
  printf("\n");
  INORDER_PRINT(T);
  FreeTreeAhead(T);

  //TraversingTreeLoop(T);
  return 0;
}

void TraversingTreeLoop(treeLink T)
{
  StackLinks S = InitStack();
  push(S, T);
  while (S->top > 0)
  {
    treeLink U = pop(S);
    if (U != NULL)
    {
      printf("%d ", U->key);
      push(S, U->lchild);
      push(S, U->rchild);
    }
  }
}
void TraversingTreeAhead(treeLink T)
{
  if (T != NULL)
  {
    treeLink p = T;
    printf("%d ", p->key);
    TraversingTreeAhead(p->lchild);
    TraversingTreeAhead(p->rchild);
  }
}
void TraversingTreeMedium(treeLink T)
{
  if (T != NULL)
  {
    TraversingTreeMedium(T->lchild);
    printf("%d ", T->key);
    TraversingTreeMedium(T->rchild);
  }
}
void TraversingTreeAfter(treeLink T)
{
  if (T != NULL)
  {
    TraversingTreeAfter(T->lchild);
    TraversingTreeAfter(T->rchild);
    printf("%d ", T->key);
  }
}
treeLink CreateBTree(treeLink P)
{
  ElementType x;
  treeLink T;
  scanf("%d", &x);
  if (x != -1)
  {
    T = (tree *)malloc(sizeof(tree));
    if (T == NULL)
    {
      printf("no memory");
      return NULL;
    }
    T->key = x;
    T->p = P;
    T->lchild = CreateBTree(T);
    T->rchild = CreateBTree(T);
  }
  else
  {
    return NULL;
  }
  // return T;
}

treeLink TreeSearch(treeLink T, int k)
{
  if (T == NULL || k == T->key)
    return T;
  if (k < T->key)
    return TreeSearch(T->lchild, k);
  else
    return TreeSearch(T->rchild, k);
}

treeLink IterativeTreeSearch(treeLink T, int k)
{
  treeLink p = T;
  while (p != NULL && k != p->key)
  {
    if (k < p->key)
      p = p->lchild;
    else
      p = p->rchild;
  }
  return p;
}

treeLink TreeMininum(treeLink T)
{
  treeLink p = T;
  while (p->lchild != NULL)
  {
    p = p->lchild;
  }
  return p;
}
//二叉搜索最小节点递归
treeLink ITreeMininum(treeLink T)
{

  if (T->lchild != NULL)
    return ITreeMininum(T->lchild);
  else
    return T;
}
treeLink TreeMaximum(treeLink T)
{
  treeLink p = T;
  while (p->rchild != NULL)
  {
    p = p->rchild;
  }
  return p;
}
//二叉搜索最大节点递归
treeLink ITreeMaximum(treeLink T)
{
  if (T->rchild != NULL)
    return ITreeMaximum(T->rchild);
  else
    return T;
}
treeLink treeSuccessor(treeLink T)
{
  treeLink x = T;
  if (x->rchild != NULL)
    return TreeMininum(x->rchild);
  treeLink y = x->p;
  while (y != NULL && x == y->rchild)
  {
    x = y;
    y = y->p;
  }
  return y;
}

treeLink treePredecessor(treeLink T)
{
  treeLink x = T;
  if (x->lchild != NULL)
    return TreeMaximum(x->lchild);
  treeLink y = x->p;
  while (y != NULL && x == y->lchild)
  {
    x = y;
    y = y->p;
  }
  return y;
}
treeLink BinarySearchTree(treeLink P)
{
  ElementType x;
  treeLink T;
  scanf("%d", &x);
  while (x != -1)
  {
    T = (tree *)malloc(sizeof(tree));
    if (T == NULL)
    {
      printf("no memory");
      return NULL;
    }
    T->key = x;
    if (P == NULL)
    {
      T->p = NULL;
      P = T;
    }
    else
    {
      treeLink p = TreeSearch(P, x);
      if (p->key == x)
      {
        printf("重复");
      }
      else
      {
        T->p = TreeSearch(P, x);
      }
    }
    scanf("%d", &x);
  }

  if (x != -1)
  {
    T = (tree *)malloc(sizeof(tree));
    if (T == NULL)
    {
      printf("no memory");
      return NULL;
    }
    T->key = x;
  }
}
StackLinks InitStack()
{
  Stacks *S = (Stacks *)malloc(sizeof(Stacks));
  if (S)
  {
    S->top = 0;
  }
  return S;
}

void push(StackLinks S, treeLink T)
{
  if (S->top == MAXSIZE - 1)
  {
    printf("栈满");
    return;
  }
  S->data[S->top] = T;
  S->top++;
}

treeLink pop(StackLinks S)
{
  if (S->top <= 0)
  {
    printf("栈空");
    return NULL;
  }
  treeLink x = S->data[S->top];
  S->top--;
  return x;
}

MutiLinkList initMList()
{
  MutiList *ML = (MutiList *)malloc(sizeof(MutiList));
  ML->freeI = 0;
  ML->L = 0;
  for (int i = 0; i < MAXSIZE; i++)
  {
    ML->prev[i] = i - 1;
    ML->next[i] = i + 1;
    ML->key[i] = 0;
  }
  ML->next[MAXSIZE - 1] = -1;
  return ML;
}

void ShowMList(MutiLinkList ML)
{
  printf("the free list is %d\n", ML->freeI);
  printf("the used list is %d\n", ML->L);
  for (int i = 0; i < MAXSIZE; i++)
    printf("%d %d %d \n", ML->prev[i], ML->key[i], ML->next[i]);
}

int Allocate_Object(MutiLinkList ML)
{
  if (ML->freeI == -1)
  {
    return -1;
  }
  else
  {
    int x = ML->freeI;
    ML->freeI = ML->next[x];
    return x;
  }
}
void Free_Object(MutiLinkList ML, int x)
{
  ML->next[ML->prev[x]] = ML->next[x];
  ML->prev[ML->next[x]] = ML->prev[x];
  ML->next[x] = ML->freeI;
  ML->freeI = x;
}
void Set_Key(MutiLinkList ML, int x, ElementType k)
{
  ML->key[x] = k;
}

MutiLinkList Compactify_list(MutiLinkList ML, int F, int L)
{
  ElementType temp[MAXSIZE];
  int l = ML->L;
  int i = 0;
  while (ML->next[l] != -1)
  {
    temp[i] = ML->key[l];
    L = ML->next[l];
    i++;
  }
  temp[i] = ML->key[l];
  for (int i = 0; i <= i; i++)
  {
    ML->prev[i] = i - 1;
    ML->next[i] = i + 1;
    ML->key[i] = temp[i];
  }
  ML->next[i - 1] = -1;
  ML->freeI = i + 1;
  ML->L = 0;
  return ML;
}

void INORDER_PRINT(treeLink T)
{
  treeLink prev = T;
  treeLink cur = T->lchild;
  treeLink next = NULL;
  while (cur != NULL)
  {
    if (prev == cur->p)
    {
      next = cur->lchild;
      if (next == NULL)
      {
        printf("%d ", cur->key);
        next = cur->rchild;
        if (next == NULL)
        {
          next = cur->p;
        }
      }
    }
    else
    {
      if (prev == cur->lchild)
      {
        printf("%d ", cur->key);
        next = cur->rchild;
        if (next == NULL)
        {
          next = cur->p;
        }
      }
      else
      {
        next = cur->p;
      }
    }
    prev = cur;
    cur = next;
  }
}
void FreeTreeAhead(treeLink T)
{
  if (T != NULL)
  {
    treeLink p = T;
    FreeTreeAhead(p->lchild);
    FreeTreeAhead(p->rchild);
    free(p);
    p = NULL;
  }
}