### 代理

```java
public interface InvocationHandler {
	/**
	 * 前连个参数用于生成$Proxy的构造器,此构造器再以InvocationHandler为参数生成$Proxy实例
	 */
	public Object invoke(Object proxy, Method method, Object[] arg)
}
```
* AbstractAdvisorAutoProxyCreator.initBeanFactory
* AbstractAutoProxyCreator.wrapIfNecessary
  - Proxy继承需要代理的class
[参考](https://www.cnblogs.com/tuyang1129/p/12878549.html)

### CGLib动态代理
* 继承


### AOP

1. 切面Aspect： Aspect 声明类似于 Java 中的类声明，在 Aspect 中会包含着一些切入点Pointcut 以及对切入点进行相应的操作的通知Advice。
2. 连接点Joint point：表示在程序中明确定义的点，典型的包括方法调用，对类成员的访问以及异常处理程序块的执行等等，它自身还可以嵌套其它连接点jointpoint。
3. 切入点Pointcut：表示一组连接点jointpoint，这些连接点或是通过逻辑关系组合起来，或是通过通配、正则表达式等方式集中起来，它定义了相应的操作处理通知Advice将要发生的地方。
4. 通知Advice：Advice 定义了在切入点pointcut 里面定义的程序点具体要做的操作和处理，它通过 before、after 和 around 来区别是在每个切入点之前、之后还是代替执行的代码。
5. 目标对象Target：代理的目标对象，即切面要被应用到的目标对象。
6. 织入Weave：指将切面应用到目标对象，并导致代理对象创建的过程。

```java
//Advisor是具体执行器
PointcutAdvisor extends Advisor 
public Object intercept(Object proxy, Method method, Object[] args, MethodProxy methodProxy){
	 retVal = new CglibMethodInvocation(proxy, target, method, args, targetClass, chain, methodProxy).proceed();
}


ExposeInvocationInterceptor //公开调用拦截器

Signature getSignature() //获取连接点的方法签名对象； 


JoinPoint 
   java.lang.Object[] getArgs()：获取连接点方法运行时的入参列表； 
   Signature getSignature() ：获取连接点的方法签名对象； 
   java.lang.Object getTarget() ：获取连接点所在的目标对象； 
   java.lang.Object getThis() ：获取代理对象本身； 

ProceedingJoinPoint 
ProceedingJoinPoint继承JoinPoint子接口，它新增了两个用于执行连接点方法的方法： 
   java.lang.Object proceed() throws java.lang.Throwable：通过反射执行目标对象的连接点处的方法； 
   java.lang.Object proceed(java.lang.Object[] args) throws java.lang.Throwable：通过反射执行目标对象连接点处的方法，不过使用新的入参替换原来的入参


//执行被代理的方法
public Object invoke(Object obj, Object[] args) throws Throwable {
	try {
		init();
		FastClassInfo fci = fastClassInfo;
		return fci.f1.invoke(fci.i1, obj, args);
	}
	catch (InvocationTargetException ex) {
		throw ex.getTargetException();
	}
	catch (IllegalArgumentException ex) {
		if (fastClassInfo.i1 < 0)
			throw new IllegalArgumentException("Protected method: " + sig1);
		throw ex;
	}
}

```
### [Enhancer](https://www.cnblogs.com/micrari/p/7565632.html#:~:text=Enhancer%E6%98%AFcglib%E4%B8%AD%E4%BD%BF%E7%94%A8,%E9%83%BD%E5%B8%A6%E6%9C%89%E5%9B%9E%E8%B0%83%E9%92%A9%E5%AD%90%E3%80%82)

### AnnotationAwareAspectJAutoProxyCreator使用post-process生成代理类

### BeanPostProcessor.class