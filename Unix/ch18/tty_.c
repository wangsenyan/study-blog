#include "tty_.h"

static struct termios save_termios;
static int ttysavefd = -1;
static enum { RESET,
              RAW,
              CBREAK } ttystate = RESET;

int tty_cbreak(int fd)
{
  int err;
  struct termios buf;
  if (ttystate != RESET)
  {
    errno = EINVAL;
    return (-1);
  }
  if (tcgetattr(fd, &buf) < 0)
    return (-1);
  save_termios = buf;
  buf.c_lflag &= ~(ECHO | ICANON);

  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
    return (-1);

  if (tcgetattr(fd, &buf) < 0)
  {
    err = errno;
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = err;
    return (-1);
  }
  if ((buf.c_lflag & (ECHO | ICANON)) || buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0)
  {
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = EINVAL;
    return (-1);
  }
  ttystate = CBREAK;
  ttysavefd = fd;
  return (0);
}

int tty_raw(int fd)
{
  int err;
  struct termios buf;
  if (ttystate != RESET)
  {
    errno = EINVAL;
    fprintf(stderr, "1\n");
    return (-1);
  }
  if (tcgetattr(fd, &buf) < 0)
    return (-1);
  save_termios = buf;
  /*
  ECHO:启用回显
  ICANON:规范输入
  IEXTEN:使扩充的输入字符处理起作用
  ISIG:使终端产生的信号起作用
  */
  buf.c_lflag &= ~(ECHO | ICANON | IEXTEN | ISIG);
  /*
  BRKINT: 接到BREAK时产生SIGINT
  ICRNL: 将输入的CR 转换为 NL
  INPCK: 打开输入奇偶校验
  ISTRIP: 播出输入字符的第8位
  IXON: 使启用/禁用输出流控制起作用
  */
  buf.c_iflag &= ~(BRKINT | ICRNL | INPCK | ISTRIP | IXON);
  /*
  CSIZE:字符大小屏蔽字
  PARENB:启用奇偶校验
  CS8：8直接屏蔽字
  */
  buf.c_cflag &= ~(CSIZE | PARENB);
  buf.c_cflag |= CS8;
  /*
  OPOST:执行输出处理
  */
  buf.c_oflag &= ~(OPOST);
  buf.c_cc[VMIN] = 1;
  buf.c_cc[VTIME] = 0;
  if (tcsetattr(fd, TCSAFLUSH, &buf) < 0)
    return (-1);
  if (tcgetattr(fd, &buf) < 0)
  {
    err = errno;
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    errno = err;
    return (-1);
  }
  if ((buf.c_lflag & (ECHO | ICANON | IEXTEN | ISIG)) ||
      (buf.c_iflag & (BRKINT | ICRNL | INPCK | ISTRIP | IXON)) ||
      (buf.c_cflag & (CSIZE | PARENB | CS8)) != CS8 ||
      (buf.c_oflag & OPOST) ||
      buf.c_cc[VMIN] != 1 || buf.c_cc[VTIME] != 0)
  {
    tcsetattr(fd, TCSAFLUSH, &save_termios);
    fprintf(stderr, "2 %s\n", strerror(errno));
    errno = EINVAL;
    return (-1);
  }
  ttystate = RAW;
  ttysavefd = fd;
  return (0);
}
int tty_reset(int fd)
{
  if (ttystate == RESET)
    return (0);
  if (tcsetattr(fd, TCSAFLUSH, &save_termios) < 0)
    return (-1);
  ttystate = RESET;
  return (0);
}

void tty_atexit(void)
{
  if (ttysavefd >= 0)
    tty_reset(ttysavefd);
}
struct termios *tty_termios(void)
{
  return (&save_termios);
}
