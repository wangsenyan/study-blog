### 集群
* redis 共有16384个槽(slot) {0..16383}
```sh
redis-cli -p {port} cluster addslots {start..end}
```