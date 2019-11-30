#ifndef _APUE_H
#define _APUE_H
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h> //va_start
#include <errno.h>
#include <unistd.h> //read write
#include <sys/stat.h>
#include <sys/wait.h>
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
void err_cont(int error, const char *fmt, ...);
void err_dump(const char *fmt, ...);
static void err_doit(int errnoflag, int error, const char *fmt, va_list ap);
void pr_exit(int status);
void pr_ids(char *name);
typedef void Sigfunc(int);
Sigfunc *signal(int, Sigfunc *);
Sigfunc *signal_intr(int, Sigfunc *);
void pr_mask(const char *str);
int system(const char *cmdstring);
//Sigfunc *signal(int signo, Sigfunc *func)
#endif