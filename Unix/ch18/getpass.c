#include "apue.h"
#include <signal.h>
#include <stdio.h>
#include <termios.h>

#define MAX_PASS_LEN 8
char *getpass(const char *prompt)
{
  static char buf[MAX_PASS_LEN + 1]; //密码最长 MAX_PASS_LEN
  char *ptr;
  sigset_t sig, osig;     //用于任务完成后恢复信号屏蔽字
  struct termios ts, ots; //用于任务完成后恢复终端配置
  FILE *fp;
  int c;
  if ((fp = fopen(ctermid(NULL), "r+")) == NULL) //打开终端
    return (NULL);
  setbuf(fp, NULL); //设置终端流不带缓冲
  sigemptyset(&sig);
  sigaddset(&sig, SIGINT);
  sigaddset(&sig, SIGTSTP);            //输入密码期间不能被中断停止
  sigprocmask(SIG_BLOCK, &sig, &osig); //设置屏蔽字

  tcgetattr(fileno(fp), &ts);
  ots = ts;
  ts.c_lflag &= ~(ECHO | ECHOE | ECHOK | ECHONL); //设置中断不回显
  tcsetattr(fileno(fp), TCSAFLUSH, &ts);
  fputs(prompt, fp); //输出提示

  //将输入保存在buf中
  ptr = buf;
  while ((c = getc(fp)) != EOF && c != '\n')
    if (ptr < &buf[MAX_PASS_LEN])
      *ptr++ = c;
  *ptr = 0;
  putc('\n', fp); //新的一行
  tcsetattr(fileno(fp), TCSAFLUSH, &ots);
  sigprocmask(SIG_SETMASK, &osig, NULL);
  fclose(fp);
  return (buf);
}

int main(void)
{
  char *ptr;
  if ((ptr = getpass("Enter password:")) == NULL)
    err_sys("getpass error");
  printf("password: %s\n", ptr);
  //如果是明文口令，为安全，程序完成后应在内存中清除它
  while (*ptr != 0)
    *ptr++ = 0;
  exit(0);
}