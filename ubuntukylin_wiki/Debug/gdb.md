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
$ dir path/to/source
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