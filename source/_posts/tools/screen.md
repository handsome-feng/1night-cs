screen命令可以实现当前窗口与任务分离，我们即使离线了，服务器仍在后台运行任务。当我们重新登录服务器，可以读取窗口线程，重新连接任务窗口。

创建新窗口

```shell
screen
screen -S name
screen command
```

分离

ctrl a+d

screen -d name

恢复

screen -ls

screen -r

杀死

ctrl a+k

ctrl a ，输入quit



清理窗口

screen -wipe