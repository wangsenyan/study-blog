#ifndef _APUE_H
#define _APUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> //va_start
#include <errno.h>
#include <unistd.h> //read write
#include <sys/stat.h>
#include <signal.h>
#define MAXLINE 4096
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
char *path_alloc(size_t *);
void err_exit(int error, const char *fmt, ...);
void err_msg(const char *fmt, ...);
void err_quit(const char *fmt, ...);
void err_sys(const char *fmt, ...);
void err_ret(const char *fmt, ...);
void err_dump(const char *fmt, ...);
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);
#endif