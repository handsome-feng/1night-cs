---
title: Snap
---



```
$ sudo snap ack ubuntu-core_1797.assert
$ sudo snap install ubuntu-core_1797.snap
$ sudo snap ack somePackage.assert
$ sudo snap install somePackage.snap

$ sudo snap install --dangerous some.snap

$ sudo snap revert hello

$ snap changes
$ sudo snap abort id
```



```
$ sudo apt install apparmor apparmor-utils
$ sudo mkdir -p /etc/default/grub.d
$ echo 'GRUB_CMDLINE_LINUX_DEFAULT="$GRUB_CMDLINE_LINUX_DEFAULT apparmor=1 security=apparmor"' \
  | sudo tee /etc/default/grub.d/apparmor.cfg
$ sudo update-grub
$ sudo reboot

$ sudo aa-status

$ ps auxZ | grep -v '^unconfined'
```

$ xdelta3 -s telegram-desktop_637.snap telegram-desktop_617.snap telegram-desktop_637.snap.xdelta3



查看SELinux状态：

1、/usr/sbin/sestatus -v      ##如果SELinux status参数为enabled即为开启状态

SELinux status:                 enabled

2、getenforce                 ##也可以用这个命令检查

关闭SELinux：

1、临时关闭（不用重启机器）：

setenforce 0                  ##设置SELinux 成为permissive模式

​                              \##setenforce 1 设置SELinux 成为enforcing模式

2、修改配置文件需要重启机器：

修改/etc/selinux/config 文件

将SELINUX=enforcing改为SELINUX=disabled

重启机器即可