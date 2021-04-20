```sh
# 磁盘读写性能
# -d 显示某块具体硬盘,没有为全部 -k 以KB为单位显示 1 统计间隔为1s 10 共统计10次
iostat -d -k 1 10

```

### 查看流量
* iftop: 
* nethogs: 按进程查看流量占用
* iptraf: 按连接/端口查看流量
* ifstat: 按设备查看流量
* ethtool: 诊断工具
* tcpdump: 抓包工具
* ss: 连接查看工具
* 其他: dstat, slurm, nload, bmon