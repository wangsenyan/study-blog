## <center>高级进程间通信</center>

* unix域套接字
 - 仅仅复制数据
 - 并不执行协议处理
 - 不需要添加或删除网络报头
 - 无需计算校验和
 - 不要产生顺序号
 - 无需发送确认报文

![socketpair](../../image/socketpair.png)