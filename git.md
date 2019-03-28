## GIT

### 错误解决方案
* `remote: HTTP Basic: Access denied`
```
   git config --system --unset credential.helper
```

### git 配置
 |文件|环境|描述
 |------|----|----
 |/etc/gitconfig|系统所有用户|<code>git config --system<code>
 |~/.gitconfig|用户目录|<code>git config --global<code>
 |.git/config|项目目录|<code>git config<code>

### 工作流程
  - commit 提交
  - 克隆 Git 资源作为工作目录。 `git clone <url> [目录]`
  - 在克隆的资源上添加或修改文件。
  - 如果其他人修改了，你可以更新资源。
  - 在提交前查看修改。
  - 提交修改。
  - 在修改完成后，如果发现错误，可以撤回提交并再次修改并提交。
  - ![工作流程](/image/git-process.png)

### Git 工作区、暂存区和版本库
  - 工作区: 就是你在电脑里能看到的目录。
  - 暂存区: 英文叫stage, 或index。一般存放在 ".git目录下" 下的index文件（.git/index）中，所以我们把暂存区有时也叫作索引（index）。
  - 版本库:工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。dev/master
  ![关系](/image/git-stage.jpg)
  - 图片中的命令

### up
 |命令|作用|提示
 |----|----|----
 |git add|工作区->暂存区Obejct_Id<->对象库Object|目录和文件
 |git commit|暂存区 ->版本库(对象库)|目录树
 |git reset HEAD|master目录树->暂存区目录树|目录树
 |git rm --cached`<file>`|删除暂存区文件|文件
 |git checkout .|暂存区->工作区|文件
 |git checkout --`<file>`|暂存区->工作区|文件
 |git checkout HEAD .|master ->暂存区->工作区|文件
 |git checkout HEAD `<file>`|master ->暂存区->工作区|`<file>`文件
### ohter
 |命令|作用|其他
 |----|----|----
 |git config --list| 列出已有的配置信息|vim ~/.gitconfig
 |git init| 初始化git仓库，根目录生成.git目录|
 |git clone `<repo><directory>`|克隆repo仓库到本地目录directory|
 |git status|查看项目的当前状态|-s 更改的文件
 |git add .|添加当前项目的所有文件到暂存区| A add M modified
 |git diff|查看执行git status的结果的详细信息|尚未缓存的改动
 |git diff --cached| 查看已经缓存的改动
 |git diff HEAD|查看已缓存的与未缓存的所有改动|
 |git diff --stat|显示摘要而非整个diff
 |git commit -am '提交描述'|git add 和 git commit - m ''|
 |git rm `<file>`|删除文件| -f 强制删除，包括暂存区(在删除前修改并保存到暂存区)
 |git rm --cached `<file>`|从暂存区删除，任保留在工作目录中|
 |git rm -r \*| 递归删除整个目录的所有子目录和文件
 |git mv|移动或重命名一个文件、目录、软链接 | `git mv a a.md`
 |git branch|列出你在本地的分支
 |git branch (branchname)|创建分支|
 |git branch -b (branchname)|创建新分支并立即切换到该分支
 |git branch -d (branchname)|删除分支
 |git checkout (branchname)|切换分支命令|替换的时候，用该分支最后提交的快照替换当前工作目录
 |git merge|合并分支|
 |git merge (branchname)|将该分支合并到当前分支，该分支删除
 |git log|历史记录
 |git log --oneline|历史记录的简洁版本
 |git log||--since --before={3.weeks.age} --after={2010-04-18}
 |git log||----no-merges 隐藏合并提交
 |git tag|打标签| -a 创建一个带注解的标签`git tag -a v1.0`
 |git remote add [shortname] [url]|添加一个新的远程仓库

### 创建远程仓库[参考](http://www.runoob.com/git/git-remote-repo.html)
 生成秘钥
```sh
 ssh-keygen -t rsa -C "youremail@example.com"
```
 验证是否成功
```sh
 ssh -T git@github.com
```
|命令|作用|其他
|---|---|
|git remote|当前配置有哪些远程仓库|
|git remote -v|每个别名的实际链接地址|
|git fetch|从远程仓库下载新分支和数据|然后merge
|git push origin master|推送到远程master分支
|git remote rm [别名]|删除远程仓库

