## <center>TPC/IP</center>
### 陌生词汇
 |*|*|*|*|*|*|*
 |-|-|-|-|-|-|-
### 常见命令
```sh
#启用网桥#
Linux# brctl addbr br0
#将br0与eth0桥接，从etho接收的帧会被br0处理，从br0发送的被eth0处理
Linux# brctl addif br0 eth0
Linux# brctl addif br0 eth1
#从<ifname>将<brname>分离出来
Linux# brctl showmacs <brname>
#shows a list of learned MAC addresses for this bridge.
Linux# brctl delif <brname> <ifname>
Linux# ifconfig etho up
Linux# ifconfig eth1 up
Linux# ifconfig br0 up
```
