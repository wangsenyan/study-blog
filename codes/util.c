#include<stdio.h>
void showArray(double *p,int n){
   for(int i=0;i<n;i++)
   	 printf("%.f  ",*(p+i));
   return;
}