### linux上的git命令
1. apt-get install git
2.
```
  git config --global user.name "wangsenyan"
  git config --global user.email "2633600702@qq.com"
  git init ÏîÄ¿Ãû³Æ
  gedit README
  gedit sample
  git add sample
  git commit -m "create a git project" //commitµ½»º´æÇø£¬²¢Ìí¼Ó¼ò½é
  git remote add origin https://github.com/wangsenyan/myGitTest.git
  git push origin master //ÉÏ´«
  git clone ¿ËÂ¡
  git pull origin master
```
3. ssh-keygen -C "2633600702@qq.com" -t ras
   passphrase -wsy12140322150232
4. ¸´ÖÆ.pubÏÂµÄ¹«Ô¿µ½githubÖÐ£¬setting-ssh and  gpg keys-new ssh key
5. ssh -T git@github.com ²âÊÔÅäÖÃ

6. add-apt-repository ppa:webupd8team/sublime-text-3 Ìí¼ÓppaÂ·¾¶
  tar -xjvf name.tar.bz2
7.
```
  sudo apt-get upgrade ¸üÐÂÒÑ°²×°µÄ°ü
  sudo apt-get install pkgname ¸üÐÂÌØ¶¨Èí¼þ
  dpkg -L xxxx²é¿´Èí¼þ°²×°Î»ÖÃ
  dpkg -l |grep filename ²é¿´Èí¼þÊÇ·ñ°²×°
```
8. pscp -i alpahcoding-test.ppk third-party-login.js     root@192.168.5.3:/root/alphacoding/config

9. git clone -b <分支名字> <地址>
10. *创建自己的项目*
```
   切换到自己的项目目录，切记.gitignore 添加node_modules等
   git add . 
     //fatal: Not a git repository (or any of the parent directories): .git
   git init
   git commit -m '描述'
   //将origin设置为远程仓库路径，包括所有分支
   git remote add origin https://git.coding.net/wangsenyan/stormshop.git
   //将本地master和远程master分支对应
   git branch --set-upstream-to=origin/master
   git push -u origin master  

```

### 管理多个ssh key

* 生成多个ssh key `ssh-keygen -C "2633600702@qq.com" -t ras` 或者  `ssh-keygen  -t ras`
* 配置 `~/.ssh/config`

```
  
Host git.apicloud.com
    HostName  git.apicloud.com
    User git
    IdentityFile ~\.ssh\id_rsa_gitlab
Host github.com
    HostName  github.com
    User git
    IdentityFile ~\.ssh\id_rsa_github
```
* 将公钥 `.pub`结尾的公钥放服务器

### 重要的指令
*  `git status` - 列出当前目录所有还没有被git管理的文件和被git管理且被修改还未提交(git commit)的文件
* `git reset --hard commit_id` - 回退到commit_id处，取消commit,代码也消失  
  没有--hard 保留工作区修改

* `git reset HEAD a ` 只是add,git add 和 git commit 之间的修改取消
* `git checkout a` - 撤销对文件a的修改,没有**add**的修改

* 已经提交
  `git reset HEAD^` - 回退到工作区
  `git checkout a` - 撤销工作区修改

### 强制回滚
```sh
git commit 版本号  ##本地回滚
git push -f origin develop ## 远程回滚
```
### 暂存
```sh
git stash ## 暂存
git stash apply stash@{1} ##取出暂存，但是没有删除
git stash clear ## 删除暂存
git stash list ## 列出暂存文件
```

### log
```sh
git log --stat ##显示log 同时又修改过的文件
git log --author=username  ## 显示某人的某个文件的log
git show commitId ## 显示该commit的log
git log --pretty=oneline filename ## 某文件的commit
git log --graph  --reverse #查看历史中什么时候出现了分支、合并  ##逆向显示
git log --since 2018-8-21 --before={3.weeks.age} --after={2010-04-18} 
git log -p -2 ##查询最近两次提交，-p代表内容差异
git log -p ##按补丁格式显示每个更新之间的差异。
git log --shortstat ##只显示 --stat 中最后的行数修改添加移除统计。
git log --name-only ##仅在提交信息后显示已修改的文件清单。
git log --name-status ##显示新增、修改、删除的文件清单。
git log --abbrev-commit ##仅显示 SHA-1 的前几个字符，而非所有的 40 个字符。
git log --relative-date ##使用较短的相对时间显示（比如，“2 weeks ago”）。
git log --graph ##显示 ASCII 图形表示的分支合并历史。
git log --pretty ##使用其他格式显示历史提交信息。可用的选项包括 oneline，short，full，fuller 和 format（后跟指定格式）。```
git log -(n) ##仅显示最近的 n 条提交
git log --since, --after ##仅显示指定时间之后的提交。
git log --until, --before ##仅显示指定时间之前的提交。
git log --author ##仅显示指定作者相关的提交。
git log --committer ##仅显示指定提交者相关的提交。
git log --grep ##仅显示含指定关键字的提交
git log -S ##仅显示添加或移除了某个关键字的提交
```

### 查看已暂存和为暂存的修改
```sh
git diff ## 工作区修改但未暂存和暂存区域快照之间的差异
git diff --staged|--cached ## 已暂存的将要下次提交你的内容
```

### 撤销操作
```sh
git commit -amend ##将暂存区的文件提交，覆盖上次的提交，合并多次提交

