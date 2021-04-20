## <center>REDIS</center>

### 基本操作

```sh
redis-cli -h host -p port # 链接
redis> keys *             # 所有的key
redis> type your-key      # 所选key的类型
```

### 基本类型

|key|String|Hash|List|set| sorted set
|:--|:-----|:---|:---|:---------|:-----------
|del |dump|exists|expire|sadd|zadd
|dump|set|hdel|blpop|scard|zcard
|exists|get|hexists|brpop|sdiff|zcount
|expire|getrange|hget|brpoplpush|sdiffstore|zincrby
|expireat|getset|hgetall|lindex|sinter|zinterstore
|pexpire|mget|hincrby|linsert|sinterstore|zlexcount
|keys pattern|setex|hincrbyfloat|llen|smember|zrange
|move|setbit|hkeys|lpop|smembers|zrangebylex
|persist|setrange|hlen|lpush|smove|zrangebyscore
|pttl|strlen|hmget|lpushx|spop|zrank
|ttl|mset|hset|lrange|srandmember|zrem
|rename|psetex|hsetnx|lrem|srem|zremrangebylex
|renamenx|incr|hvals|lset|sunion|zremrangebyrank
|type|incrby|hscan|ltrim|sunionstore|zremrangebyscore
|-|incrbyfloat|rpop|sscan|-|zrevrange
|-|decr|rpoplpush|-|-|zscore
|-|decrby|rpush|-|-|zunionstore
|-|append|rpushx|-|-|zscan
