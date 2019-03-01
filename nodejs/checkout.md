## <center>CHECKOUT</center>
### NAME
git-checkout - 转换分支或者恢复工作树文件
### 概述
```sh
git checkout [-q] [-f] [-m] [<branch>]
git checkout [-q] [-f] [-m] --detach [<branch>]
git checkout [-q] [-f] [-m] [--detach] <commit>
git checkout [-q] [-f] [-m] [[-b|-B|--orphan] <new_branch>] [<start_point>]
git checkout [-f|--ours|--theirs|-m|--conflict=<style>] [<tree-ish>] [--] <paths>…​
git checkout [<tree-ish>] [--] <pathspec>…​
git checkout (-p|--patch) [<tree-ish>] [--] [<paths>…​]
```
### 描述
更新工作树中的文件以匹配索引或指定树中的版本，如果没有给出路径，git checkout也会更新`HEAD`以将指定的分支设置为当前分支。

#### *git checkout <branch>*
更改分支，保留对工作树中文件的本地修改以便可以提交。
如果找不到<branch>但是在一个具有匹配名称的远程（称为<remote>）中确实存在跟踪分支，则视为等效于
```sh
$ git checkout -b <branch> --track <remote>/<branch>
```
你可以省略<branch>，在这种情况下，命令退化为“检查当前分支”，这是一个带有相当昂贵的副作用的美化无操作，只显示当前分支的跟踪信息（如果存在）。