git reset HEAD <file> ## 只会撤销暂存区 --hard 工作区也取消
git checkout -- <file> ## 撤销工作区的修改
```

### checkout,reset,revert
|命令|作用域|常用情景
|---|------|-------
|git reset |提交层面|  在私有分支上舍弃一些没有提交的更改
|git reset |文件层面|  将文件从缓存区中移除
|git checkout  |提交层面 | 切换分支或查看旧版本
|git checkout  |文件层面 | 舍弃工作目录中的更改
|git revert  |提交层面  |在公共分支上回滚更改
|git revert  |文件层面  |然而并没有

### commit 包含四个部分 放在`object`
- 工作目录快照的哈希
- 提交的说明信息
- 提交者的信息
- 父提交的哈希值
- `git cherry -v` 查看未传送到远程代码库的提交描述/说明

### **.gitignore**
* 所有空行或者以 ＃ 开头的行都会被 Git 忽略。
* 可以使用标准的 glob 模式匹配。
* 匹配模式可以以（/）开头防止递归。
* 匹配模式可以以（/）结尾指定目录。
* 要忽略指定模式以外的文件或目录，可以在模式前加上惊叹号（!）取反。
```txt
所谓的 glob 模式是指 shell 所使用的简化了的正则表达式。 星号（*）匹配零个或多个任意字符；[abc] 匹配任何一个列在方括号中的字符（这个例子要么匹配一个 a，要么匹配一个 b，要么匹配一个 c）；问号（?）只匹配一个任意字符；如果在方括号中使用短划线分隔两个字符，表示所有在这两个字符范围内的都可以匹配（比如 [0-9] 表示匹配所有 0 到 9 的数字）。 使用两个星号（*) 表示匹配任意中间目录，比如`a/**/z` 可以匹配 a/z, a/b/z 或 `a/b/c/z`等。
```

```txt
#               表示此为注释,将被Git忽略
*.a             表示忽略所有 .a 结尾的文件
!lib.a          表示但lib.a除外
/TODO           表示仅仅忽略项目根目录下的 TODO 文件，不包括 subdir/TODO
build/          表示忽略 build/目录下的所有文件，过滤整个build文件夹；
doc/*.txt       表示会忽略doc/notes.txt但不包括 doc/server/arch.txt
 
bin/:           表示忽略当前路径下的bin文件夹，该文件夹下的所有内容都会被忽略，不忽略 bin 文件
/bin:           表示忽略根目录下的bin文件
/*.c:           表示忽略cat.c，不忽略 build/cat.c
debug/*.obj:    表示忽略debug/io.obj，不忽略 debug/common/io.obj和tools/debug/io.obj
**/foo:         表示忽略/foo,a/foo,a/b/foo等
a/**/b:         表示忽略a/b, a/x/b,a/x/y/b等
!/bin/run.sh    表示不忽略bin目录下的run.sh文件
*.log:          表示忽略所有 .log 文件
config.php:     表示忽略当前路径的 config.php 文件
 
/mtk/           表示过滤整个文件夹
*.zip           表示过滤所有.zip文件
/mtk/do.c       表示过滤某个具体文件
```
### 添加远程仓库
```sh
git origin
git remote add <shortname> <url> ##shortname和origin类似
git remote -v
git fetch [remote-name] ## 从远程仓库获取数据
git remote show [origin] ## 查看仓库的更多信息
git remote rename ##修改远程仓库的简写名
git remote remove [remove-name] ##移除远程分支
```

### 从某个分支更新当前分支
从B更新A
```sh
git checkout A ##切换到需要更新的分支
git merge B ## 将A的修改更新到B

# 将B上的b.md 文件改动合并到A分支上
git checkout A
git checkout --path B b.md
git reset --hard origin/master ## ???

# 有效方法
## 在前一个分支commit B
## 在另一个分支 
git checkout B path/file ## 从另一个分支检出文件
git commit -m ''
```