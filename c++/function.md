### 函数
* 下面中，finger和\*ps都是const，而\*finger和ps不是
```cpp
int sloth=3;
const int *ps =&sloth;
int * const finger=&sloat;
```
* 二维数组
```cpp
int a[][5];
int (*a)[5];
```
* 字符串
返回字符串地址来引用字符串
```cpp
char *ps=buildstr(ch,times);
```
* 默认情况下C++按值传递参数

* 函数指针
 - 获取函数的地址 -- 函数名
 - 声明一个函数指针
 - 使用函数指针来调用函数

```cpp
double pam(int)
double (*pf)(int);
pf=pam //将函数地址赋给它
*pf(int) //返回指针的函数

double x=pam(4);
double y=(*pf)(5);
double z=pf(6);
const double * (*pf)(const double*,int)
*(*pf)(av,3)

const double *(*pa[3])(const double *,int)={f1,f2,f3}
const double * px=pa[0](av,3);
const double * py= (*pa[1])(av,3);
const double x=*pa[0](av,3);
const double y= *(*pa[1])(av,3);

const double *(*(*pd)[3])(const double *,int)=&pa;
(*pd)[i](av,3) (*(*pd)[i])(av,3);
*(*pd)[i](av,3) *(*(*pd)[i])(av,3);
```
指针从内到外

```cpp
typedef const double *(*p_fun)(const double*,int);
p_fun pa[3]={f1,f2,f3};
p_fun (*pd)[3]=&pa;
```
* 参数声明
当且仅当声明函数的形参时，下面两个声明才是等价，当做参数时不会传递长度信息
```cpp
typeName arr[]
type * arr;
```