#!/bin/bash

start_ssredir() {
    # please modify MyIP, MyPort, etc.
    (ss-redir -s 8.9.4.178 -p 8838 -m 'aes-256-gcm' -k fuck -b 127.0.0.1 -l 60080 --no-delay -u -T -v </dev/null &>>/var/log/ss-redir.log &)
}

stop_ssredir() {
    kill -9 $(pidof ss-redir) &>/dev/null
}

start_iptables() {
  
    #四种表 raw->mangle->nat->filter
    #raw表
    #filter表: 对数据包进行过滤,根据具体的规则要求决定如何处理一个数据包,包含三种链input,output,forward
    #nat表: 修改数据包的ip地址、端口号等信息,包含preouting,postouting,output
    #mangle表: 用来修改数据包的tos,ttl或者为数据包设置mark标记以实现流量整形,包含 prerouting、postrouting、input、output、forward链
    
    #五种规则链
    #INPUT链：入站时，应用此规则。
    #OUTPUT链：出站时，应用此规则。
    #FORWARD链：当接到需要通过防火墙中转发送给其他地址的数据包时，应用此链规则。
    #PREROUTING链：在对数据包做路由现则之前，应用。用于目标地址转换（DNAT）
    #POSTROUTING链：在对数据包做路由选择之后，应用。用于源地址转换（SNAT）。

    #-t, --table table 对指定的表 table 进行操作， 
    #table 必须是 raw， nat，filter，mangle 中的一个。
    #如果不指定此选项，默认的是 filter 表。
    
    #-N, --new-chain chain 用指定的名字创建一个新的链。

    ##################### SSREDIR #####################
    iptables -t mangle -N SSREDIR


    #-A, --append chain rule-specification 在指定链 chain 的末尾插入指定的规则，
    #也就是说，这条规则会被放到最后，最后才会被执行。规则是由后面的匹配来指定。
    #-j, --jump target <指定目标> ：即满足某条件时该执行什么样的动作。
    #target 可以是内置的目标，比如 ACCEPT，也可以是用户自定义的链。
    
    #CONNMARK 在整个连接上设置标记
    # connection-mark -> packet-mark
    iptables -t mangle -A SSREDIR -j CONNMARK --restore-mark
    iptables -t mangle -A SSREDIR -m mark --mark 0x2333 -j RETURN

    #-p 匹配协议
    #-d 匹配目标地址
    #--dport 匹配目标端口号
    #--sport 匹配来源端口号

    # 忽略发送到ss-server的流量
    # please modify MyIP, MyPort, etc.
    # ignore traffic sent to ss-server
    iptables -t mangle -A SSREDIR -p tcp -d 8.9.4.178 --dport 8388 -j RETURN
    iptables -t mangle -A SSREDIR -p udp -d 8.9.4.178 --dport 8388 -j RETURN

    #忽略发送到保留地址的流量
    # ignore traffic sent to reserved addresses
    iptables -t mangle -A SSREDIR -d 0.0.0.0/8          -j RETURN
    iptables -t mangle -A SSREDIR -d 10.0.0.0/8         -j RETURN
    iptables -t mangle -A SSREDIR -d 100.64.0.0/10      -j RETURN
    iptables -t mangle -A SSREDIR -d 127.0.0.0/8        -j RETURN
    iptables -t mangle -A SSREDIR -d 169.254.0.0/16     -j RETURN
    iptables -t mangle -A SSREDIR -d 172.16.0.0/12      -j RETURN
    iptables -t mangle -A SSREDIR -d 192.0.0.0/24       -j RETURN
    iptables -t mangle -A SSREDIR -d 192.0.2.0/24       -j RETURN
    iptables -t mangle -A SSREDIR -d 192.88.99.0/24     -j RETURN
    iptables -t mangle -A SSREDIR -d 192.168.0.0/16     -j RETURN
    iptables -t mangle -A SSREDIR -d 198.18.0.0/15      -j RETURN
    iptables -t mangle -A SSREDIR -d 198.51.100.0/24    -j RETURN
    iptables -t mangle -A SSREDIR -d 203.0.113.0/24     -j RETURN
    iptables -t mangle -A SSREDIR -d 224.0.0.0/4        -j RETURN
    iptables -t mangle -A SSREDIR -d 240.0.0.0/4        -j RETURN
    iptables -t mangle -A SSREDIR -d 255.255.255.255/32 -j RETURN
    # 标记连接的第一个数据包
    # mark the first packet of the connection
    iptables -t mangle -A SSREDIR -p tcp --syn                      -j MARK --set-mark 0x2333
    iptables -t mangle -A SSREDIR -p udp -m conntrack --ctstate NEW -j MARK --set-mark 0x2333

    # packet-mark -> connection-mark
    iptables -t mangle -A SSREDIR -j CONNMARK --save-mark

    #代理此计算机的传出流量
    ##################### OUTPUT #####################
    # proxy the outgoing traffic from this machine
    iptables -t mangle -A OUTPUT -p tcp -m addrtype --src-type LOCAL ! --dst-type LOCAL -j SSREDIR
    iptables -t mangle -A OUTPUT -p udp -m addrtype --src-type LOCAL ! --dst-type LOCAL -j SSREDIR

    #通过此计算机的代理流量（其他->其他）
    ##################### PREROUTING #####################
    # proxy traffic passing through this machine (other->other)
    iptables -t mangle -A PREROUTING -p tcp -m addrtype ! --src-type LOCAL ! --dst-type LOCAL -j SSREDIR
    iptables -t mangle -A PREROUTING -p udp -m addrtype ! --src-type LOCAL ! --dst-type LOCAL -j SSREDIR
    
    #将标记的包装交给TPROXY进行处理
    # hand over the marked package to TPROXY for processing
    iptables -t mangle -A PREROUTING -p tcp -m mark --mark 0x2333 -j TPROXY --on-ip 127.0.0.1 --on-port 60080
    iptables -t mangle -A PREROUTING -p udp -m mark --mark 0x2333 -j TPROXY --on-ip 127.0.0.1 --on-port 60080
}

