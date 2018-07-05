## <center>JAVA开发</center>

### 网站开发默认目录
```
|-- Deployment Descriptor:
|-- JAX-WS Web Services
|-- Java Resources
   |--src  -存放Java源代码的目录
   |--Libraries  -存放的是Tomcat及JRE中的jar包
|-- JavaScript Resources
   |--WebContent
   |--ECMAScript Build-In Library
   |--ECMA 3 Browser Support Library
|--build -自动编译java文件的目录
|--WebContent -需要部署到服务器的文件
   |--META-INF -存放工程自身相关的一些信息，元文件信息，通常由开发工具和环境自动生成
   |--WEB-INF - 不能被客户端直接访问
      |--classes - 存放Java字节码文件的目录
      |--lib -用于存放该工程用到的库
      |--web.xml -web工程的配置文件，完成用户请求的逻辑名称大真正的servlet类的映射
```   