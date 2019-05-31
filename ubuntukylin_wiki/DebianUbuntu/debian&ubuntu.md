## 通用

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



## Debian

### The experimental repository

```
deb http://deb.debian.org/debian experimental main
apt-get update
apt-get -t experimental install packagename

//listing all packages installed from experimental
aptitude search ~S~i~Aexperimental
```



### Debian version numbering

 The format is: [epoch:]upstream_version[-debian_revision]

The three components here are:

 * epoch
This is a single (generally small) unsigned integer. It may be omitted, in which case zero is assumed. If it is omitted then the upstream_version may not contain any colons. It is provided to allow mistakes in the version numbers of older versions of a package, and also a package's previous version numbering schemes, to be left behind.
* upstream_version
This is the main part of the version number. It is usually the version number of the original ("upstream") package from which the .deb file has been made, if this is applicable. Usually this will be in the same format as that specified by the upstream author(s); however, it may need to be reformatted to fit into the package management system's format and comparison scheme.
The comparison behavior of the package management system with respect to the upstream_version is described below. The upstream_version portion of the version number is mandatory.
The upstream_version may contain only alphanumerics[36] and the characters "." (full stop), "+" (plus), "-" (hyphen), ":" (colon), "~" (tilde) and should start with a digit. If there is no debian_revision then hyphens are not allowed; if there is no epoch then colons are not allowed.
* debian_revision
This part of the version number specifies the version of the Debian package based on the upstream version. It may contain only alphanumerics and the characters "." (full stop), "+" (plus), "~" (tilde) and is compared in the same way as the upstream_version is.
It is optional; if it isn't present then the upstream_version may not contain a hyphen. This format represents the case where a piece of software was written specifically to be a Debian package, where the Debian package source must always be identical to the pristine source and therefore no revision indication is required.
It is conventional to restart the debian_revision at 1 each time the upstream_version is increased.
The package management system will break the version number apart at the last hyphen in the string (if there is one) to determine the upstream_version and debian_revision. The absence of a debian_revision is equivalent to a debian_revision of 0.
* Comparison
When comparing two version numbers, first the epoch of each are compared, then the upstream_version if epoch is equal, and then debian_revision if upstream_version is also equal. epoch is compared numerically. The upstream_version and debian_revision parts are compared by the package management system using the following algorithm:
The strings are compared from left to right.
First the initial part of each string consisting entirely of non-digit characters is determined. These two parts (one of which may be empty) are compared lexically. If a difference is found it is returned. The lexical comparison is a comparison of ASCII values modified so that all the letters sort earlier than all the non-letters and so that a tilde sorts before anything, even the end of a part. For example, the following parts are in sorted order from earliest to latest: ~~, ~~a, ~, the empty part, a.
Then the initial part of the remainder of each string which consists entirely of digit characters is determined. The numerical values of these two parts are compared, and any difference found is returned as the result of the comparison. For these purposes an empty string (which can only occur at the end of one or both version strings being compared) counts as zero.
These two steps (comparing and removing initial non-digit strings and initial digit strings) are repeated until a difference is found or both strings are exhausted.
Note that the purpose of epochs is to allow us to leave behind mistakes in version numbering, and to cope with situations where the version numbering scheme changes. It is not intended to cope with version numbers containing strings of letters which the package management system cannot interpret (such as ALPHA or pre-), or with silly orderings.

ubuntu will indicate that the package has been built specifically for Ubuntu. The alpha and build strings don't seem to have any particular meaning, but dfsg refers to a package that has been modified for compliance with the Debian Free Software Guidelines.



### 安装命令提示器

sudo apt install command-not-found