### `BeanFactory` 容器 
    - `FactoryBean` --> 创建bean工厂 
    - `DefaultListableBeanFactory`
### 强化class `enhancedClass`
### bean定义(`AbstractBeanDefinition`)替换原class为`enhancedClass`
### `BeanPostProcessor` 回调

### 预加载
- static
- @PostConstruct
- 实现`ApplicationRunner`与`CommandLineRunner`
- 顺序 static>constructer>@PostConstruct>CommandLineRunner和ApplicationRunner

### 实例化bean
- `singletonsCurrentlyInCreation` 正在创建的单例
- `RootBeanDefinition` 类定义
- `doCreateBean` 之前先 判断是否有代理`resolveBeforeInstantiation`
- `populateBean` 填充bean