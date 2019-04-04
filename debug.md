### gdb调试

```
$ b main            //设置断点
$ info b            //显示断点
$ delte 3           //删除断点，基于断点号
$ delete 1-3
$ clear mythrad1    //删除断点基于文件或行号
$ clear myThread.c :mythread1
$ info threads      //显示线程
$ thread 2          //切换到线程2
$ set scheduler-locking on //只调试当前线程
$ step              //单步调试，跟踪
$ bt                //查看当前所有栈信息
$ frame             //查看当前栈（当前执行的源码在哪一行）
$ info locals       //显示所有局部变量
$ print xx          //显示变量xx的值 
$ watch n           //监控n的值，有变化时显示出来
$ file /home/feng/a.out //载入新的symbol table
$ attach pid        //附到一个已经在跑的进程上(需要root权限)
$ info inferiors    //查询正在调试的进程
```

```
$ set follow-fork-mode [parent|child] set detach-on-fork [on|off]  //调试多进程
```

| follow-fork-mode | detach-on-fork | 说明                                                 |
| ---------------- | -------------- | ---------------------------------------------------- |
| parent           | on             | 只调试主进程（GDB默认）                              |
| child            | on             | 只调试子进程                                         |
| parent           | off            | 同时调试两个进程，gdb跟主进程，子进程block在fork位置 |
| child            | off            | 同时调试两个进程，gdb跟子进程，主进程block在fork位置 |

set target-async on

set pagination off

set non-stop on

### strace

```
$ strace ./a.out    //察看程序在执行什么系统调用
$ strace -p pid     //附到一个已经在跑的进程上，实时观察
```

### 察看进程占用IO命令

只显示有I/O行为的进程　　　　　`iotop -oP`
查看特定进程　　　　　　　　　　`iotop -p $PID`
展示I/O统计,每秒更新一次　　　　`pidstat -d 1` 
查看该进程启动的完整命令行　　　`ps eho command -p $PID`
查看该进程启动时候所在的目录　　`readlink /proc/$PID/cwd`
查看该进程启动时的完整环境变量　`strings -f /proc/$PID/environ | cut -f2 -d ”`
列出该进程所打开的所有文件:　　　`lsof -p $PID`
　　cwd代表当前目录,这里是/root
　　rtd代表根目录,这里是/
　　txt代表执行的程序,这里是/bin/bash
　　mem代表映射到内存的文件,这里是/lib/libc-2.7.so等动态链接库
　　TYPE一栏表示文件/目录的类型,DIR代表目录,REG代表普通文件,CHR代表字符设备.
列出该进程所打开的网络连接:　　　`netstat -pan | grep $PID`

### 察看多线程所有线程ID

`$ ps -T`
`$ top -H -p <pid>`　　//让top输出某个特定进程并检查该进程内运行的线程状况
`$ htop`