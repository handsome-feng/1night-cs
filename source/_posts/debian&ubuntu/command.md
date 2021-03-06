---
title: common command
---



## 查找

### find

使用格式如下：

$ find <指定目录> <指定条件> <指定动作>

　　- <指定目录>： 所要搜索的目录及其所有子目录。默认为当前目录。

　　- <指定条件>： 所要搜索的文件的特征。

　　- <指定动作>： 对搜索结果进行特定的处理。

使用实例：

　　$ find . -name 'test*'

搜索当前目录（含子目录，以下同）中，所有文件名以test开头的文件。

　　$ find . -name 'test*' -ls

搜索当前目录中，所有文件名以test开头的文件，并显示它们的详细信息。

　　$ find . -type f -mmin -10

搜索当前目录中，所有过去10分钟中更新过的普通文件。如果不加-type f参数，则搜索普通文件+特殊文件+目录。

NOTE: name后面的名字如果包含“\*”，而且不加引号，find会做这样的处理：
先看当前工作目录（子目录不算）中有没有省略“*”后剩下的文件名，如果能找到完全匹配的文件，就用这个名字匹配。如果找不到，就按原来的通配符匹配。

因为在“/”下没有直接能完全匹配的文件名，第一次就是按"*bak\*.py"搜索的。
在/home下有一个这样的文件名，所以按“bak.py”搜索的。

如果name后接的名字加上双引号，就是强制用通配符匹配。

### locate

它不搜索具体目录，而是搜索一个数据库（/var/lib/locatedb），这个数据库中含有本地所有文件信息。Linux系统自动创建这个数据库，并且每天自动更新一次，所以使用locate命令查不到最新变动过的文件。为了避免这种情况，可以在使用locate之前，先使用updatedb命令，手动更新数据库。

locate命令的使用实例：

　　$ locate /etc/sh

搜索etc目录下所有以sh开头的文件。

　　$ locate ~/m

搜索用户主目录下，所有以m开头的文件。

　　$ locate -i ~/m

搜索用户主目录下，所有以m开头的文件，并且忽略大小写。

### whereis

whereis命令只能用于程序名的搜索，而且只搜索二进制文件（参数-b）、man说明文件（参数-m）和源代码文件（参数-s）。如果省略参数，则返回所有信息。

whereis命令的使用实例：

　　$ whereis grep

### which

which命令的作用是，在PATH变量指定的路径中，搜索某个系统命令的位置，并且返回第一个搜索结果。也就是说，使用which命令，就可以看到某个系统命令是否存在，以及执行的到底是哪一个位置的命令。

which命令的使用实例：

　　$ which grep

### type

type命令其实不能算查找命令，它是用来区分某个命令到底是由shell自带的，还是由shell外部的独立二进制文件提供的。如果一个命令是外部命令，那么使用-p参数，会显示该命令的路径，相当于which命令。

type命令的使用实例：

　　$ type cd

系统会提示，cd是shell的自带命令（build-in）。

　　$ type grep

系统会提示，grep是一个外部命令，并显示该命令的路径。

　　$ type -p grep

加上-p参数后，就相当于which命令。

## 包管理

#### dpkg

dpkg -x

dpkg -e

dpkg-deb -b

### 设备信息

sudo /sbin/hdparm -i /dev/sda | grep -i serialno #硬盘序列号

### X相关

#### xwininfo

#### xprop

#### xkill

#### xdotool



用户管理：

adduser feng

usermod -aG sudo feng



