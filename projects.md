## 项目

### flatpak

基本概念：
**运行时(runtimes)**:
“运行时”提供应用程序所需的基本依赖。有各种各样的“运行时”,比如“Freedesktop运行时”，“GNOME运行时”。“Freedesktop运行时”包含一系列必要的库和服务，包括D-Bus, GLib, PulseAudio, X11和Wayland等。“GNOME运行时”基于“FreeDesktop运行时”，增加了一些GNOME平台相关的库，比如GStreamer,GTK+,GVFS等。必须针对运行时构建每个应用程序，并且必须在主机系统上安装此运行时才能运行应用程序。用户可以同时安装多个不同的运行时，包括不同版本的同一个运行时。

每一个运行时可以看做一个’/usr’ 文件系统，当程序运行时，它的运行时挂载在‘/usr’上。

**捆绑库(Bundled libraries)**
当一个程序需要的依赖不在运行时中，使用捆绑库来绑定这些依赖到程序上。

**SDK(软件开发套件)**
SDK也是一个“运行时”，是用于构建应用程序的特殊类型的运行时，它包含了构建和打包工具（‘devel’ parts），如头文件，编译器和调试器。通常，SDK与“运行时”配对，由应用程序使用。

**扩展(Extensions)**
一个扩展是对于运行时或程序的可选插件，一般用于把translations和debug信息从运行时分离出来，比如, org.freedesktop.Platform.Locale 可以追加到org.freedesktop.Platform运行时上用来添加翻译。

**沙箱（Sandbox）**
使用Flatpak，每个应用程序都是在孤立的环境中构建和运行的。默认情况下，应用程序只能“查看”自身及其“运行时”,访问用户文件，网络，graphics sockets，总线和设备上的子系统必须明确授予权限，访问其他内容（如其他进程）是不允许的。（可以通过Portals机制在沙箱内访问外面系统，比如打印，截图等）

Flatpak主要使用了如下技术：

1. bubblewrap：依赖它作为沙箱的底层实现,限制了应用程序访问操作系统或用户数据的能力，并且提供了非特权用户使用容器的能力。
2. Systemd：将各个subsystem和cgroup树关联并挂载好，为沙箱创建 cgroups。
3. D-Bus, 为应用程序提供高层APIs。
4. 使用Open Container Initiative的OCI格式作为单文件的传输格式，方便传输。
5. 使用OSTree系统用于版本化和分发文件系统树。
6. 使用Appstream元数据，使得Flatpak应用程序在软件中心可以完美呈现出来。

