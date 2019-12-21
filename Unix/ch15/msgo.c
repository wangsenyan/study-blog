#include "apue.h"
#include <sys/msg.h>

#define KEY 888

struct mymesg
{
  long mtype;
  char mtext[100];
};
int main(void)
{
  int i, msgid;

  for (i = 0; i < 5; i++)
  {
    if ((msgid = msgget(KEY, IPC_CREAT | IPC_EXCL)) < 0)
      err_sys("msgget error");
    fprintf(stderr, "msgid %d\n", msgid);
    if (msgctl(msgid, IPC_RMID, NULL) < 0)
      err_sys("msgctl error");
  }
  for (i = 0; i < 5; i++)
  {
    if ((msgid = msgget(KEY, IPC_CREAT | IPC_PRIVATE)) < 0)
      err_sys("msgget error");
    fprintf(stderr, "msgid %d\n", msgid);
    struct mymesg mymsg;
    mymsg.mtype = 4;
    sprintf(mymsg.mtext, "%s", "hello world");
    if (msgsnd(msgid, (void *)&mymsg, strlen(mymsg.mtext), 0) < 0)
      err_sys("msgsnd error");
  }
  exit(0);
}