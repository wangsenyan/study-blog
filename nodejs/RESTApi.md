---
  Transfer: 资源在网络中以某种表现形式进行状态转移
  Resource: 资源，即数据(网络核心)
  Representational: 某种表现形式，比如JSON，XML，JPEG
  State Transfer: 状态变化，通过HTTP动词实现
---
## HTTP 库
  * 必须支持HTTPS和SSL证书验证
  * 必须支持至少五个主要HTTP方法:GET,POST,HEAD,PUT,DELETE
  * 必须允许程序员定制PU或POST请求的实体主体里的数据
  * 必须允许程序员定制请求的HTTP报头
  * 必须允许程序员获取HTTP响应的响应代码和报头，不仅仅是HTTP响应的实体主体
  * 必须支持通过HTTP代理(proxy)进行HTTP通信
  * XML 解析器
    1. 基于文档的策略
    2. 基于事件的策略SAX
    3. JavaScript:responseXML 来自XMLHttpRequest,自动解析
## REST--Resource Representational State Transfer
  * URL定位资源，用HTTP动词(GET,POST,PUT，DELETE,DETC)描述操作
  * 描述在网络中client和server一种交互形式
  * URL中只使用名词指定资源，原则上不使用动词
  * JSON或XML传递资源的表现形式
  * 用HTTP Status Code传递Server的状态信息
注意:
  1. url root
  2. uri 使用名词而不是动词
  3. 保证HEAD和GET方法是安全的
  4. 资源的地址推荐嵌套结构，http支持分页(pagination操作)，在header中使用link即可
  5. 使用正确的HTTP Status Code表示访问状态
### restful特点
  * 可寻址性
  * 无状态性
  * 利用HTTP响应代码
### 面向资源构架 ROA
  * 作用域信息都在URI中
  * 把实际问题转换成REST式web服务的方法
  * 特性
    1. 可寻址性
    2. 无状态性
      * 每个HTTP请求都是完全孤立的，减少出错条件
      * 改变无状态性，常用session，状态保存在服务器端的某个数据结构里
      * 应用状态 保存在客户端
      * 资源状态 保存在服务端
      * 表示
         为同一资源的不同表示设定不同URI
         rest是连通性的？？？
    3. 连通性
    4. 统一接口
  * 资源
    1. 可以存放在计算机上并体现为比特流的事物
    2. URLs既是资源的名称也是资源的地址
    3. 一个资源可以有一个或多个URI
    4. 一个URI只能指示一个资源

### HTTP
  * 基于文档的协议
  * 请求
    1. methods
      * GET/HEAD/PUT/DELETE/POST
      * 创建一个新资源: 新URI发送HTTP PUT，或已有URI发送HTTP POST 服务器负责资源采用什么URI
      * 修改已有资源 HTTP PUT 客户端负责决定新资源用什么URI
      * HEAD 只包含元数据的表示 
      * OPTIONS 查看一个资源支持哪些HTTP方法
  * 响应
    1. HTTP响应代码 HTTP response code
    2. 响应报头 reqsponse headers
      * COntent-Type 实体主体的媒体类型 MIME类型、内容类型(content type)、数据类型(data type)
    3. 实体主体 entity-body/representation
  * 作用域信息
### HTTPS
   1. 443端口，标准HTTPS端口建立起TCP/IP套接字连接
### REST web服务
   * [Atom](http://www.ietf.org/html.charters/atompub-charter.html)
   * [Amazon S3](http://aws.amazon.com/s3)
   * [Yahoo](http://developer.yahoo.com/)
### 其他构架
   1. RPC
     XML-RPC 方法信息和作用域信息都放在XML文档中
     包括XML-RPC，SOAP等
     为每个处理远程调用的进程暴露一个URL
   2. REST-RPC
     只是把HTTP当成一种容纳文档的信封
     为每个操作暴露一个URI，不是为每一则数据暴露一个URI
   3. XML-RPC
   4. SOAP 
      基于XML的信封格式，属于RPC式架构
      WSDL web服务描述语言，WSDL文档
   5. WADL 
      web应用描述语言
### 
