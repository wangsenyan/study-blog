#include <stdio.h>
#include "matrix.h"
#include <stdlib.h>
//#include <limits.h>
#include <float.h>
int **matrix(int rows, int cols)
{
  int **p1 = (int **)malloc(sizeof(int *) * rows);
  for (int i = 0; i < rows; i++)
    p1[i] = (int *)malloc(sizeof(int) * cols);
  return p1;
}
//void intial_matrix(int **m, int rows,int cols)
//{
//  for (int i = 0; i < rows; i++)
//    for (int j = 0; j < cols; j++)
//      *(*(m+i)+j)=(rand() % 100);
//}
void intial_matrix(int**m, int rows, int cols) {
    for (int rowi = 0; rowi < rows; rowi++) {
        int *row = m[rowi];
        for (int coli = 0; coli < cols; coli++) {
            row[coli] = rand() % 100;
        }
    }
}
void show_matrix(int **p, int rows,int cols)
{
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++)
      printf("%d\t", *(*(p+i)+j));
    printf("\n");
  }
}

void free_matrix(int **p, int rows,int cols)
{
  for (int i = 0; i < rows; i++)
  {
    printf("i am rush");
    free((void *)p[i]);
  }
  free((void *)p);
}

int main()
{
	//int **p;
	int **p=matrix(4,5);
    intial_matrix(p,4,5);
	show_matrix(p,4,5);
	free_matrix(p,4,5);
	return 0;
	
}
