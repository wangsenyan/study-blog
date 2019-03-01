## <center>RPC</center>
![RPC](../image/RPC.png)
### 基本概念
|组成|说明
|----|----
|RpcServer|负责导出(export)远程接口
|RpcClient|负责导入(import)远程接口的代理实现
|RpcProxy|远程接口的代理实现
|RpcInvoker|客户方实现:负责编码调用信息和发送调用请求到服务方并等待调用结果返回<br>服务方实现:负责调用服务端接口的具体实现并返回调用结果
|RpcProtocal|负责协议编/解码
|RpcConnector|负责维持客户方和服务方的连接通道和发送数据到服务方
|RpcAccepter|负责接收客户方请求并返回请求结果
|RpcProcessor|负责制服务方控制调用过程，包括管理调用线程池、超时时间等。
|RpcChannel|数据传输通道
### 参考(https://blog.csdn.net/mindfloating/article/details/39474123)
