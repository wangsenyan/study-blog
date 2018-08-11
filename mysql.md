## mysql

### 导入导出功能
* 导入
```sh
mysql> source path/filename.sql
```
* 导出
```sh
>mysqldump -u[username] -p[password] [database] --add-drop-table >e:\new\myshop.sql
```

### 增删改查
### 表操作
### 数据库设计

### 查看表的注释和创建  
    注意键反引号

```sh
#创建
>create table `users`(
	`id` int(11) auto_increment primary key comment '学号',
	`name` varchar(32) not null default '' comment '姓名'
 )engine = innodb charset = utf8 comment = '表注释';

# 查看创建表的命令
>show create table `users`;

#修改表注释
>alter table `users` comment '注释';

#修改字段的注释
>alter table `users` modify column `id` comment '号码';

#查看表结构包括注释
>show full columns from `users`;
```
### 便捷方法

```sql
select @@IDENTITY id ## insert into 后获得自动插入的id, @@IDENTITY返回为当前会话的所有作用域中的任何表最后生成的标识符
select SCOPE_IDENTITY() as id ## 返回当前作用域和当前会话的任何表最后生成的标识符

```
### 函数

* CONCAT() - 将多个字符串连接成一个字符串  
* CONCAT_WS(separator,str1,str2,…) - 用separator分割参数
* CAST(value as type); - 获取一个类型的值并产生另一个类型的值
   * 二进制，同带binary前缀的效果 : BINARY    
   * 字符型，可带参数 : CHAR()     
   * 日期 : DATE     
   * 时间: TIME     
   * 日期时间型 : DATETIME     
   * 浮点数 : DECIMAL      
   * 整数 : SIGNED     
   * 无符号整数 : UNSIGNED
* CONVERT(value, type); - 获取一个类型的值并产生另一个类型的值

### 条件优先级
从左到右
and > or



