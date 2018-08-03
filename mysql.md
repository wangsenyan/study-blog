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