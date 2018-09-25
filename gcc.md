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