## <center>thinkjs</center>

### ...

1. express 灵活性高，容易泄露内存
   thinkjs 异步简单
2. `npm install thinkjs@2 -g --registry=https://registry.npm.taobao.org --verbose` 
3. `thinkjs --version/-V`
4. `npm install (-g)thinkjs@2`  //(全局)更新
5. `thinkjs new (--es)`项目名称(es6模式)
6. `npm install`
7. |-- src/common 通用模块目录，项目目录都是按模块划分的
   |-- src/common/bootstrap 自动加载，定义全局函数、注册中间件等。
      |-- global.formatDate =obj=>{}
      |-- thinkjs.middleware("",http=>){}
   |-- src/common/config 通用配置，如路由/hook/本地化配置
   |-- src/common/controller 控制器，放置通用控制器
   |-- src/common/runtime 项目运行时生成的一些目录，如:缓存文件目录
   |-- src/home 项目默认模块,src/common/config/config.js修改配置default_module来重新定义默认模块
   |--src/home/logic 逻辑处理，每个操作执行前可以进行逻辑校验，参数是否合法、提交的数据是否正常、当前用户是否登录、是否有权限等。use strict  export default class extends think.logic.base{indexAction(){}}
   |--www 可访问根目录
   |--www/development.js 开发模式下的项目的入口文件
   |-- www/static 存放静态资源文件
8. 文件路径尽量用小写，用init代替constrcutor,thinkjs里所有的类都会继承think.base基类，类实例化时自动调用
9. 使用babel编译，使用async/await代替*/yield
10. 断点调试http://www.web2816.com/info/index/id/358.html
11. 默认服务监听的端口为8360，可以修改src/common/config/config.js 
12. 默认视图文件路径问view/[module]/[controller]_[action].html,修改src/common/config/view.js 
13. 错误的捕获http://www.web2816.com/info/index/id/359.html
     输出图像export default class extends think.controller.base {
      imageAction(){ //图片 buffer 数据，读取本地文件或者从远程获取                        let  imageBuffer = new Buffer(); this.type("image/png"); this.end(imageBuffer);
         }
      }
14. 不同环境使用不同配置src/common/config/env/[devolopment|testing|production] 开发|测试|线上
15. nunjunks模板继承路径使用相对路径{% extends "./parent.html" %} 
16. 跨模块调用:this.model调用
17. 线上模式502 
  ```sh
     export default class extends think.controller.base {
       indexAction(){ let method = this.http.method.toLowerCase(); if(method === "options"){ this.setCorsHeader(); this.end(); return;
        } this.setCorsHeader(); this.success();
      }
      setCorsHeader(){ this.header("Access-Control-Allow-Origin", this.header("origin") || "*"); this.header("Access-Control-Allow-Headers", "x-requested-with"); this.header("Access-Control-Request-Method", "GET,POST,PUT,DELETE"); this.header("Access-Control-Allow-Credentials", "true");
      }
     }
```
18. current path is not thinkjs project原因是.thinkjsrc文件丢失

