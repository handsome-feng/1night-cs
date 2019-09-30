---
title: Debugging Procedures
---



<https://wiki.ubuntu.com/DebuggingProcedures>

### Info for the BugSquad

1. This will create a minimal Precise system:

   ```
   sudo mkdir -p /chroots/precise
   sudo debootstrap precise /chroots/precise/
   ```

2. Now change into this minimal precise system:

   ```
   sudo chroot /chroots/precise
   ```

3. Edit /etc/apt/sources/list and add all the repositories you need, including the ddeb repository.

4. Execute the following in a terminal:

   ```
   sudo apt-get update; sudo apt-get install gdb apport
   ```

5. use apport-retrace as you're used to.



### Compiling with debugging -g option

```shell
./autogen.sh
./configure CFLAGS="-g -O0" #option A
./configure --enable-debug  #option B
```



### Debug Symbol Packages

1. Create an /etc/apt/sources.list.d/ddebs.list by running the following line at a terminal:

   ```shell
   echo "deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse
   deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse
   deb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse" | \
   sudo tee -a /etc/apt/sources.list.d/ddebs.list
   ```

2. Import the debug symbol archive signing key from the Ubuntu server:

   ```shell
   $ sudo apt install ubuntu-dbgsym-keyring   
   $ sudo apt update
   ```

3. Install debug packages

   ```shell
   $ sudo apt install xxx-dbgsym
   ```

4. Automatic resolution

   ```shell
   #!/bin/bash -x
   progname=`basename "$0"`
   
   explain() {
       cat << EOF
   Usage: $progname [-adt] [-p pid] | [exectable]
   
   You must specify a pid (-p) or an executable name/path.
   
   This scripts list the dbug symbols packages you need to install for a complete dump of the give executable. Already installed symbols packages are not shown.
   
   Options are:
     -p pid  uses the running process with the given pid to get the list.
                   If specified, you may omit the executable name.
     -a          show all the required symbol packages (not only the not-installed
                   ones)
     -d          prefer XXX-dbg symbol packages over XXX-dbgsym ones
     -t           terse: print the packages names only (no package description).
                   Useful to pass output directly to apt-get install.
   
   NOTE: in some cases $progname may report already installed
   packages. This currently happens with binaries using libpthread.so as
   libc6-i686-dbgsym apparently doesn't contain debug symbols for it.
   
   To examine a running server process by pid, you will need to run this script
   using sudo.
   EOF
       exit -1
   }
   
   all=false
   preferred="dbgsym dbg"
   debug=false
   terse=false
   pid=
   while getopts :adgp:t opt; do
       case $opt in
           a)
               all=true
               ;;
           d)
               preferred="dbg dbgsym"
               ;;
           g)
               debug=true
               ;;
           p)
               pid="$OPTARG"
               binary=$(readlink /proc/$pid/exe)
               [ -z "$binary" ]&& echo "Unable to get binary path for pid $pid" && exit -1
           t)
               terse=true
               ;;
           \?)
               explain
               ;;
       esac
   done
   
   if [ -z "$binary" ]; then
       shift $(( $OPTIND - 1 ))
       [ $# -ne 1 ] && explain
       binary="$1"
       [ ! -x "$binary" -a `basename @"$binary"` = @"$binary" -a -n "`which $binary`" ] && binary=`which $binary`
   fi
   
   find-debug() {
       while read i; do
           for ext in $preferred; do
               i=$(echo "$i"|cut -f 1 -d:) #remove the architecture suffix
               apt-cache search "^$i-$ext\$"
           done |head -1
       done
   }
   
   if [ ! -z "$pid" ]; then
      Args="--pid=$pid"
   else
      Args="$binary"
   fi
   
   echo q| gdb "$Args" | \
   grep 'Reading symbols from '| \
   if $all; then cat; else grep 'no debugging symbols found'; fi | \
   sed -e 's/^Reading symbols from \(.*\)\.\.\.\((\|Reading \).*$/\1/' | \
   while read i; do \
       #dpkg -S "$i" |while read j; do if $debug; then echo '!' $i '-->' $j 1>&2; fi; echo $j; done
       ( if ! dpkg -S "$i" 2>/dev/null; then [ -L "$i" ] && dpkg -S `readlink "$i"`; fi ) | \
       while read j; do if $debug; then echo '!' $i '-->' $j 1>&2; fi; echo $j; done \
   done| sed -e 's/^\(.*\): .*$/\1/' | sort -u | \
   find-debug | if $terse; then sed -e 's/ - .*$//'; else cat; fi |sort -u
   ```

   



