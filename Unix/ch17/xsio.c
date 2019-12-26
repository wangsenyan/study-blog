#include "apue.h"
#include <sys/msg.h>
#define MAXMSZ 512

struct mymesg
{
  long mtype;
  char mtext[MAXMSZ];
};

int main(int argc, char *argv[])
{
  key_t key;
  long qid;
  size_t nbytes;
  struct mymesg m;
  if (argc != 3)
  {
    fprintf(stderr, "usage: sendmsg KEY message\n");
    exit(1);
  }

  //long int strtol (const char* str, char** endptr, int base);
  //endptr 指向第一个不可转换的字符位置的指针
  //base 转换成几进制的数
  key = strtol(argv[1], NULL, 0); //字符串转换成长整形
  if ((qid = msgget(key, 0)) < 0)
    err_sys("can't open queue key %s", argv[1]);
  memset(&m, 0, sizeof(m));
  strncpy(m.mtext, argv[2], MAXMSZ - 1);
  nbytes = strlen(m.mtext);
  m.mtype = 1;
  if (msgsnd(qid, &m, nbytes, 0) < 0)
    err_sys("can't send message");
  exit(0);
}