## Cluster
 ```sh
  var cluster = require('cluster');
 ```
 * cluster是child_process和net模块的组合应用
## 工作进程
  由child_process.fork()创建
  方法1：循环法,主监听端口，连接分发给工作进程
  方法2：主进程创建监听socket后发送给感兴趣的工作进程，由工作进程负责直接接收连接
## Worker
  * Worker包含进程的public的信息和方法
  * 在一个主进程中，使用cluster.workers获取worker对象
  * 在一个工作进程中，使用cluster.worker获取worker对象
## 断开连接

```js
 cluster.fork().on('disconnect',()=>{
 })
```
## process.on('error')

```js
const worker = cluster.fork()
worker.on('exit',(code,signal)=>{
    if(signal){
        console.log(`worker was killed by signal:${signal}`);
    }else if(code!==0){
        console.log(`worker exited with error code:${code}`);
    }else{
        console.log(`worker success`)
    }
    })
```
## API
### cluster.fork([env])
  * env 增加进程环境变量
  * return <cluster.Worker>
  * 衍生出一个新的工作进程，只能通过主进程调用

### cluster.isMaster
  * 当进程为主进程时，返回true
  * 由 _process.env.NODE_UNIQUE_ID_ 决定，当该值未定义时，isMaster为ture
