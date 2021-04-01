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