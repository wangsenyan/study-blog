···
 [文档](https://github.com/jamiebuilds/babel-handbook/blob/master/translations/zh-Hans/plugin-handbook.md)
···
## 基本操作
```sh
  npm uninstall babel

  npm install babel-cli --save-dev

  npx babel script.js

  npx babel script.js --watch/-w --out-file script-compiled.js
  npx babel script.js --out-file script-compiled.js --source-maps source maps编译
  npx babel script.js --out-file script-compiled.js --source-maps inline 内联的

  npx babel src --out-dir lib 编译整个src 目录将其输出到lib目录找那个
  npx babel src -d lib

  npx babel src --out-file script-compiled.js 编译整个src目录并将其输出到单个文件找中

  npx babel src --out-dir lib --ignore spec.js,test.js 忽略
  npx babel src --out-dir lib --copy-files 复制不需要编译的文件

  npx babel --out-file script-compiled.js < script.js 通过标准输入传入一个文件并输出到script-compiled.js
  npx babel script.js --out-file script-compiled.js --plugins=transform-runtime,transform-es2015-modules-amd
  使用插件

  npx babel script.js --out-file script-compiled.js --presets=es2015,react
  使用--presets 选项指定编译中要使用的插件

  npx babel --no-babelrc script.js --out-file script-compiled.js --presets=es2015,react
  忽略 .babelrc文件的配置并使用cli选项

  npm install babel babel-cli babel-preset-es2015 babel-preset-react
  babel demo.es6.js --presets es2015 -o demo.js 把es6转为es5
  babel demo.jsx --presets react -o demo.js 把jsx 转为es5的js
  {
    "presets": ["es2015", "react"]
  } 把es6与jsx同时编译
```
## 语法
  ### IfStatement
  ### ExpressionStatment
   * BlockStatement
   * ThrowStatement
   * AssignmentExpression
   * Identifier
   * Literal
   * MemberExpress
   * CallExpression
## 模块
 ### babylon
   Babel的解析器
   ```sh
   npm install --save babylon
   ```
   ```js
   import * as babylon from "babylon";
   const code = `function square(n) {
    return n * n;
    }`;

   babylon.parse(code);
   ```
 ### babel-traverse
   Babel-traverse(遍历)模块维护整棵树的状态，并且负责替换、移除和添加结点
   ```sh
   npm install --save babel-traverse
   ```
 ### babel-types
   1. path.node.property - AST 有 left,right,property属性
   2. 获取内部的path
     path.get('left')
     path.get('body.0')
   3. 检查结点的类型
     ```js
      t.isIdentifier(path.node.left)
      if(t.isIdentifier(path.node.left,{name:"n"}))
      ===
      if(
        path.node.left!=null &&
        path.node.left.type === "Identifier" &&
        path.node.left.name === "n"
      )

      path.get('left').isIdentifier({name:"n"})
      t.isIdentifier(path.node.left,{name:"n"})
     ```
   4. 检查标识符(identifier)是否被引用
     ```js
     Identifier(path){
       if(path.isReferencedIdentifier())
       // if(t.isReferrenced(path.node,path.parent))
     }
     ```
   5. 找到特定的父路径
     ```js
      path.findParent((path)=>path.isObjectExpression())
      /*遍历当前结点*/
      path.find((path)=>path.isObjectExpression())
     ```
   6. 查找最接近的父函数或程序
     ```js
      path.getFunctionParent();
     ```
   7. 向上遍历语法树，直到找到在列表中的父节点路径
     ```js
     path.getStatementParent()
     ```
   8. 获取同级路径
     * 使用 _path.inList_ 来判断路径是否有同级节点，
     * 使用 _path.getSibling(index)_ 来获得同级路径,
     * 使用 _path.key_ 获取路径所在容器的索引,
     * 使用 _path.container_ 获取路径的容器（包含所有同级节点的数组）
     * 使用 _path.listKey_ 获取容器的key
   9. 停止遍历
    ```js
    if (path.node.operator !== '**') return;
    ```
    如果在顶级路劲中进行遍历，则可以使用2个提供的api方法
    ```js
    path.skip()
    path.stop()
    ```
  ```sh
  npm install --save babel-types
  ```
 ### babel-generator
  代码生成器，它读取AST并将其转换为代码和源码映射（sourcemaps）
  ```sh
   npm install --save babel-generator
  ```
  ```js
   import * as babylon from "babylon";
   import generate from "babel-generator";

   const code = `function square(n) {
    return n * n;
   }`;

   const ast = babylon.parse(code);

   generate(ast, {}, code);

   generate(ast, {
    retainLines: false,
    compact: "auto",
    concise: false,
    quotes: "double",
    // ...
  }, code);
  ```
  ### babel-template
   babel-template 是另一个虽然很小但却非常有用的模块。 它能让你编写字符串形式且带有占位符的代码来代替手动编码， 尤其是生成的大规模 AST的时候。 在计算机科学中，这种能力被称为准引用（quasiquotes）。
   ```sh
   npm install --save babel-template
   ```
   ```js
    import template from "babel-template";
    import generate from "babel-generator";
    import * as t from "babel-types";

    const buildRequire = template(`
      var IMPORT_NAME = require(SOURCE);
    `);

    const ast = buildRequire({
      IMPORT_NAME: t.identifier("myModule"),
      SOURCE: t.stringLiteral("my-module")
    });

    console.log(generate(ast).code);
    var myModule = require("my-module");
   ```
