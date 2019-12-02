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
#include <syslog.h>
#include <fcntl.h>
#include <sys/resource.h>
#define MAXLINE 4096
#define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define DIR_MODE (FILE_MODE | S_IXUSR | S_IXGRP | S_IXOTH)
#define LOCKFILE "/var/run/deamon.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)
#define read_lock(fd, offset, whence, len) \
  lock_reg((fd), F_SETLK, F_RDLCK, (offset), (whence), (len))
#define readw_lock(fd, offset, whence, len) \
  lock_reg((fd), F_SETLKW, F_RDLCK, (offset), (whence), (len))
#define write_lock(fd, offset, whence, len) \
  lock_reg((fd), F_SETLK, F_WRLCK, (offset), (whence), (len))
#define writew_lock(fd, offset, whence, len) \
  lock_reg((fd), F_SETLKW, F_WRLCK, (offset), (whence), (len))
#define un_lock(fd, offset, whence, len) \
  lock_reg((fd), F_SETLK, F_UNLCK, (offset), (whence), (len))
#define is_read_lockable(fd, offset, whence, len) \
  lock_test((fd), F_RDLCK, (offset), (whence), (len))
#define is_write_lockable(fd, offset, whence, len) \
  lock_test((fd), F_WRLCK, (offset), (whence), (len))
// #define lockfile(fd) write_lock((fd), 0, SEEK_SET, 0)
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
void daemonize(const char *cmd);
int already_running(void);
int lockfile(int fd);
int set_cloexec(int fd);
void set_fl(int fd, int flags);
void clr_fl(int fd, int flags);
int lock_reg(int fd, int cmd, int type, off_t offset, int whence, off_t len);
int lock_test(int fd, int type, off_t offset, int whence, off_t len);
void TELL_WAIT(void);
void TELL_PARENT(pid_t pid);
void WAIT_PARENT(void);
void TELL_CHILD(pid_t pid);
void WAIT_CHILD(void);
//Sigfunc *signal(int signo, Sigfunc *func)
#endif