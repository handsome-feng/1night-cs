---
title: Ubuntu
---



本地准备工作:

~/.bashrc:

```
export DEBFULLNAME="handsome_feng"
export DEBEMAIL="jianfengli@ubuntukylin.com"
alias mylintian="lintian -i -EvIL +pedantic --verbose"
alias mylicensecheck="licensecheck -r . | grep -v 'UNKNOWN'"
```
~/.



## Ubuntu

[镜像下载](https://cdimage.ubuntu.com)
[Mirros](https://launchpad.net/ubuntu/+archivemirrors)
[Packages Search](http://packages.ubuntu.com/)
[Source](https://launchpad.net/ubuntu/+source/youker-assistant)
[Testing tracker](http://iso.qa.ubuntu.com/qatracker)
[Autopkgtest](http://autopkgtest.ubuntu.com/)

#### seeds

https://wiki.ubuntu.com/UbuntuStudio/Seeds
https://wiki.ubuntu.com/SeedManagement
https://wiki.ubuntu.com/Germinate
https://wiki.ubuntu.com/ProposedMigration
http://people.canonical.com/~ubuntu-archive/seeds/
http://people.canonical.com/~ubuntu-archive/germinate-output/
[Ubuntu中文WIKI](http://wiki.ubuntu.org.cn/)
[Ubuntu桌面指南](https://help.ubuntu.com/lts/ubuntu-help/index.html)
[Ubuntu认证硬件](https://certification.ubuntu.com/certification/desktop/)
Debian新维护人员手册
https://www.debian.org/doc/manuals/maint-guide/index.zh-cn.html
https://www.debian.org/doc/manuals/maint-guide/
Debian开发人员手册: https://www.debian.org/doc/manuals/developers-reference/
Debian打包指南:
https://www.debian.org/doc/manuals/packaging-tutorial/packaging-tutorial.en.pdf
https://www.debian.org/doc/manuals/packaging-tutorial/packaging-tutorial.zh_TW.pdf
http://packaging.ubuntu.com/html/
[Debian Policy Manual]( https://www.debian.org/doc/debian-policy/)
[lintian tags](https://lintian.debian.org/tags/)
[Daily build log](http://people.canonical.com/~ubuntu-archive/cd-build-logs/)
[Ubuntu Autopkgtest Results](http://autopkgtest.ubuntu.com/)
TechnicalBoard:
https://wiki.ubuntu.com/TechnicalBoard
https://wiki.ubuntu.com/TechnicalBoardAgenda
excuses(proposed迁移): http://people.canonical.com/~ubuntu-archive/proposed-migration/update_excuses.html
packagesets:        https://people.canonical.com/~ubuntu-archive/packagesets/bionic/
License Information: https://ftp-master.debian.org/licenses/
DeveloperMembershipBoard: https://wiki.ubuntu.com/DeveloperMembershipBoard
Ubuntu Developers: https://wiki.ubuntu.com/UbuntuDevelopers/TeamDelegation
Bugs/EmailInterface: https://help.launchpad.net/Bugs/EmailInterface
Live filesystem information: https://launchpad.net/~ubuntu-cdimage/+livefs/ubuntu/cosmic/ubuntukylin/
Debian bug-tracking system: https://debian-administration.org/article/436/Using_the_Debian_bug-tracking_system
debian archive:      https://salsa.debian.org/handsome_feng-guest
Debian new and byhand pakcages: https://ftp-master.debian.org/new.html
[Irc logs](https://irclogs.ubuntu.com)
[Release](https://wiki.ubuntu.com/Releases)
[changelogs]( http://changelogs.ubuntu.com/)

### 常用流程

#### SponsorshipProcess

https://wiki.ubuntu.com/SponsorshipProcess

#### FFe

https://wiki.ubuntu.com/FreezeExceptionProcess

#### syncRequestProcess

https://wiki.ubuntu.com/SyncRequestProcess

### 打包工具

SBuild:         https://wiki.ubuntu.com/SimpleSbuil
DebDiff:        https://wiki.ubuntu.com/UbuntuStudio/DebDiff

在线工具

在线贴图工具:    https://imgur.com/
在线贴文字工具:  https://paste.ubuntu.com/

在线gif制作:     http://www.soogif.com/
在线流程图:      https://www.processon.com/diagrams 

实用工具

1. Youcompleteme
2. gollum
3. irssi
4. goldendict
5. Beyond Compare
6. SS
7. xdotool

X window

- 查看快捷键被谁捕获

```shell
xdotool keydown "shift+Print"; xdotool key "XF86LogGrabInfo"; xdotool keyup "Print"; sleep 1; xdotool keyup "shift"; tail /var/log/Xorg.0.log
```

- 其他

1. ANSI控制码: http://ascii-table.com/ansi-escape-sequences.php