### strace

```
$ strace ./a.out    //察看程序在执行什么系统调用
$ strace -p pid     //附到一个已经在跑的进程上，实时观察
```

### mtrace

### valgrind

### Backtrace

Generation

1. Please ensure you have packages with debug symbols installed. You can do this by following the instructions at DebuggingProgramCrash.
2. Make sure the GNU Debugger is installed.
3. sudo apt-get install gdb 
   Start the program under control of gdb via a terminal (some programs run as root, so one would use sudo gdb instead of just gdb below):

```
gdb <program> 2>&1 | tee ~/gdb-<program>.txt
(gdb) handle SIG33 pass nostop noprint
(gdb) set pagination 0
(gdb) run <arguments, if any>
```

4. The program will start. Perform any actions necessary to reproduce the crash. If the program hangs but doesn't crash you can press ctrl+c in gdb while the program is frozen and then continue with the next step.
   Retrieve a backtrace:

```
(gdb) backtrace full
(gdb) info registers
(gdb) x/16i $pc
(gdb) thread apply all backtrace
(gdb) quit 
```

Attach the complete output from GDB, contained in gdb-<program>.txt, in your bug report. You will find the file in your home directory /home/<username>/.

### 察看进程占用IO命令

只显示有I/O行为的进程

`$ iotop -oP`

查看特定进程　

`$ iotop -p $PID`

展示I/O统计,每秒更新一次

`$ pidstat -d 1` 

查看该进程启动的完整命令行

`$ ps eho command -p $PID`

查看该进程启动时候所在的目录

`$ readlink /proc/$PID/cwd`

查看该进程启动时的完整环境变量

`strings -f /proc/$PID/environ | cut -f2 -d ”`

列出该进程所打开的所有文件:

`$ lsof -p $PID`
　　cwd代表当前目录,这里是/root
　　rtd代表根目录,这里是/
　　txt代表执行的程序,这里是/bin/bash
　　mem代表映射到内存的文件,这里是/lib/libc-2.7.so等动态链接库
　　TYPE一栏表示文件/目录的类型,DIR代表目录,REG代表普通文件,CHR代表字符设备.
列出该进程所打开的网络连接:

`$ netstat -pan | grep $PID`

查看文件被哪个i进程占用

`$ sudo fuser -v path/to/file`

`$ lsof path/to/file`

### 察看多线程所有线程ID

`$ ps -T`
`$ top -H -p <pid>`　　//让top输出某个特定进程并检查该进程内运行的线程状况
`$ htop`

### 监控文件

audit

inotifywait

inotifymoniter

### PS

To print a process tree:

```
ps -ejH
ps axjf
```

To get info about threads:

```
ps -eLf
ps axms
```

To get security info:

```
ps -eo euser,ruser,suer,fuser,f,comm,label
ps axZ
ps -eM
```

To see every process running as root (real & effective ID) in user format:

```
ps -U root -u root u
```

To see every process with a user-defined format:

```
ps -eo pid,tid,class,rtprio,ni,pri,psr,pcpu,stat,wchan:14,comm
ps axo stat,euid,ruid,tty,tpgid,sess,pgrp,ppid,pid,pcpu,comm
ps -Ao pid,tt,user,fname,tmout,f,wchan
```

Print only the process IDs of syslogd:

```
ps -C syslogd -o pid=
```

Print only the name of PID 42:

```
ps -q 42 -o comm=
```

