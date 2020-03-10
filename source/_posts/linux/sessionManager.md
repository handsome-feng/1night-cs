Session Manager

1. 会话管理器是什么，什么作用

2. KDE/GNOME/Deepin

3. ukui-session-manager优势与劣势

   

传统的 Linux 系统使用 ConsoleKit 跟踪用户登录情况，并决定是否赋予其关机的权限。现在 ConsoleKit 已经被 systemd 的 logind 所替代。

logind 不是 pid-1 的 init 进程。它的作用和 UpStart 的 session init 类似，但功能要丰富很多，它能够管理几乎所有用户会话(session)相关的事情。logind 不仅是 ConsoleKit 的替代，它可以：

* 维护，跟踪会话和用户登录情况。如上所述，为了决定关机命令是否可行，系统需要了解当前用户登录情况，如果用户从 SSH 登录，不允许其执行关机命令；如果普通用户从本地登录，且该用户是系统中的唯一会话，则允许其执行关机命令；这些判断都需要 logind 维护所有的用户会话和登录情况。
* Logind 也负责统计用户会话是否长时间没有操作，可以执行休眠/关机等相应操作。
  为用户会话的所有进程创建 CGroup。这不仅方便统计所有用户会话的相关进程，也可以实现会话级别的系统资源控制。
* 负责电源管理的组合键处理，比如用户按下电源键，将系统切换至睡眠状态。
* 多席位(multi-seat) 管理。如今的电脑，即便一台笔记本电脑，也完全可以提供多人同时使用的计算能力。多席位就是一台电脑主机管理多个外设，比如两个屏幕和两个鼠标/键盘。席位一使用屏幕 1 和键盘 1；席位二使用屏幕 2 和键盘 2，但他们都共享一台主机。用户会话可以自由在多个席位之间切换。或者当插入新的键盘，屏幕等物理外设时，自动启动 gdm 用户登录界面等。所有这些都是多席位管理的内容。ConsoleKit 始终没有实现这个功能，systemd 的 logind 能够支持多席位。

好的一点是，这非常有助于标准化 Linux 的管理！从前，不同的 Linux 发行版各行其事，使用不同方法管理系统，从来也不会互相妥协。比如如何将系统进入休眠状态，不同的系统有不同的解决方案，即便是同一个 Linux 系统，也存在不同的方法，比如一个有趣的讨论：如何让 ubuntu 系统休眠，可以使用底层的/sys/power/state 接口，也可以使用诸如 pm-utility 等高层接口。存在这么多种不同的方法做一件事情对像我这样的普通用户而言可不是件有趣的事情。systemd 提供统一的电源管理命令接口，这件事情的意义就类似全世界的人都说统一的语言，我们再也不需要学习外语了，多么美好！

X Session Management Protocol

The purpose of the X Session Management Protocol (XSMP) is to provide a uniform mechanism for users to save and restore their sessions. 

A session is a group of clients, each of which has a particular state. 



### Mate Session Manager

require_dbus_session

gsm_util_export_activation_environment

gsm_util_export_user_environment

check_gl

XDG_CURRENT_DESKTOP=MATE

DISPLAY=gdk_display_get_name

MATE_DESKTOP_SESSION_ID=this-is-deprecated

initialize_gsettings

accessibility: GTK_MODULES=gail:atk-bridge

gsm_store_new

gsm_xsmp_server_new

acquire_name

msm_gnome_start() //gnome compat mode: keyring, smproxy

set_overlay_scroll

gsm_manager_new

mdm_signal_hander_new

load_standard_apps(初始化为autostart_app, add进client_store)

​	maybe_load_saved_session_apps

​	gsm_manager_add_autostart_apps_from_dir

​	append_default_app: ukui-settings-daemon

​	append_required_apps: dock, filemanager, panel, windowmanager

​	append_accessibility_apps: 

```
typedef enum {
    /* gsm's own startup/initialization phase */
    GSM_MANAGER_PHASE_STARTUP = 0,

    /* xrandr setup, mate-settings-daemon, etc */
    GSM_MANAGER_PHASE_INITIALIZATION,

    /* window/compositing managers */
    GSM_MANAGER_PHASE_WINDOW_MANAGER,

    /* apps that will create _NET_WM_WINDOW_TYPE_PANEL windows */
    GSM_MANAGER_PHASE_PANEL,

    /* apps that will create _NET_WM_WINDOW_TYPE_DESKTOP windows */
    GSM_MANAGER_PHASE_DESKTOP,

    /* everything else */
    GSM_MANAGER_PHASE_APPLICATION,

    /* done launching */
    GSM_MANAGER_PHASE_RUNNING,

    /* shutting down */
    GSM_MANAGER_PHASE_QUERY_END_SESSION,
    GSM_MANAGER_PHASE_END_SESSION,
    GSM_MANAGER_PHASE_EXIT
} GsmManagerPhase;
```



### KDE ksmserver

* sanity_check(he(合理性检验)

  HOME, ICEAUTHORITY, KDETMP/ice-unix(socket directory where X-windows session information is saved)

* SESSION_MANAGER=

* checkComposite()

* QT_QPA_PLATFORM=xcb when launchpad ksmserver self

* fcntl(ConnectionNumber(QX11Info::display()), F_SETFD, 1);

* check_library_exists(ICE _IceTransNoListen "" HAVE__ICETRANSNOLISTEN)

* setupShortcuts





