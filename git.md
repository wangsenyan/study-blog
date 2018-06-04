
## GIT
### git 配置
 |文件|环境|描述
 |------|----|----
 |/etc/gitconfig|系统所有用户|<code>git config --system<code>
 |~/.gitconfig|用户目录|<code>git config --global<code>
 |.git/config|项目目录|<code>git config<code>
### 工作流程
 - 克隆 Git 资源作为工作目录。
 - 在克隆的资源上添加或修改文件。
 - 如果其他人修改了，你可以更新资源。
 - 在提交前查看修改。
 - 提交修改。
 - 在修改完成后，如果发现错误，可以撤回提交并再次修改并提交。
 - ![工作流程](git-process.png)
### Git 工作区、暂存区和版本库
 - 工作区: 就是你在电脑里能看到的目录。
 - 暂存区: 英文叫stage, 或index。一般存放在 ".git目录下" 下的index文件（.git/index）中，所以我们把暂存区有时也叫作索引（index）。
 - 版本库:工作区有一个隐藏目录.git，这个不算工作区，而是Git的版本库。dev/master
   ![关系](git-stage.jpg)
 - 解释

  |命令|作用|提示
  |----|----|----
  |git add|工作区->暂存区Obejct_Id<->对象库Object|目录和文件
  |git commit|暂存区 ->版本库(对象库)|目录树
  |git reset HEAD|master目录树->暂存区目录树|目录树
  |git rm --cached`<file>`|删除暂存区文件|文件
  |git checkout .|暂存区->工作区|文件
  |git checkout --`<file>`|暂存区->工作区|文件
  |git checkout HEAD .|master ->暂存区->工作区|文件
  |git checkout HEAD `<file>`|master ->暂存区->工作区|文件`<file>`
  
### 基本命令
 |命令|作用|其他
 |-----------------|-----------------| 
 |git config --list| 列出已有的配置信息| vim ~/.gitconfig
 |git init| 初始化git仓库，根目录生成.git目录
 |git clone `<repo><directory>`|克隆repo仓库到本地目录directory|
 |git status|查看项目的当前状态|-s 更改的文件
 |git add .|添加当前项目的所有文件到暂存区| A add M modified
 |git diff|查看执行git status的结果的详细信息|尚未缓存的改动
 |git diff --cached| 查看已经缓存的改动
 |git diff HEAD|查看已缓存的与未缓存的所有改动|
 |git diff --stat|显示摘要而非整个diff
 |git commit -am '提交描述'|git add 和 git commit - m ''|
 |git rm `<file>`|删除文件| -f 强制删除，包括暂存区
 |git rm --cached `<file>`|从暂存区删除，任保留在工作目录中|
 |git rm -r *| 递归删除整个目录的所有子目录和文件
 |git mv|移动或重命名一个文件、目录、软链接 | `git mv a a.md`
 |git branch|列出你在本地的分支
 |git branch (branchname)|创建分支|
 |git branch -b (branchname)|创建新分支并立即切换到该分支
 |git branch -d (branchname)|删除分支
 |git checkout (branchname)|切换分支命令| 替换的时候，用该分支最后提交的快照替换当前工作目录
 |git merge|合并分支|
 |git merge (branchname)|将该分支合并到当前分支，该分支删除
 |git log|历史记录
 |git log --oneline|历史记录的简洁版本
 |git log --graph|查看历史中什么时候出现了分支、合并|--reverse 逆向显示
 |git log||--author = wangsenyan
 |git log||--since --before={3.weeks.age} --after={2010-04-18}
 |git log||----no-merges 隐藏合并提交
 |git tag|打标签| -a 创建一个带注解的标签`git tag -a v1.0`
 |git remote add [shortname] [url]|添加一个新的远程仓库|
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
10. 创建自己的项目
```
   切换到自己的项目目录，切记.gitignore 添加node_modules等
   git add . 
     //fatal: Not a git repository (or any of the parent directories): .git
   git init
   git commit -m '描述'
   git remote add origin https://git.coding.net/wangsenyan/stormshop.git
   git push -u origin master  
```
