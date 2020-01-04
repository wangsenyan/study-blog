//linux版本，传递证书
#include "apue.h"
#include <sys/socket.h>
#define _GNU_SOURCE
#if defined(SCM_CREDS)
#define CREDSTRUCT cmsgcred
#define SCM_CREDTYPE SCM_CREDS
#elif defined(SCM_CREDENTIALS)
#define CREDSTRUCT ucred
#define SCM_CREDTYPE SCM_CREDENTIALS
#else
#error parsing credentials is unsupported!
#endif

#define RIGHTSLEN CMSG_LEN(sizeof(int))
#define CREDSLEN CMSG_LEN(sizeof(struct CREDSTRUCT))
#if defined(CONTROLLEN)
#undef CONTROLLEN
#define CONTROLLEN (RIGHTSLEN + CREDSLEN)
#endif
static struct cmsghdr *cmptr = NULL;

int send_fd(int fd, int fd_to_send)
{
  struct CREDSTRUCT *credp;
  struct cmsghdr *cmp;
  struct iovec iov[1];
  struct msghdr msg;
  char buf[2];

  iov[0].iov_base = buf;
  iov[0].iov_len = 2;
  msg.msg_iov = iov;
  msg.msg_iovlen = 1;
  msg.msg_name = NULL;
  msg.msg_namelen = 0;
  msg.msg_flags = 0;

  if (fd_to_send < 0)
  {
    msg.msg_control = NULL;
    msg.msg_controllen = 0;
    buf[1] = -fd_to_send;
    if (buf[1] == 0) // -256
      buf[1] = 1;
  }
  else
  {
    if (cmptr == NULL && (cmptr = malloc(CONTROLLEN)) == NULL)
      return (-1);
    msg.msg_control = cmptr;
    msg.msg_controllen = CONTROLLEN;
    cmp = cmptr;

    cmp->cmsg_level = SOL_SOCKET;
    cmp->cmsg_type = SCM_RIGHTS; //发送/接收描述符
    cmp->cmsg_len = RIGHTSLEN;
    *(int *)CMSG_DATA(cmp) = fd_to_send;
    cmp = CMSG_NXTHDR(&msg, cmp);
    cmp->cmsg_level = SOL_SOCKET;
    cmp->cmsg_type = SCM_CREDTYPE; //发送/接收用户凭证
    cmp->cmsg_len = CREDSLEN;
    credp = (struct CREDSTRUCT *)CMSG_DATA(cmp);
#if defined(SCM_CREDENTIALS)
    credp->uid = getuid();
    credp->gid = getgid();
    credp->pid = getpid();
#endif
    buf[1] = 0;
  }
  buf[0] = 0;
  if (sendmsg(fd, &msg, 0) != 2)
    return (-1);
  return (0);
}
