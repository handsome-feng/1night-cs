---
title: Gdb
---



### gdb调试常用命令

```
$ b main            //设置断点
$ break [where] if [condition]  //条件断点
$ info b            //显示断点
$ delte 3           //删除断点，基于断点号
$ delete 1-3
$ clear mythrad1    //删除断点基于文件或行号
$ clear myThread.c :mythread1
$ step              //单步调试，跟踪
$ bt                //查看当前所有栈信息
$ frame             //查看当前栈（当前执行的源码在哪一行）
$ info locals       //显示所有局部变量
$ print xx          //显示变量xx的值 
$ watch n           //监控n的值，有变化时显示出来
$ file /home/feng/a.out //载入新的symbol table
$ attach pid        //附到一个已经在跑的进程上(需要root权限)
$ info inferiors    //查询正在调试的进程
$ dir path/to/source  //加载源文件
$ set args          //设置命令行参数
$ set $i = 0        // 设置变量
```

### 多线程调试

```
$ info threads  //查看当前进程的线程
$ thread <ID>  //切换调试的线程为指定ID的线程
$ break file.c:100 thread all  //为所有经过这里的线程设置断点
$ set scheduler-locking off|on|step
off: 不锁定任何线程，默认
on:  只有当前线程会执行
step: 单步的时候，除了next过一个函数的情况以外，只有当前线程会执行
```

### 多进程调试
```
$ set follow-fork-mode parent|child
$ set detach-on-fork on|off  //调试多进程
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

### 调试宏

```
// 编译时加上-ggdb3
$ info marco
$ marco  //查看宏展开
```

