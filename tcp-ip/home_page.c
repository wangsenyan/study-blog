#include "web.h"

void home_page(const char *host,const char *fname)
{
    int fd,n;
    char line[MAXLINE];
    fd = tcp_connect(host, SERV);
    n = snprintf(line, sizeof(line), GET_CMD, fname);
    writen(fd, line, n);
    for (;;)
    {
        if((n=read(fd,line,MAXLINE))==0)
            break;
        printf("read %d bytes of home page\n", n);
    }
    printf("end-of-file on home page\n");
    close(fd);
}