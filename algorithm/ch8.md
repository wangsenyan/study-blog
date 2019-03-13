## <center>线性时间排序</center>

### 桶排序
* 性质
假设输入是独立、均匀分布在[0,1)区间

所有桶的大小的平方和与总的元素树呈线性关系
* BUCKED-SORT(A)
```
BUCKED-SORT(A)
   n=A.length
   let B[0...n-1] be a new array
   for i=0 to n-1
     make B[i] an empty list
   for i=1 to n
     insert A[i] into list B[nA[i]]
   for i=0 to n-1
     sort list B[i] with insetion sort
   concatenate the list B[0],B[1],....B[n-1] together in order
``` 