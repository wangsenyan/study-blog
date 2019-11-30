## <center>文件和目录</center>

### 函数stat、fstat、fstatat 和 lstat

```c
#include <sys/stat.h>

int stat(const char *restrict pathname,struct stat *restrict buf);

int fstat(int fd,struct stat *buf);

int lstat(const char *restrict pathname,struct stat *restrict buf); 
//符号链接时，返回链接本身的信息
int fstatat(int buf,const char *restrict pathname,struct stat *restrict buf,int flag);//相对路径
//返回：若成功，返回0，出错返回-1

struct stat {
  mode_t            st_mode; /*file type & mode (permissions) */
  ino_t             st_ino;  /*i-node number(serial number) */
  dev_t             st_dev;  /*device number(file system) */
  dev_t             st_rdev; /*device number for special files */
  nlink_t           st_nlink;/*number of links */
  uid_t             st_uid;  /*user Id of owner */
  gid_t             st_gid;  /*group Id of owner */
  off_t             st_size; /*size in bytes,for regular files */
  struct timespec   st_atime;/*time of last access */
  struct timespec   st_mtime;/*time of last modification */
  struct timespec   st_ctime;/*time of last file status change */
  blksize_t         st_blksize;/*best I/O block size */
  blkcnt_t          st_blocks;/*number of disk blocks allocated */
};

struct timespec {
  time_t tv_sec;
  long tv_nsec;
  ...
};

#define S_IFMT //屏蔽字
#define S_ISDIR(mode) (((mode)&S_IFMT)==S_IFDIR) //宏

struct inode {
        struct hlist_node       i_hash;              /* hash list */
        struct list_head        i_list;              /* list of inodes */
        struct list_head        i_dentry;            /* list of dentries */
        unsigned long           i_ino;               /* inode number */
        atomic_t                i_count;             /* reference counter */
        umode_t                 i_mode;              /* access permissions */
        unsigned int            i_nlink;             /* number of hard links */
        uid_t                   i_uid;               /* user id of owner */
        gid_t                   i_gid;               /* group id of owner */
        kdev_t                  i_rdev;              /* real device node */
        loff_t                  i_size;              /* file size in bytes */
        struct timespec         i_atime;             /* last access time */
        struct timespec         i_mtime;             /* last modify time */
        struct timespec         i_ctime;             /* last change time */
        unsigned int            i_blkbits;           /* block size in bits */
        unsigned long           i_blksize;           /* block size in bytes */
        unsigned long           i_version;           /* version number */
        unsigned long           i_blocks;            /* file size in blocks */
        unsigned short          i_bytes;             /* bytes consumed */
        spinlock_t              i_lock;              /* spinlock */
        struct rw_semaphore     i_alloc_sem;         /* nests inside of i_sem */
        struct semaphore        i_sem;               /* inode semaphore */
        struct inode_operations *i_op;               /* inode ops table */
        struct file_operations  *i_fop;              /* default inode ops */
        struct super_block      *i_sb;               /* associated superblock */
        struct file_lock        *i_flock;            /* file lock list */
        struct address_space    *i_mapping;          /* associated mapping */
        struct address_space    i_data;              /* mapping for device */
        struct dquot            *i_dquot[MAXQUOTAS]; /* disk quotas for inode */
        struct list_head        i_devices;           /* list of block devices */
        struct pipe_inode_info  *i_pipe;             /* pipe information */
        struct block_device     *i_bdev;             /* block device driver */
        unsigned long           i_dnotify_mask;      /* directory notify mask */
        struct dnotify_struct   *i_dnotify;          /* dnotify */
        unsigned long           i_state;             /* state flags */
        unsigned long           dirtied_when;        /* first dirtying time */
        unsigned int            i_flags;             /* filesystem flags */
        unsigned char           i_sock;              /* is this a socket? */
        atomic_t                i_writecount;        /* count of writers */
        void                    *i_security;         /* security module */
        __u32                   i_generation;        /* inode version number */
        union {
                void            *generic_ip;         /* filesystem-specific info */
        } u;
};



```

* 文件类型
  - 普通文件
  - 目录文件
  - 块特殊文件
  - 字符特殊文件
  - FIFO
  - 套接字
  - 符号链接

![stat](../../image/stat.png)

![ipc_stat](../../image/ipc_stat.png)

### 设置用户ID和设置组ID

![user_group](../../image/user_group.png)

![st_mode](../../image/st_mode.png)

* 当用名字打开任一类型的文件时，对该名字中包含的每一个目录，包括可能隐含的当前工作目录都应有执行权限  
  /usr/include/stdio.h  ->  /、/usr、/user/include  
  对一个不具有执行权限的目录，shell绝不会在该目录下找到可执行文件

* 为了在一个目录中创建一个新文件，必须对该目录具有写权限和执行权限
* *为了删除一个现有文件，必须对包含该文件的目录具有写权限和执行权限，对该文件本身不需要有读写权限*
* exec 执行的文件必须对该文件本身具有执行权限，该文件还必须是一个普通文件
* 权限检查 - 进程执行文件，进程id匹配用户id/用户组id ->匹配权限

