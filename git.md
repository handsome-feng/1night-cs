### Git 常用命令
git checkout -b <branch-name>

git remote -v
git remote add origin-gitlab git@salsa.debian.org:handsome_feng-guest/ukui-session-manager.git
git push origin-gitlab debian:master

git cherry-pick <commit-id>
git cherry-pick <start-commit-id>..<end-commit-id>

git submodule update

git revert <commit-id>



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