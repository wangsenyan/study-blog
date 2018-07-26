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