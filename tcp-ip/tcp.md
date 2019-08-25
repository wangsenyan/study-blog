## 鸟哥私房菜 笔记
### 路由器命令
```sh
# 更改history文件
vim ~/.bash_history
# -n 将主机名以IP的方式显示
[root@www ~]# route -n 

Kernel IP routing table
Destination     Gateway         Genmask         Flags Metric Ref    Use Iface
192.168.13.0    0.0.0.0         255.255.255.0   U     0      0        0 eth0
169.254.0.0     0.0.0.0         255.255.0.0     U     1002   0        0 eth0
172.17.0.0      0.0.0.0         255.255.0.0     U     0      0        0 docker0
0.0.0.0         192.168.13.1    0.0.0.0         UG    0      0        0 eth0
You have mail in /var/spool/mail/root

# Destination : network
# Gateway     : 若为0:0:0:0 表示不需要额外的IP
# Flags       : 表示该网域或主机代表的意思
#               U:代表路由可用
#               G:代表该网域需要经由Gateway来帮忙传递
#               H:代表该行路由为一步主机，而非一整个网域
# Iface       : 就是Interface接口的意思
```    
```sh
#获得ip/mac对应的arp表
#在linux环境下
[root@www ~]# arp -[nd] hostname
[root@www ~]# arp -s hostname(IP) Hardware_address
选项与参数：
-n ：将主机名以 IP 的型态显示
-d ：将 hostname 的 hardware_address 由 ARP table 当中删除掉
-s ：设定某个 IP 或 hostname 的 MAC 到 ARP table 当中

[root@www ~]# arp -n

[root@www ~]# arp -n
Address HWtype HWaddress Flags Mask Iface
192.168.1.100 ether 00:01:03:01:02:03 C eth0
192.168.1.240 ether 00:01:03:01:DE:0A C eth0
192.168.1.254 ether 00:01:03:55:74:AB C eth0

#范例二：将 192.168.1.100 那部主机的网卡卡号直接写入 ARP 表格中
[root@www ~]# arp -s 192.168.1.100 01:00:2D:23:A1:0E
# 这个指令的目的在建立静态 ARP
```
* ping 和 traceroute 利用ICMP检验网络状态
### 常见端口

|端口|功能
|--|--
|20 |FTP-data，文件传输协议所使用的主动数据传输端口
|21 |FTP，文件传输协议的命令通道
|22 |SSH，较为安全的远程联机服务器
|23 |Telnet，早期的远程联机服务器软件
|25 |SMTP，简单邮件传递协议，用在作为 mail server 的埠口
|53 |DNS，用在作为名称解析的领域名服务器
|80 |WWW，这个重要吧！就是全球信息网服务器
|110| POP3，邮件收信协议，办公室用的收信软件都是透过他
|443| https，有安全加密机制的WWW服务器

### 
 将防火墙、路由器等设备归类为主机，因为这些组件内部一定会含有一个网卡
 * 跳线 - 跳线实际就是连接电路板（PCB）两需求点的金属连接线，因产品设计不同，其跳线使用材料，粗细都不一样。大部分跳线是用于同等电势电压传输，也有用于保护电路的参考电压，对于有精密电压要求的，一点点的金属跳线所产生的压降也会使产品性能产生很大影响。
 * 并行线


 * DNS 即使用TCP又使用UDP，
   - 域名解析时使用UDP协议
   - 区域传送时使用TCP，同步主域名服务器和辅助域名服务器数据