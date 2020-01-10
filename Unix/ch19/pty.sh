#!/bin/sh
./pty "${SHELL:-/bin/sh}" | tee typescript

# tee 在输出重定向的时候可以用tee命令将标准输出再拷贝一份输出