stop_iptables() {

    #-D	num 删除某一条规则
    ##################### PREROUTING #####################
    iptables -t mangle -D PREROUTING -p tcp -m mark --mark 0x2333 -j TPROXY --on-ip 127.0.0.1 --on-port 60080 &>/dev/null
    iptables -t mangle -D PREROUTING -p udp -m mark --mark 0x2333 -j TPROXY --on-ip 127.0.0.1 --on-port 60080 &>/dev/null

    iptables -t mangle -D PREROUTING -p tcp -m addrtype ! --src-type LOCAL ! --dst-type LOCAL -j SSREDIR &>/dev/null
    iptables -t mangle -D PREROUTING -p udp -m addrtype ! --src-type LOCAL ! --dst-type LOCAL -j SSREDIR &>/dev/null

    ##################### OUTPUT #####################
    iptables -t mangle -D OUTPUT -p tcp -m addrtype --src-type LOCAL ! --dst-type LOCAL -j SSREDIR &>/dev/null
    iptables -t mangle -D OUTPUT -p udp -m addrtype --src-type LOCAL ! --dst-type LOCAL -j SSREDIR &>/dev/null
    
    #-F	清空规则链
    #-X 删除用户自定义的空链
    #-Z 清空计数
    ##################### SSREDIR #####################
    iptables -t mangle -F SSREDIR &>/dev/null
    iptables -t mangle -X SSREDIR &>/dev/null
}

start_iproute2() {
    ip route add local default dev lo table 100
    ip rule  add fwmark 0x2333        table 100
}

stop_iproute2() {
    ip rule  del   table 100 &>/dev/null
    ip route flush table 100 &>/dev/null
}

start_resolvconf() {
    # or nameserver 8.8.8.8, etc.
    echo "nameserver 1.1.1.1" >/etc/resolv.conf
}

stop_resolvconf() {
    echo "nameserver 114.114.114.114" >/etc/resolv.conf
}

start() {
    echo "start ..."
    start_ssredir
    start_iptables
    start_iproute2
    start_resolvconf
    echo "start end"
}

stop() {
    echo "stop ..."
    stop_resolvconf
    stop_iproute2
    stop_iptables
    stop_ssredir
    echo "stop end"
}

restart() {
    stop
    sleep 1
    start
}

main() {
    if [ $# -eq 0 ]; then
        echo "usage: $0 start|stop|restart ..."
        return 1
    fi

    for funcname in "$@"; do
        if [ "$(type -t $funcname)" != 'function' ]; then
            echo "'$funcname' not a shell function"
            return 1
        fi
    done

    for funcname in "$@"; do
        $funcname
    done
    return 0
}
main "$@"