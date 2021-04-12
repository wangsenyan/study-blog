### 流程

* Redisson.create()

* Redisson(Config)

* ConnectionManager.createConnectionManager()

* SingleConnectionManager()

* MasterSlaveConnectionManager.initSingleEntry()

* MasterSlaveConnectionManager()

* MasterSlaveEntry.setupMasterEntry()

	* MasterSlaveConnectionManager.createClient()

	* RedisClient.create(redisConfig)

* MasterSlaveEntry.setupMasterEntry(client)

* SingleThreadEventExecutor.doStartThread()

* NioEventLoop.run()

* SingleThreadEventExecutor.runAllTasks()

* AbstractEventExecutor.safeExecute()

* Bootstrap.run()

* AbstractChannel.register(EventLoop,ChannelPromise)

* AbstractChannel.register0()

* DefaultChannelPipline.execute()

* DefaultChannelPipline.invokeHandlerAddedIfNeeded()

* DefaultChannelPipline.callHandlerAddedForAllHandlers()

* task.execute() -> task = task.next

* callHandlerAdded0()

* AbstractChannelHandlerContext.callHandlerAdded()


### Channel
* 和文件描述符一对一？提供抽象服务?
* Channel 和 pipeline 一对多

### Pipeline
* in/out handler 的载体

### Select
* bind -> doBind() -> initAndRegister() ->init(channel)