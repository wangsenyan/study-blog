#define ElementType int
typedef struct pDtype
{
  int k;
} D, *pD;

ElementType DIRECT_ADDRESS_SEARCH(pD T, int k)
{
  return T[k];
}