
**文件比较粗糙，具体看官方文档**
[sequelize](https://github.com/demopark/sequelize-docs-Zh-CN)
## 自动生成
  ```js
   sequelize.authenticate().then(()=>{}).catch(err=>{})
  ```
## 定义模块
  ```js
  sequelize.define('user',{attributes},{options})
  difine('user',{},{timestamps:true,createdAt:false,updatedAt: 'updateTimestamp',deletedAt: 'destroyTime',paranoid: true});// 时间戳默认为false
  ```
 ### 参数设置
  ```js
    paranoid: true //// 不删除数据库条目，但将新添加的属性deletedAt设置为当前日期（删除完成时）
    underscored: true //不使用驼峰样式自动添加属性，而是下划线样式，因此updatedAt将变为updated_at
    freezeTableName: true //禁用修改表名; 默认情况下，sequelize将自动将所有传递的模型名称（define的第一个参数）转换为复数。
    tableName: 'my_very_custom_table_name' //定义表的名
    comment: "I'm a table comment!" //注释
  ```
### engine:'MYISAM'
### 
  ```js
  const sequelize = new Sequelize('connectionUri', {
    define: {
      timestamps: false // 默认为 true
    }
  });
  ```
### 
  ```js
  const AuthorModel = db.import('project', require('./path/to/models/project'));
  ```
### Sequelize.STRING

### 强制执行，如果有就删除然后重建
  ```js
   User.sync({force:true}).then(()=>{return User.create({firstName:'Johe',lastName:'Hancock'});});
  ```
###User.findAll().then(users=>{})
### user=await User.findOne()
  console.log(user.get('firstName'))
### 
  ```js
   define('foo', {flag: { type: Sequelize.BOOLEAN, allowNull: false, defaultValue: true, unique:'compositeIndex'/true/false, autoIncrement: true}
   }) 
  ```
###
  ```js
  {indexes: [{unique: true, fields: ['someUnique']}]},
  ```
### Sequelize.DATA|INTEGER|
### 创建外键 
  ```js
   bar_id: {
   type: Sequelize.INTEGER,

   references: {
      // 这是引用另一个模型
    model: Bar,

      // 这是引用模型的列名称
    key: 'id',

      // 这声明什么时候检查外键约束。 仅限PostgreSQL。
    deferrable: Sequelize.Deferrable.INITIALLY_IMMEDIATE
   }
  }
 ```
 ## Project.sync()
   ```js
    Task.sync() //创建表
    Project.sync({force: true}) //强制创建
    Project.drop()
    Task.drop()//删除表
    //事件处理
    Project.[sync|drop]().then(() => {
    // 好吧...一切都很好！
    }).catch(error => {
      // oooh，你输入了错误的数据库凭据？
    })
  
    sequelize.sync() // 同步所有尚未在数据库中的模型
    sequelize.sync({force: true，match: /_test$/ }) //强制同步所有模型
    sequelize.drop() // 删除所有表
    sequelize.[sync|drop]().then(() => { //广播处理
      // woot woot
      }).catch(error => {
        // whooops
      })
   ``` 
  ## 索引
    [indexes](https://github.com/demopark/sequelize-docs-Zh-CN/blob/master/models-definition.md#%E9%85%8D%E7%BD%AE)
  ## setDataValue() 和 getDataValue() 函数
  ## 操作符
      ```js
       const Op = Sequelize.Op

        [Op.and]: {a: 5}           // 且 (a = 5)
        [Op.or]: [{a: 5}, {a: 6}]  // (a = 5 或 a = 6)
        [Op.gt]: 6,                // id > 6
        [Op.gte]: 6,               // id >= 6
        [Op.lt]: 10,               // id < 10
        [Op.lte]: 10,              // id <= 10
        [Op.ne]: 20,               // id != 20
        [Op.eq]: 3,                // = 3
        [Op.not]: true,            // 不是 TRUE
        [Op.between]: [6, 10],     // 在 6 和 10 之间
        [Op.notBetween]: [11, 15], // 不在 11 和 15 之间
        [Op.in]: [1, 2],           // 在 [1, 2] 之中
        [Op.notIn]: [1, 2],        // 不在 [1, 2] 之中
        [Op.like]: '%hat',         // 包含 '%hat'
        [Op.notLike]: '%hat'       // 不包含 '%hat'
        [Op.iLike]: '%hat'         // 包含 '%hat' (不区分大小写)  (仅限 PG)
        [Op.notILike]: '%hat'      // 不包含 '%hat'  (仅限 PG)
        [Op.regexp]: '^[h|a|t]'    // 匹配正则表达式/~ '^[h|a|t]' (仅限 MySQL/PG)
        [Op.notRegexp]: '^[h|a|t]' // 不匹配正则表达式/!~ '^[h|a|t]' (仅限 MySQL/PG)
        [Op.iRegexp]: '^[h|a|t]'    // ~* '^[h|a|t]' (仅限 PG)
        [Op.notIRegexp]: '^[h|a|t]' // !~* '^[h|a|t]' (仅限 PG)
        [Op.like]: { [Op.any]: ['cat', 'hat']} // 包含任何数组['cat', 'hat'] - 同样适用于 iLike 和 notLike
        [Op.overlap]: [1, 2]       // && [1, 2] (PG数组重叠运算符)
        [Op.contains]: [1, 2]      // @> [1, 2] (PG数组包含运算符)
        [Op.contained]: [1, 2]     // <@ [1, 2] (PG数组包含于运算符)
        [Op.any]: [2,3]            // 任何数组[2, 3]::INTEGER (仅限PG)

        [Op.col]: 'user.organization_id' // = 'user'.'organization_id', 使用数据库语言特定的列标识符, 本例使用 PG
              {
          rank: {
            [Op.or]: {
              [Op.lt]: 1000,
              [Op.eq]: null
            }
          }
        }
  ```