### 函数access和faccessat
* 检查文件的用户权限
* open打开文件，内核以进程的有效用户ID和有效组ID为基础执行访问权限测试
* 实际用户 - 登录用户

```c
#include <unistd.h>
int access(const char *pathnanme,int mode);
int faccessat(int fd,const char *pathname,int mode,int flag);
//返回：成功，返回0，失败，返回-1

```

mode | 说明
-----|-----
F_OK | 文件是否存在
R_OK | 测试读权限
W_OK | 测试写权限
X_OK | 测试执行权限

* faccessat 
  - pathname 参数为绝对路径 和 fd参数取值为AT_FDCWD而pathname参数为相对路径
  - flag 设置为 AT_ACCESS，访问检查有效用户id和有效组ID

* 权限

11 | 10 | 9 | 8 | 7 | 6 | 5 | 4 | 3 | 2 | `1` | 0
---|----|---|---|---|---|---|---|---|---|---|---
`S`  | `G`  | `T` | `r` | `w` | `x` | `r` | `w` | `x`| `r` | `w` | `x`

* S 代表设置但该位置没有设置执行位，s代表设置执行位
* 加SUID和SGID，在程序的可执行位被设置时起作用
  - chmod u + s filename 设置SUID位
  - chmod u - s filename 去掉SUID位
  - chmod g + s filename 设置SGID位
  - chmod g - s filename 去掉SGID位

### 函数umask

* umask函数为进程设置文件模式创建屏蔽字，并返回之前的值

```c
#include <sys/stat.h>
mode_t umask(mode_t cmask);//返回：之前的文件模式创建屏蔽字
```

* 更改进程的文件模式创建屏蔽字并不影响父进程的屏蔽字
* 屏蔽字8进制数，一位代表一种要屏蔽的权限
* umask -S 打印符号格式

屏蔽位|含义
-----|-----
0400 | 用户读
0200 | 用户写
0100 | 用户执行
0040 | 组读
0020 | 组写
0010 | 组执行
0004 | 其他读
0002 | 其他写
0001 | 其他执行


### 函数 chmod、fchmod、fchmodat
* 更改现有文件的访问权限

```c
#include <sys/stat.h>
int chmod(const char *pathname,mode_t mode);
int fchmod(int fd,mode_t mode);
int fchmodat(int fd,const char *pathname,mode_t mode,int flag);
//返回：若成功，返回0，出错返回-1
```

mode    | 说明
--------|-----------------------
S_ISUID | 执行时设置用户ID
S_ISGID | 执行时设置组ID
S_ISVTX | 保存正文(粘着位)
--------|-----------------------
S_IRWXU | 用户(所有者)读、写和执行
S_IRUSR | 用户(所有者)读
S_IWUSR | 用户(所有者)写
S_IXUSR | 用户(所有者)执行
--------|-----------------------
S_IRWXG | 组读、写和执行
S_IRGRP | 组读
S_IWGRP | 组写
S_IXGRP | 组执行
--------|----------------------
S_IRWXO | 其他读、写和执行
S_IROTH | 其他读
S_IWOTH | 其他写
S_IXOTH | 其他执行

### 黏着位
* 如果对一个目录设置了黏着位，只有对该目录具有写权限的用户并且满足下列条件之一，才能删除或重命名该目录下的文件
  - 拥有此文件
  - 拥有此目录
  - 是超级用户

### 函数 chown、fchown、fchownat和lchown
* 更改文件的用户ID和组ID，如果两个参数owner或group中的任意一个是-1，则对应的ID不变
* lchown和fchownat(设置了AT_SYMLINK_NOFOLLOW标志)更改符号链接本身的所有者，而不是该符号链接所指向的文件的所有者
* 你可以更改你所拥有的文件的组ID，但只能改到你所属的组
```c
#include <unistd.h>
int chown(const char *pathname,uid_t owner,gid_t group);
int fchown(int fd,uid_t owner,gid_t group);
int fchownat(int fd,const char *pathname,uid_t owner,gid_t group,int flag);
int lchown(const char *pathname,uid_t owner,gid_t group);
//返回：成功，返回0，出错，返回-1
```

* 符号链接文件长度是在文件名中的实际字节数
* st_blksize 对文件I/O较合适的块长度
* st_blocks 是所分配的实际512字节块块数

### 文件中的空洞
* 由设置的偏移量超过文件尾端，并写入了某些数据后造成的
* 复制会将所有空洞填满，实际数据字节皆填0
```c
ls -l file.hole file.nohole
du -s file.hole file.nohole //多少个512字节块
wc -c file.hole  //计算文件中的字节数
```

### 文件截断

```c
#include <unistd.h>
int truncate(const char *pathname,off_t length);
int ftruncate(int fd,off_t length);
//返回：成功，0，出错，-1
```

### 文件系统

### 函数link、linkat、unlink、unlinkat、remove

