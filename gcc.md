```sh
$ g++ -E main.cpp -o main.i

$ g++ -S main.i -o main.s
$ g++ -S main.i -o main.debug.s --ggdb -g3

$ as main.s -o main.as.o
$ as main.debug.s -o main.as.debug.o

$ gcc -c #编译和汇编但不要链接
$ gcc -static -o prog2c main2.o -L. -lvector # -static 告诉编译器驱动程序，链接器应该构建一个完全链接的可执行目标文件，-lvector 是 libvector.a 的缩写，-L.参数告诉链接器在当前目录下查找libvector.a

$ gcc -shared -fpic -o libvector.so addvec.c multvec.c # -fpic指示编译器生成与位置无关的代码，-shared指示链接器创建一个共享的目标文件
```

### 处理目标文件的工具
* AR 创建静态库，插入、删除、列出和提取成员
* STRINGS 列出一个目标文件中所有可打印的字符串
* STRIP 从目标文件中删除符号表信息
* NM 列出一个目标文件的符号表中定义的符号
* SIZE 列出目标文件中节的名字和大小
* READELF 显示一个目标文件的完整结构，包括ELF头中的所有信息。
* OBJDUMP 所有二进制工具之母。能够显示一个目标文件中的所有的信息。最大作用是反汇编.text节中的二进制指令
* LDD 列出一个可执行文件在运行时所需的共享库