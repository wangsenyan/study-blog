## <center>终端I/O</center>

```c
#include <stdio.h>
char *ctermid(char *ptr);
//返回：成功，返回指向终端控制终端名的指针，出错，返回空指针
#include<unistd.h>
int isatty(int fd);//判断文件描述符是否引用一个终端设备
//返回：若未终端设备，返回1，否则，0
char *ttyname(int fd);
//返回：指向终端路径名的指针，若出错，返回NULL
```