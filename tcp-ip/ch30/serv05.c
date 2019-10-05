//make 
//gcc serv05.c util.c sock_ntop.c child05.c web_child.c pr_cpu_time.c -o serv05 
#include "util.h"
#include "child.h"

static int nchildren;

int main(int argc,char **argv){
    int listenfd, i, navail, maxfd, nsel, connfd, rc;
    void sig_int(int);
    pid_t child_make(int, int, int);
    ssize_t n;
    fd_set rset, masterset;
    socklen_t addrlen, clilen;
    struct sockaddr *cliaddr;

    if(argc ==3)
        listenfd = tcp_listen(NULL, argv[1], &addrlen);
    else if(argc==4)
        listenfd = tcp_listen(argv[1], argv[2], &addrlen);
    else
        err_quit("usage:serv05 [<host>] <port#> <#children>");

    FD_ZERO(&masterset);
    FD_SET(listenfd, &masterset);
    maxfd = listenfd;
    cliaddr = malloc(addrlen);

    nchildren = atoi(argv[argc - 1]);
    navail = nchildren;
    cptr = calloc(nchildren, sizeof(Child));

    for (i = 0; i < nchildren;i++)
    {
        child_make(i, listenfd, addrlen);
        FD_SET(cptr[i].child_pipefd, &masterset);
        maxfd = MAX(maxfd, cptr[i].child_pipefd);
    }

    signal(SIGINT, sig_int);
    for (;;)
    {
        rset = masterset;
        //如果没有可用的进程，停止listen
        if(navail<=0)
            FD_CLR(listenfd, &rset); 
        //nsel 可读的描述符
        nsel = select(maxfd + 1, &rset,NULL,NULL,NULL);
        //有新的连接
        if(FD_ISSET(listenfd,&rset))
        {
            clilen = addrlen;
            connfd = accept(listenfd, cliaddr, &clilen);
            //判断服务器是否有进程可用
            for (i = 0; i < nchildren;i++)
               if(cptr[i].child_status==0)
                   break;
            if(i==nchildren)
                err_quit("no avaliable children");
            cptr[i].child_status = 1;
            cptr[i].child_count++;
            navail--;
            //向管道发送1字节并关闭
            n = write_fd(cptr[i].child_pipefd, "", 1, connfd);
            close(connfd);
            //特殊情况，没有可用描述符
            if(--nsel ==0)
                continue;
        }
        //遍历已经可读的套接字
        for (i = 0; i < nchildren;i++)
        {
            if(FD_ISSET(cptr[i].child_pipefd,&rset)){
               if((n=read(cptr[i].child_pipefd,&rc,1))==0)
                   err_quit("child %d terminated unexpectedly", i);
                cptr[i].child_status = 0;
                navail++;
                if(--nsel==0)
                    break;
            }
        }
    }
}