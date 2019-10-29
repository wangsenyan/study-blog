## <center> 标准I/O库 </center>

* restrict  
  类型限定符，告诉编译器，对象已经被指针所引用，不能通过除改指针外所有其他直接或间接的方式修改对象的内容

```c
#include <stdio.h>
void setbuf(FILE *restrict fp,char *restrict buf);
void setvbuf(FILE *restrict fp,char *restrict buf,int mode,size_t size);
//返回：若成功，返回0，若出错，返回非0
int fflush(FILE *fp)
//返回：若成功，返回0，若出错，返回EOF
//使该流所有未写的数据都被传送至内核
```
![setbuf](../../image/setbuf.png)

### 打开流

```c
#include <stdio.h>
FIFE *fopen(const char *restrict pathname,const char *restrict type);
FILE *freopen(const char *restrict pathname,const char *restrict type,FILE *restrict fp);
FILE *fdopen(int fd,const char *type);
//返回：若成功， 返回文件指针，出错，返回null
fclose(FILE *fp); 
//返回：若成功，返回0，出错，返回EOF
```

![io_type](../../image/io_type.png)
![io_type_six](../../image/io_type_six.png)

* 当一个进程正常终止时，所有带未写缓冲数据的标准I/O流都被冲洗，所有打开的标准I/O流都被关闭

### 读和写流
* 非格式化I/O
  - 每次一个字符的I/O
  - 每次一行的I/O，fgets fputs
  - 直接I/O,fread fwrite  二进制I/O，一次一个对象I/O、面向记录的I/O或面向结构的I/O

```c
#include <stdio.h>
//输入函数
int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void); //getc(stdin)
//返回：若成功，返回下一个字符，若已到达文件尾端或出错，返回EOF

int ferror(FILE *fp);
int feof(FILE *fp);
//返回：条件为真，返回非0，否则返回0(假)
void clearerr(FILE *fp);
//清除 出错标志 和 文件结束标志

int ungetc(int c,FILE *fp);
//返回：成功，返回c，出错，返回EOF
//将字符压送回流中，相当于栈，只是写会标准I/O库的流缓冲区中

//输出函数
int putc(int c,FILE *fp);
int fputc(int c,FILE *fp);
int putchar(int c);// putc(c,stdout)
//返回：成功 0 ，出错 EOF


//每次一行I/O
//输入
char *fgets(char *restrict buf,int n,FILE *restrict fp);
char *gets(char *buf);
//返回：成功，返回buf, 文件尾或出错，NULL
```

* getc 可被实现为宏，而fgetc不能实现为宏
* 为区分出错还是到达文件尾端，必须调用 ferror或feof
* 压送不能是EOF，但已到达文件尾端，仍可以会送一个字符
  一次成功的ungetc调用会清除改流的文件结束标志

* fgets 一直读到换行符为止，但是不超过n-1个字符  
  该缓冲区以null字节结尾（换行符--> null）
* gets并不将换行符存入缓冲区，而fgets会