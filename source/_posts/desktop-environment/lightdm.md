---
Lightdm
---



命令行工具，它可用来锁定当前 seat, 切换会话，等等

$ dm-tool --help

 

$  sudo apt install xserver-xephyr

$ lightdm --test-mode --debug

 

默认打开小键盘:

安装 numlockx, 编辑 /etc/lightdm/lightdm.conf 添加以下几行:

[Seat:*]

greeter-setup-script=/usr/bin/numlockx on

 

$ systemctl status lightdm.service

$ systemctl help lightdm.service

 

After enabling lightdm a symlink display-manager.service should be set in /etc/systemd/system/. You may need to use --force to override old symlinks. 

feng@380:~$ file /etc/systemd/system/display-manager.service

/etc/systemd/system/display-manager.service: symbolic link to /lib/systemd/system/lightdm.service

 

loginctl --help

 

Session configuration

Many display managers read available sessions from /usr/share/xsessions/ directory. It contains standard desktop entry files for each DM/WM. 

 

Starting applications without a window manager

 

You can also launch an application without any decoration, desktop, or window management. For example to launch google-chromeAUR create a web-browser.desktop file in /usr/share/xsessions/ like this:

 

[Desktop Entry]

Encoding=UTF-8

Name=Web Browser

Comment=Use a web browser as your session

Exec=/usr/bin/google-chrome --auto-launch-at-startup

TryExec=/usr/bin/google-chrome --auto-launch-at-startup

Icon=google-chrome

 

 ~/.xinitrc or /etc/X11/xinit/xinitrc 

  

# **The Light Display Manager (LightDM)**

## **Description**

*LightDM* is a cross-desktop display manager. A display manager is a daemon that:

Runs display servers (e.g. X) where necessary.

Runs greeters to allow users to pick which user account and session type to use.

Allows greeters to perform authentication using PAM.

Runs session processes once authentication is complete.

Provides remote graphical login options.

Key features of LightDM are: 

Cross-desktop - supports different desktop technologies.

Supports different display technologies (X, Mir, Wayland ...).

Lightweight - low memory usage and fast performance.

Guest sessions.

Supports remote login (incoming - XDMCP, VNC, outgoing - XDMCP, pluggable).

Comprehensive test suite.

## **Configuration**

LightDM configuration is provided by the following files:

/usr/share/lightdm/lightdm.conf.d/*.conf_x000D_/etc/lightdm/lightdm.conf.d/*.conf_x000D_/etc/lightdm/lightdm.conf

System provided configuration should be stored in */usr/share/lightdm/lightdm.conf.d/*. System administrators can override this configuration by adding files to */etc/lightdm/lightdm.conf.d/* and */etc/lightdm/lightdm.conf*. Files are read in the above order and combined together to make the LightDM configuration.

配置文件书写规则http://bazaar.launchpad.net/~lightdm-team/lightdm/trunk/view/head:/data/lightdm.conf

 

# **LightDM Design**

## **What is a Display Manager?**

The responsibilities of a display manager are: 

Starting and managing local instances of the X server. 

Authenticating users. 

 

Starting and managing user sessions. Common use cases: 

 

 

Starting a single X server on boot and starting a session (kiosk mode). 

 

Starting a single X server instance on boot, displaying a greeter GUI (username and password), and starting the user session when connected (traditional). 

Supporting multiple simultaneous logins by exposing what users are logged in, and starting new X servers for each user (user switching). 

Running a thin-client server by allowing X servers to connect using XDMCP, and connecting greeters and sessions to those X servers. 

## **Design Goals**

Fast - The display manager should add no noticeable delay to startup time. 

Fail-safe - Failures should be handled gracefully. 

Secure - Resistant to malicious users. 

Flexible - Able to support a range of use-cases. 

Extensible - Able to support rarer use-cases though plugins. 

Simple - Configuration should be easy and the code should be simple to understand and modify. 

## **Definitions**

Display Manager - A daemon that manages the displays on a system. 

Display - A combination of an X server, greeter and a user session. 

User session - An application that runs on a display and allows the user to run applications. 

Greeter - An application to run on a display and prompt for authentication and session options. 

## **Requirements**

Daemon: 

Able to run as as system service without user interaction 

Provide logging information for debugging 

Launch and monitor X servers 

Launch and monitor greeter applications for displays without a user session 

Launch and monitor user sessions after user is authenticated 

Authenticate users 

Provide an interface to greeter applications 

Provide an interface to user switchers 

Store a database of active displays 

Load sessions from /usr/share/xsessions 

Store session configuration in ~/.dmrc 

Support .dmrc not being readable before login 

Advertise display database to [Software/ConsoleKit](https://www.freedesktop.org/wiki/Software/ConsoleKit/) if available 

Use PAM for authentication Session environment: 

Set USER to the username 

Set HOME to users home directory 

Set SHELL to the users shell 

Set PATH to /usr/bin:/bin 

Set LANG to the users language 

Set DISPLAY to the X servers address 

 

Set environment variables from /etc/environment Static Display Module: 

 

Allow 0-N displays to be enabled at all time 

 

Support automatic/timed login User Switcher Module: 

 

 

Interface to switch to existing local display for a logged in user 

 

Start new static display if user not logged in XDMCP Server Module: 

Implement XDMCP protocol Module interface: 

 

Expose display database Greeter application/interface: 

  

User authentication 

Session choice 

Session language 

Session keyboard layout 

Logged in users 

## **Implementation**

Daemon: 

　　Implemented in C+GObject 

Single process Greeter Interface: 

D-Bus GTK+ Greeter: 

## **Inter-process Relationships**

![img](file:////tmp/wps-feng/ksohtml/wpsaXjxvp.jpg) 

 