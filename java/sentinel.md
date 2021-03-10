1. [同一个宿主机器上容器间相互访问No route to host](https://blog.csdn.net/QingKong999/article/details/79750383?utm_medium=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.control&dist_request_id=1328626.10481.16153670795892929&depth_1-utm_source=distribute.pc_relevant.none-task-blog-BlogCommendFromMachineLearnPai2-1.control)

2. 不同的宿主,使用 `Dcsp.sentinel.api.port=xxxx` jvm参数
   propeties: `sentinel.transport.clientIp=xxxx` 外网可访问

3. 开启防火墙，安全组