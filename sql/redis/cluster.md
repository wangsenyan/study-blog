### [配置文件](./redis7000.conf)
```sh
# 启动
redis-server redis7000.conf
# 以cluster启动redis
redis-cli -p 7000 -c

# 启动客户端并分配槽,{0,16383}
redis-cli -p 7002 cluster addslots {0..5000}
# 当前集群节点
>cluster nodes
# 将节点 7001 加入集群
>cluster meet host port
# cluster 信息 
>cluster info

# key 所在的槽
>cluster keyslot key

#迁移槽
#目标节点准备接收槽
target>cluster setslot [slot] importing [source_id]
#源节点准备将槽迁移至目标节点
source>cluster setslot [slot] migrating [target_id]
#从源节点获取槽下的count 个 key
source>cluster getkeysinslot [slot] [count]
#源节点将key发送给目标节点
source>migrate [target_ip] [target_port] [key] 0 [timeout]
#通知集群槽指派完毕
anany>cluster setslot [slot] node [target_id] 

#从节点slave
slave>cluster replicate [master_id]
slave>slaveof [master_ip] [master_ip]
#从结点要在非cluster下创建
```

### [一致性哈希](https://blog.csdn.net/cywosp/article/details/23397179)