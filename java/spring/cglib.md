## cglib

* [借助asm生成字节码](https://blog.csdn.net/catoop/article/details/50629921)

```java

CglibAopProxy.getProxy()
	//获取回调
	CglibAopProxy.getCallbacks()
    		//创建代理
	CglibAopProxy.createProxyClassAndInstance()
	
		AdvisedSupport.getInterceptorsAndDynamicInterceptionAdvice()
		//
		Enhancer.generateClass()
		//生成方法的代理
		Enhancer.emitMethods()
		//类生成
		ClassEmiter
		//代码生成
		CodeEmiter.getStaticHook()

		MethodInterceptorGenerator.generate()

```