附：[没想到你是这样的flatpak](http://www.ubuntukylin.com/news/shownews.php?lang=cn&id=664)

**bubblewrap** uses `PR_SET_NO_NEW_PRIVS` to turn off setuid binaries, which is the [traditional way](https://en.wikipedia.org/wiki/Chroot#Limitations) to get out of things like chroots.

```
/* Never gain any more privs during exec */
  if (prctl (PR_SET_NO_NEW_PRIVS, 1, 0, 0, 0) < 0)
```

bubblewrap works by **creating a new, completely empty, mount namespace** where the root is on a tmpfs that is invisible from the host, and will be automatically cleaned up when the last process exits.
bubblewrap always creates a new mount namespace, and the user can specify exactly what parts of the filesystem should be visible in the sandbox.
Any such directories you specify mounted `nodev` by default, and can be made readonly.

#### **namespaces**

目前，Linux内核里面实现了7种不同类型的namespace。

|名称      |  宏定义            | 隔离内容 
| :------- | :----------------- | :-------- 
| Cgroup   |   CLONE_NEWCGROUP  | Cgroup root directory (since Linux 4.6)
| IPC      |   CLONE_NEWIPC     | System V IPC, POSIX message queues (since Linux 2.6.19)
| Network  |   CLONE_NEWNET     | Network devices, stacks, ports, etc. (since Linux 2.6.24)
| Mount    |   CLONE_NEWNS      | Mount points (since Linux 2.4.19)
| PID      |   CLONE_NEWPID     |Process IDs (since Linux 2.6.24)
| User     |   CLONE_NEWUSER    | User and group IDs (started in Linux 2.6.23 and completed in Linux 3.8)
| UTS      |   CLONE_NEWUTS     | Hostname and NIS domain name (since Linux 2.6.19)

查看当前bash进程所属的namespace: `ls -l /proc/$$/ns`
namespace相关的函数:

1. clone: 创建一个新的进程并把他放到新的namespace中

```
int clone(int (*child_func)(void *), void *child_statck, int flags, void *arg);
flags: 指定一个或者多个上面的CLONE_NEW*(当然也可以包含跟namespace无关的flags),这样就会创建一个或多个新的不同类型的namespace,并新创建的子进程加入新创建的这些namespace中.
```

1. setns: 将当前进程加入到已有的namespace中

```
int setns(int fd, int nstype);
fd: 指向/proc/[pid]/ns/目录里相应namespace对应的文件,表示要加入哪个namespace
nstype: 指定nsmespace的类型:
        1. 如果当前进程不能根据fd得到它的类型,如fd由其他进程创建,并通过UNIX domain socket传给当前进程,那么就需要通过nstype来制定fd指向的namespace的类型.
        2. 如果进程能根据fd得到namespace类型,比如这个fd是由当前进程打开的,那么nstype设置为0即可.
```

1. unshare: 使当前进程退出指定类型的namespace,并加入到新创建的namespace(相当于创建并加入新的namespace)

```
int unshare(int flags);
flags: 指定一个或者多个namespace类型,这样当前进程就退出了当前指定类型的namespace并加入到新创建的namespace
```

当一个namespace中的所有进程都退出时，该namespace将会被销毁。当然还有其他方法让namespace一直存在，假设我们有一个进程号为1000的进程，以ipc namespace为例：

1. 通过mount --bind命令。例如mount --bind /proc/1000/ns/ipc /other/file，就算属于这个ipc namespace的所有进程都退出了，只要/other/file还在，这个ipc namespace就一直存在，其他进程就可以利用/other/file，通过setns函数加入到这个namespace
2. 在其他namespace的进程中打开/proc/1000/ns/ipc文件，并一直持有这个文件描述符不关闭，以后就可以用setns函数加入这个namespace。

### unity7

Compiz窗口管理器的一个插件，使用nux(opengl)图形库。部分采用cario直接绘制。
添加动态调整整体布局以及kylin style的锁屏和dash，通过监控gsettings设置，条件判断+工厂模式。

### unity8

The Unity 8 Desktop Preview is the new Unity 8 desktop shell running on the Mir display technology.
unity8(c++ + qml) + mir
If you want to run X11 applications that do not have native Mir support in the toolkit they use then the answer is an X11 server that runs on Mir. That could be either Xmir or Xwayland.

### ukui

会话管理器, 按照X 会话管理协议 (XSMP)
会话管理协议的主要部分是：

1. 会话管理器为每个客户端选择一个唯一的标识符
2. 会话管理器需要客户端保存他们的状态
3. 客户端指定它该如何重启以便恢复状态（例如，使用命令行来启动程序）

### 窗口管理器

使用窗口管理器时，Xserver 并不直接与其它 Xclient 通信，而是通过WM中转，当一些消息被定义为WM指令时，它们会被拦截。例如 Alt+F4 关闭窗口、拖动标题栏……

**系统启动过程**：
内核加载 –> init程序运行 –> systemd -> 显示管理器运行(众多服务之一) –> X Server 运行 –> 显示管理器连接到 X Server，显示登录界面 –> 用户登录后，登录界面关闭，加载桌面环境

从上面的流程可以看出，显示管理器是 X Server 的父进程，它负责启动 X Server，当 X Server 启动后，它又变成了 X Server 的一个 Client 程序，连接到 X Server 显示欢迎界面和登录界面，最后，显示管理器又是所有桌面环境的父进程，它负责启动桌面环境需要的其它 Client 程序。

lightdm 在启动 X Server 的时候，给 X Server 加上了 -nolisten tcp 参数，所以远程计算机就没有办法连接到 Ubuntu 的桌面了。