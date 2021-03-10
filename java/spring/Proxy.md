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