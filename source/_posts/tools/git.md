---
title: Git
---

### 常用命令

```shell
git checkout -b <branch-name>
git remote -v
git remote add origin-gitlab git@salsa.debian.org:handsome_feng-guest/ukui-session-manager.git
git push origin-gitlab debian:master
git cherry-pick <commit-id>
git cherry-pick <start-commit-id>..<end-commit-id>
git submodule update --init
git revert <commit-id>
git reset
```



将本地debian分支推送到远程origin-debian的master分支：

`git push origin-debain debian:master`



删除本地分支：

`git branch -d <branchName>`

删除远程分支：

`git push origin --delete <branchName>`

切换分支：

`git checkout -b debian remotes/origin/debian`

#### 合并某个分支的特定文件：

`git checkout [branch]  [file name]`

#### 合并两个分支

`git remote add new-origin git@github.com:handsome-feng/new.git`

`git merge new-origin/master --allow-unreleated-histories`

#### 删除某个commit

`git rebase -i previous_commit`

### bzr to git

```
cp -pr repo-dir repo-dir_backup                 # Make a backup
cd repo-dir                                     # Change into your dir
git init                                        # Initialise a new git repo
bzr fast-export --plain . | git fast-import     # Do the actual conversion
git co -f master                                # Will reply 'Already on master'
rm -rf .bzr/                                    # Remove the bzr data
```



### Removing files from Git history

`$ java -jar bfg.jar --delete-folders .git --delete-files .git --no-blob-protection my-repo.git`

## git使用代理

```shell
# 设置代理
git config --global http.proxy socks5://127.0.0.1:1080
git config --global https.proxy socks5://127.0.0.1:1080

# 取消代理
git config --global --unset http.proxy
git config --global --unset https.proxy
```