* unlink：打开该文件的进程个数为0，链接计数为0，删除文件的内容
```c
#include <unistd.h>
int link(const char *existingpath,const char *newpath);
int linkat(int efd,const char *existingpath,int nfd,const char *newpath,int flag);
int unlink(const char *pathname);
int unlinkat(int fd,const char *pathname,int flag);

#include <stdio.h>
int remove(const char *pathname);
//返回：若成功，返回0，若出错，返回-1
```

### 函数rename和renameat

```c
#include <stdio.h>
int rename(const char *oldname,const char *newname);
int renameat(int oldfd,const char *oldname,int newfd,const char *newname);
//返回：若成功，返回0，若出错，返回-1
```

* oldname是文件而不是目录，为该文件或符号链接重命名
  - newname已存在

  ### 读目录
  
  * 对某个目录具有访问权限的任一用户都可以读该目录，但是，只有内核可以写目录

```c
#include <dirent.h>

struct dirent {
  ino_t d_ino; /* i-node number */
  char d_name[]; /* null-terminated filename */
}
DIR *opendir(const char *pathname);
DIR *fdopendir(int fd);
//返回：成功，返回指针，失败，返回null
struct dirent *readdir(DIR *dp);
//返回：成功，范湖指针，出错，返回null
void rewinddir(DIR *dp);
//将一个目录设置到目录列表的起始位置
int closedir(DIR *dp);
//返回：若成功，返回0，若出错，返回-1
long telldir(DIR *dp);
//返回值：与dp关联的目录中的当前位置
void seekdir(DIR *dp,long loc);
```

[代码](ftwo.c)

### 函数chdir、fchdir和getcwd
* 当前工作目录是进程的一个属性，起始目录是登录名的一个属性
```c
#include <unistd.h>
int chdir(const char *pathname);
int fchdir(int fd); 
//返回值：成 0 错 -1

char *getcwd(char *buf,size_t size);
//返回：成功 buf,出错，null
//buf必须足够长容纳绝对路径名再加一个终止null字节
//跟随符号链接
```
* 通过 (..) 找到其上一级目录，然后读其目录项，直到该目录项中的i节点编号与工作目录i节点编号相同，这样地就找到了其对应的文件名

### 设备特殊文件
* 每个文件系统所在的存储设备都由其主、次设备号表示
* 主设备号标识设备驱动程序，有时编码为与其通信的外设板
* 次设备号标识特定的子设备
* 只有字特殊文件和块特殊文件才有st_rdev值，包含实际设备的设备号

![quanxian](../../image/quanxian.png)


### du 和 df
* du 显示目录或文件的大小
* df 显示目前在Linux系统上的文件系统的磁盘使用情况统计
* awk [-F field-separator] 'commands' input-file(s)  
  awk工作流程是这样的：读入有'\n'换行符分割的一条记录，然后将记录按指定的域分隔符划分域，填充域，$0则表示所有域,$1表示第一个域,$n表示第n个域。默认域分隔符是"空白键" 或 "[tab]键".
```s
du -h --max-depth=1  
df -h 
du --max-depth=1 | sort -n | awk 'BEGIN {OFMT = "%.0f"} {print $1/1024,"MB", $2}'
#OFMT 输出格式为数字
tar -zcvf dest sour  
/*
-A或--catenate：新增文件到以存在的备份文件；
-B：设置区块大小；
-c或--create：建立新的备份文件；
-C <目录>：这个选项用在解压缩，若要在特定目录解压缩，可以使用这个选项。
-d：记录文件的差别；
-x或--extract或--get：从备份文件中还原文件；
-t或--list：列出备份文件的内容；
-z或--gzip或--ungzip：通过gzip指令处理备份文件；
-Z或--compress或--uncompress：通过compress指令处理备份文件；
-f<备份文件>或--file=<备份文件>：指定备份文件；
-v或--verbose：显示指令执行过程；
-r：添加文件到已经压缩的文件；
-u：添加改变了和现有的文件到已经存在的压缩文件；
-j：支持bzip2解压文件；
-v：显示操作过程；
-l：文件系统边界设置；
-k：保留原有文件不覆盖；
-m：保留文件不被覆盖；
-w：确认压缩文件的正确性；
-p或--same-permissions：用原来的文件权限还原文件；
-P或--absolute-names：文件名使用绝对名称，不移除文件名称前的“/”号；
-N <日期格式> 或 --newer=<日期时间>：只将较指定日期更新的文件保存到备份文件里；
--exclude=<范本样式>：排除符合范本样式的文件。
*/
```

## 习题
4.8 du需要文件名，不计算将被删除但任然被占用的文件，df查看文件系统中实际可用的空闲空间
4.11 [codes](ftwo.c)
4.12 chroot只能由超级用户执行，一旦更改了一个进程的根，该进程及其后代进程就再也不能恢复至原来的根
4.14 finger 命令可以让使用者查询一些其他使用者的资料
4.16 [codes](deptho.c)
4.17 /dev 目录关闭了一般用户的写访问权限，以防止普通用户删除目录中的文件名,unlink失败 [codes](dev_fdo.c)