19. thinkjs module xxx   添加 模块（默认common/home）
     禁用模块src/common/config/config.js，export default {
    deny_module_list: ["xxx"] //禁用 xxx 模块 }
20. 控制器是一类操作的集合,用来相应用户同一类的请求
     module.exports = think.controller(Base,{indexAction:function(self){//auto render template file index_index.html  return self.display();}})
    多层控制器:如src/home/controller/group/article.js,解析为二级，具体为group/article,Logic,View的目录与此相同。
21. 动态创建类方式（保证class有contructor）
     init(http){super.init(http)}; es6方法
     init:function(http){this.super("init",http);//调用父类的init方法}
22. 前置操作_before
     在具体action调用之前自动调用。_before(){}，后置操作_after,空操作_call
23. Action 一个Action代表一个要执行的操作，如：URL为/home/article/detail
     解析后的模块为/home,控制器为article，action为detail，name执行的Action就是文件src/home/controller/aritcle里的detailAction。注意二级控制器
24. Logic数据校验，assign和display进行变量赋值和模板渲染 ？？？
     this.model("user") 模型实例化？？？
25. 控制器在实例化时，会将http传递进去，该http对象是thinkjs对req和res重新包装的一个对象，非node.js内置http对象
26. 回调或者Promise都会增加一层作用域，导致在回调函数内无法直接使用this,简单的处理办法是在顶部定义一个变量，将 this 赋值给这个变量，然后在回调函数内使用这个变量。indexAction:function(self)中self等同于var self=this
27. JSON输出
    this.success和this.fail方法来输出这样的接口数据。
    indexAction(){ let data = {name: "thinkjs"}; this.success(data);}
    indexAction(){ this.fail(1000, "connect error");
   export default{10001:"get data error"}放在 src/common/config/locale/[lang].js 
28. GET参数
     indexAction(){ let name = this.get("name"); let allParams = this.get(); //获取所有 GET 参数 }
29. POST参数
     indexAction(){ let name = this.post("name"); let allParams = this.post(); //获取所有 POST 参数 }
30. file方法获取上传的文件
     indexAction(){ let file = this.file("image"); let allFiles = this.file(); //获取所有上传的文件 }返回值是个对象，包含
     {fieldName: "file", //表单字段名称 originalFilename: filename, //原始的文件名 path: filepath, //文件保存的临时路径，使用时需要将其移动到项目里的目录，否则请求结束时会被删除 size: 1000 //文件大小 }

31. 
```
    JSONP //this.jsonp方法输出JSONP格式的数据，callback请求参数名默认callback
    isGet() 当前是否是 GET 请求
    isPost() 当前是否是 POST 请求
    isAjax() 是否是 AJAX 请求
    ip() 获取请求用户的 ip
    redirect(url) 跳转到一个 url
    write(data) 输出数据，会自动调用 JSON.stringify
    end(data) 结束当前的 http 请求
    json(data) 输出 JSON 数据，自动发送 JSON 相关的 Content-Type
    jsonp(data) 输出 JSONP 数据，请求参数名默认为 callback
    success(data) 输出一个正常的 JSON 数据，数据格式为 {errno: 0, errmsg: "",     data: data}
    fail(errno, errmsg, data) 输出一个错误的 JSON 数据，数据格式为 {errno:     errno_value, errmsg: string, data: data}
    download(file) 下载文件
    assign(name, value) 设置模版变量
    display() 输出一个模版
    fetch() 渲染模版并获取内容
    cookie(name, value) 获取或者设置 cookie
    session(name, value) 获取或者设置 session
    header(name, value) 获取或者设置 header
    action(name, data) 调用其他 Controller 的方法，可以跨模块
    model(name, options) 获取模型实例
```
32. 视图模式view/ 默认命名规则 模块/控制器_操作.html
     如果每个模块有独立的视图目录，将配置root_path修改为空即可
     Ttinkjs默认支持的模板引擎有ejs,jade,swig,nunjucks,通过adapter设置
      ejs默认的定界符是<%和%>，通过delimiter:"&"修改
     转义输出<%=data.name%>
     不转义输出<%-data.name%>
     注释<%#data.name%>
     条件判断<%if(){%>
                     <%else if(){%>
                      <%}%>
    引用文件 <%include in/header.html/%>
    变量赋值:this.assign("name","value")

                     this.assign({name:"value",name1:"value1"})
     获取赋值 let title =this.assign("name")
     模板渲染indexAction(){this.display();//render home/index_index.html}
     获取渲染后的内容indexAction(){ let content = yield this.fetch();
     动态创建类的方式indexAction: function(){ this.fetch().then(function(content){}）}
     默认模板变量http/controller.navType="home"/config.name="text"
     国际化方法_<%_("title")%>
33. common 模块下定义一些通用的配置，其他模块下配置会继承 common 下的配置
     每个模块下的config/config.js存放基本配置，config/[name].js存放具体某个独立功能的配置，如db.js，config/env/[mode].js不同项目环境的差异化配置
34. 配置读取，在Controller，Logic，Middleware等地方可以通过this.config("db")来获取/this.config("db"),路由解析前无法通过上面方法获取非通用模块下的配置
    系统默认配置http://www.web2816.com/info/index/id/363.html
35. 路由：URL解析为pathname,根目录开始
     模块/控制器/操作/参数1/参数1值/参数2/参数2值 默认识别
     eg.pathname为admin/group/detail识别后module为admin,controller为group,action为detail,对应方法为detailAction,如果admin这个模块被禁用或无用了，则识别后的结果为module为默认home，controller为admin，action为group，方法为groupAction参数为{detail:""}
     如果有多级控制器，那么会进行多级控制器的识别，然后才是 action 的识别。
     大写转小写，action取消_,但模板名还是有_,controller_action.html
     默认路由src/common/config/config.js
36. 自定义路由 route_on:true; 
    export default [
     ["规则1", "需要识别成的pathname"],
     ["规则2", {
      get: "get请求下需要识别成的pathname",
      post: "post请求下需要识别成的pathname" }]
    ];
37. 正则路由，
```js
    export default [
      [/^article\/(\d+)$/, {
        get: "home/article/detail?id=:1", delete: "home/article/delete?id=:1",
        post: "home/article/save?id=:1" }]
      ];//多个分组，通过:1,:2,:3获取相应的值
        //规则路由，
     export default [
       ["group/:year/:month", "home/group/list"]
       ]
     //静态路由，
        export default [
        ["list", "home/article/list"]
      ]
      //优化路由：
      common/config/route.js
      admin：{reg:/^(account|admin)} //account和admin都命中admin模块
```
38. 创建模型 `thinkjs model [name] src/common/model/user.js`    
            `thinkjs model home/user   src/home/model/user.js`  
    模型命名采用驼峰时的规则,首字母大写，去除表的前缀 `db_prefix`  
    UserModel->数据表think_user[如果前缀为think_]  
    model.pk 数据表主键，默认为id  
    model.name 模型名，默认从当前文件名中解析  
    model.tablePrefix 数据表名称前缀，默认为think_  
    model.tableName 数据表名称，不包含前缀，默认等于模型名  
    model.fields 数据表字段  
    model.indexes 数据表索引，默认自动从数据表分析  
    model.config 配置，实例化的时候指定  
    model._db 连接数据库句柄  
    model._data 操作的数据库 model._options操作选项    
    model方法  
        model.model(name,options,module) 模型名称/配置项/模块名                  
        链式调用  
        where, 用于查询或者更新条件的定义  
        table, 用于定义要操作的数据表名称  
        alias, 用于给当前数据表定义别名  
        data, 用于新增或者更新数据之前的数据对象赋值  
        field, 用于定义要查询的字段，也支持字段排除  
        order, 用于对结果进行排序  
        limit, 用于限制查询结果数据  
        page, 用于查询分页，生成 sql 语句时会自动转换为 limit  
        group, 用于对查询的 group 支持  
        having, 用于对查询的 having 支持  
        join, 用于对查询的 join 支持  
        union, 用于对查询的 union 支持  
        distinct, 用于对查询的 distinct 支持  
        cache 用于查询缓存  
39. 修改主键
      export default class extends think.model.base {
                 init(...args){ super.init(...args); this.pk = "user_id"; //将主键字段设置为 user_id       }
}
    分布式数据库
    const MYSQL_READ={host:"10.0.0.1",}
    const MYSQL_WRITE={host:"10.0.0.2"}
    export default{host:"127.0.0.1",
                            adapter:{
                                mysql:{
                                   parser:function(options){let sql=options.sql;
                                                                           if(sql.indexOf("SELECT")===0){
                                                                              return MYSQL_READ;
}                                        return MYSQL_WRITE;                                                                    
}
}                            
}}
40. 添加一条数据add
     addAction(){ let model = this.model("user"); let insertId = yield model.add({name: "xxx", pwd: "yyy"});
    添加多条数据addMany
     addAction(){ let model = this.model("user"); let insertId = yield model.addMany([
     {name: "xxx", pwd: "yyy"},
     {name: "xxx1", pwd: "yyy1"}
    ]);
  }检查字段唯一thenAdd
    thenAdd(data,where,ture)，
    更新数据update，返回为影响的行数，添加where防止误操作，
     updateAction(){ let model = this.model("user"); let affectedRows = yield model.where({name: "thinkjs"}).update({email: "admin@thinkjs.org"});
  }或者where("1=1")更新所有的数据
    给符合条件的字段添加特定的值increment
     this.where({id: id}).increment("view_nums", 1);
    给符合条件的字段减少特定的值
    this.where({id:id}).decrement("num",10);
41.  查询数据  
     单条数据 this.model("user").where({name:"this"}).find();返回对象，可用this.isEmpty检查{}  
     多条数据this.model("user").limit(4).select();返回值为[{}]格式  
     分页查询数据 this.model("user").page(this.get("page"),10).countSelect();返回值格式为  
             {  
       numsPerPage: 10, //每页显示的条数 currentPage: 1, //当前页 count: 100, //总条数     totalPages: 10, //总页数 data: [{ //当前页下的数据列表 name: "thinkjs",  
       email: "admin@thinkjs.org" }, ...]  
      }  
      countSelect(true)修正到第一页，countSelect(false)修正到最后一页，countSelect(1000)  
     总条数  
     查询符合条件的总条数count(）  
     查询符合条件的字段总和sum()this.where({status: "publish"}).sum("view_nums");  
     符合条件的最大值max() this.where({status: "publish"}).max("comments");  
     符合条件的最小值min()   
     查询缓存return this.cache("get_list", 3600).where({id: {">": 100}}).select();  
     缓存配置src/common/config/db.js   
     删除数据delete this.model("user").where({}).delete()  
42. 使用事务  
      startTrans 开启事务  
      commit 正常操作后，提交事物  
         rollback  操作异常后进行回滚  
       等同于transaction  
43. [关联模型,即id和user_id的对应关系](http://www.web2816.com/info/index/id/369.html)
      think.model.HAS_ONE 一对一 模型  
      this.model.BELONG_TO 一对一属于，与has_one相反  
      this.model.HAS_MANY 一对多  
      this.model.MANY_TO_MANY 多对多   
      创建方式 think.model.relation{cate:{},comment:{}};init(...args){super.init(...args)}  
      设置关联关系查询后，查询操作都会自动查询关联表的数据。  
      通过setRelation（false）方法临时关闭关联关系查询  
      部分关闭setRelation（"comment",false）关闭comment  
      全部启用setRelation（true）  
      设置查询条件：field:"id,name.email"相当于populate（）
      ```js
            field: model => { return model._relationField;
                where: where: model => { return model._relationWhere;
                page:page: [1, 15] //第一页，每页 15 条 } 
                         page: model => { return model._relationPage;}
                limit: page: model => { return model._relationLimit;}
                order:order: model => { return model._relationOrder;}
           selectData(){ this._relationOrder= "level DESC"; return this.select();}
    ```
    设置变量
44. adapter解决一类功能的多种实现，如：支持多种数据库，支持多种模版引擎等  
    有Cache，Session，WebSocket，Db，Store，Template，Socket   
    thinkjs adapter template/dot 创建名为dot的template adapter，路径在src/common/adapter/template/dot.js  
    通过think.adapter("template","dot")加载  
    使用第三方引入let DotTemplate = require("think-template-dot");  
               think.adapter("template", "dot", DotTemplate);  
45. cache memory内存缓存，file文件缓存，memcache,redis缓存  
    新建扩展缓存thinkjs adapter cache/fo  
46. session 支持file，db,redis,memory  
    读取this.session("userInfo")  
    设置this.session("userInfo",data)  
    清除this.session();  
    http.session()读取session  
    创建thinkjs adapter session/foo   
    创建文件 src/common/adapter/session/foo.js  
47. 模板引擎 src/common/config/view.js
48. [middleware中间件 `src/common/config/hook.js`](http://www.web2816.com/info/index/id/376.html)  
    解析参数，判断是否静态资源访问，路由解析，页面静态化判断，执行操作，查找模版，渲染模版等。项目里根据需要可能还会增加其他的一些处理，如：判断 IP 是否在黑名单中，CSRF   检测等。  
    payload_parse: ["prepend", "parse_xml"] prepend前置追加，append后置追加,返回promise  
    await think.hook("payload_parse",hhtp,data);  
    await this.hook("payload_parse",data) 有http对象直接使用this.hook  
    class 方式 thinkjs middleware xxx  
    http._get 用来存放 GET 参数值，http.get(xxx) 从该对象获取数据  
    http._post 用来存放 POST 参数值，http.post(xxx) 从该对象获取数据  
    http._file 用来存放上传的文件值，http.file(xxx) 从该对象获取数据  
49. think.ROOT_PATH  项目的根目录。
    think.RESOURCE_PATH  静态资源根目录，路径为 think.ROOT_PATH + /www/。
    think.APP_PATH  APP 代码目录，路径为 think.ROOT_PATH + /app/。  
    think.THINK_PATH  ThinkJS 框架的根目录。  
    think.THINK_LIB_PATH ThinkJS 框架 lib 目录。  
    think.getPath(module, type) let path1 = think.getPath("common", "model");//获取common 下 model 的目录 
    let path2 = think.getPath("home", "controller"); //获取 home 模块下 controller 的目录 
    自定义路径常量 项目的入口文件src/index.js 或src/production.js
    可以再src/common/bootstrap里的文件定义路径常量
    `__dirname,__filename,process.cwd()` 绝对路径 
50. 通过命令行访问URL，http://www.web2816.com/info/index/id/387.html
    `node www/production.js home/index/index` 表示执行 home 模块下 index Controller 里的 indexAction。
51. `npm run compile` 将src/目录编译到app/目录，然后将app/目录下的文件下线  
    `npm install -g pm2`
52. async await
     async表示，这是一个async函数，await只能用在这个函数里面，await表示在这里等待promise返回结果，再继续执行，await后面跟着的应该是一个promise对象

```js
   var sleep = function (time) {
    return new Promise(function (resolve, reject) {
        setTimeout(function () {
            // 模拟出错了，返回 ‘error’
            reject('error');
        }, time);
     })
   };

  var start = async function () {
    try {
        console.log('start');
        await sleep(3000); // 这里得到了一个返回错误
        
        // 所以以下代码不会被执行了
        console.log('end');
    } catch (err) {
        console.log(err); // 这里捕捉到错误 `error`
    }
  };
```
 循环多个await
 写入for循环里
  
53. `https://www.jianshu.com/p/063f7e490e9a`
   promise对象代表一个异步操作。(Pending进行中、Resolved已完成、Rejected以失败)
   一旦状态改变就不再变化，任何时候可以得到这个结果。Pending->Resolved/Rejected
    缺点：无法取消，不设置回调函数取不到内部错误信息，处于pending不能得知具体阶段 
    var promise=new Promise(function(resolve,reject){if(success){resolve(value);}else{reject(error);}});
    promise.then(function(value){success},function(value){failure})
   如果异步操作成功，则用 resolve 方法将 Promise 对象的状态，从「未完成」变为「成功」（即从 pending 变为 resolved）；  

    如果异步操作失败，则用 reject 方法将 Promise 对象的状态，从「未完成」变为「失败」（即从 pending 变为 rejected）
    基本的API：Promise.resolve()/Promise.reject()/Promise.prototype.then()/Promise.prototype.catch()/Promise.all()//所有的完成/Promise.race()//竞速，完成一个即可 promises 的奇妙在于给予我们以前的 return 与 throw，每个 Promise 都会提供一个 then() 函数，和一个 catch()，实际上是 then(null, ...) 函数，
   somePromise().then(function(){//do something})
  return 另一个promise/return 一个同步的值/throw 一个同步异常throw new error('')

54. 框架默认的配置-》项目模式下的框架配置-》项目公共配置-》项目模式下的公共配置-》模块下的配置（后加载的key值会覆盖先加载的key）
