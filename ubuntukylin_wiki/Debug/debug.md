

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

### 察看多线程所有线程ID

`$ ps -T`
`$ top -H -p <pid>`　　//让top输出某个特定进程并检查该进程内运行的线程状况
`$ htop`



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

