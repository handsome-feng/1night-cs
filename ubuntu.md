* 常用网址  
  镜像下载:         https://cdimage.ubuntu.com  
  Mirros:          https://launchpad.net/ubuntu/+archivemirrors  
  Packages Search: http://packages.ubuntu.com/  
  Source:          https://launchpad.net/ubuntu/+source/youker-assistant  
  Testing tracker: http://iso.qa.ubuntu.com/qatracker  
  Autopkgtest: http://autopkgtest.ubuntu.com/  
  seeds:  https://wiki.ubuntu.com/UbuntuStudio/Seeds  
          https://wiki.ubuntu.com/SeedManagement  
          https://wiki.ubuntu.com/Germinate  
          https://wiki.ubuntu.com/ProposedMigration  
          http://people.canonical.com/~ubuntu-archive/seeds/  
          http://people.canonical.com/~ubuntu-archive/germinate-output/  
  Ubuntu中文WIKI:     http://wiki.ubuntu.org.cn/  
  Ubuntu桌面指南:     https://help.ubuntu.com/lts/ubuntu-help/index.html  
  Ubuntu认证硬件:     https://certification.ubuntu.com/certification/desktop/  
  Debian新维护人员手册: https://www.debian.org/doc/manuals/maint-guide/index.zh-cn.html  
                       https://www.debian.org/doc/manuals/maint-guide/  
  Debian开发人员手册: https://www.debian.org/doc/manuals/developers-reference/  
  Debian打包指南：    https://www.debian.org/doc/manuals/packaging-tutorial/packaging-tutorial.en.pdf  
                     https://www.debian.org/doc/manuals/packaging-tutorial/packaging-tutorial.zh_TW.pdf  
                     http://packaging.ubuntu.com/html/  
  Debian Policy Manual: https://www.debian.org/doc/debian-policy/  
  lintian tags:      https://lintian.debian.org/tags/  
  Daily build log:   http://people.canonical.com/~ubuntu-archive/cd-build-logs/  
  Ubuntu Autopkgtest Results:  http://autopkgtest.ubuntu.com/  
  TechnicalBoard:    https://wiki.ubuntu.com/TechnicalBoard  
                     https://wiki.ubuntu.com/TechnicalBoardAgenda  
  excuses(proposed迁移): http://people.canonical.com/~ubuntu-archive/proposed-migration/update_excuses.html  
  packagesets:        https://people.canonical.com/~ubuntu-archive/packagesets/bionic/  
  License Information: https://ftp-master.debian.org/licenses/  
  DeveloperMembershipBoard: https://wiki.ubuntu.com/DeveloperMembershipBoard  
  Ubuntu Developers: https://wiki.ubuntu.com/UbuntuDevelopers/TeamDelegation  
  Bugs/EmailInterface: https://help.launchpad.net/Bugs/EmailInterface  
  Live filesystem information: https://launchpad.net/~ubuntu-cdimage/+livefs/ubuntu/cosmic/ubuntukylin/  
  Debian bug-tracking system: https://debian-administration.org/article/436/Using_the_Debian_bug-tracking_system  
  debian archive:      https://salsa.debian.org/handsome_feng-guest  
  Debian new and byhand pakcages: https://ftp-master.debian.org/new.html  
  Irc logs:  https://irclogs.ubuntu.com  
  Release:   https://wiki.ubuntu.com/Releases  

* 常用流程  
  SRU:           https://wiki.ubuntu.com/StableReleaseUpdates  
                 http://people.canonical.com/~ubuntu-archive/pending-sru.html  
  SponsorshipProcess: https://wiki.ubuntu.com/SponsorshipProcess  
  FFe:           https://wiki.ubuntu.com/FreezeExceptionProcess  

* 打包工具  
  SBuild:         https://wiki.ubuntu.com/SimpleSbuild  
  DebDiff:        https://wiki.ubuntu.com/UbuntuStudio/DebDiff  

* 在线工具  
  在线贴图工具:    https://imgur.com/  
  在线贴文字工具:  https://paste.ubuntu.com/  
  在线gif制作:     http://www.soogif.com/  
  在线流程图:      https://www.processon.com/diagrams 

* 实用工具  
 1. Youcompleteme  
 2. gollum  
 3. irssi  
 4. goldendict
 5. Beyond Compare
 6. SS
 7. xdotool  

* 服务器  
 1. discuz  
 2. wordpress  

* 启动流程
 1. BIOS
 2. Kernel
 3. lightdm
 4. session-manager

* 设备
 1. 终端: /dev/tty1 ... /dev/pts/0 ...  

* 常用命令
 1. 包管理
    * 包规范
      ```
      alias mylintian="lintian -i -EvIL +pedantic --verbose"
      alias mylicense="licensecheck -r . | grep -v 'UNKNOWN'"
      ```

 2. 系统监控
    * 网络
      1. ifconfig
      2. netstat
      3. tcpdump
      4. wireshark

 3. X window

    - 查看快捷键被谁捕获

    ```shell
    xdotool keydown "shift+Print"; xdotool key "XF86LogGrabInfo"; xdotool keyup "Print"; sleep 1; xdotool keyup "shift"; tail /var/log/Xorg.0.log
    ```

* 跨版本

 1. Flatpak
 2. Snap

* 其他
 1. ANSI控制码: http://ascii-table.com/ansi-escape-sequences.php
