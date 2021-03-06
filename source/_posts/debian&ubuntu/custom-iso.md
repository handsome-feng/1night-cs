---
title: 手动定制优麒麟镜像
---

## 手动集成版本流程如下：

1. 点击基础iso镜像，右键挂载镜像:

     `sudo mount xxx.iso /mnt/uk64`

2. 创建一个image-iso目录，拷贝挂载镜像的所有文件到image-iso目录（注意隐藏文件不要漏掉了）

     `cd /image-iso`

     `rsync -a /mnt/uk64 .`

3. 将image-iso/casper/filesystem.squashfs 移动到工作目录下:

     `sudo mv uk64/casper/filesystem.squashfs .`

4. 解压缩文件，生成squashfs-root目录

     `sudo unsquashfs filesystem.squashfs`

5. chroot进入squashfs-root目录，命令：

     `sudo chroot squashfs-root`

6. 进入chroot后第一个操作为mount：

   ```shell
   mount -t proc proc /proc
   mount -t sysfs sysfs /sys
   mount -t devtmpfs devtmpfs /dev
   mount -t devpts devpts /dev/pts
   ```

7. 配置chroot环境中的网络、apt源等（配置网络修改/etc/resolv.conf，修改源更改/etc/apt/sources.list文件,添加multiverse)

     `vim.tiny /etc/resolv.conf: nameserver 114.114.114.114`

8. chroot环境中安装包、删除包、修改配置文件等

     ```shell
     add-apt-repository ppa:feng-kylin/1810aid
     apt-get install foxitreader flashplugin-installer libgconf-2-4
     apt purge apport apport-gtk apport-symptoms python-apport gnome-software gnome-software-common ubuntu-software libreoffice-* mate-polkit kylin-greeter
     ```

     * windows字体 添加可执行权限和可读权限
       sudo cp -r huawen_font /usr/share/fonts
       chmod +rx -R huawen_font

     * 更新字体缓存，执行命令

       `fc-cache -v -f`

     * 更新开机动画 (可选，主题包postinst文件里有)

       ```bash
       update-alternatives \
           --install /usr/share/plymouth/themes/default.plymouth default.plymouth \
           /usr/share/plymouth/themes/ubuntukylin-logo/ubuntukylin-logo.plymouth 150
       update-alternatives \
           --install /usr/share/plymouth/themes/text.plymouth text.plymouth \
           /usr/share/plymouth/themes/ubuntukylin-text/ubuntukylin-text.plymouth 150
       update-initramfs -u
       ```

     * 更新grub主题 (可选)

       ```bash
       if [ -e /boot/grub/grub.cfg ]; then
           update-grub || true
       fi
       ```

     * 还原定制版本中修改的配置文件及清除缓存，如/etc/resolv.conf文件，/var/cache/apt/archives目录下的deb包，/var/lib/apt/lists目录下的apt更新list文件等

       ```shell
       add-apt-repository -r ppa:feng-kylin/1810aid
       rm /etc/apt/sources.list.d/feng-kylin-*
       rm /var/lib/apt/lists/ppa.launchpad.net_feng-kylin_1810aid_ubuntu_dists_cosmic_*
       apt-get clean
       rm /var/lib/apt/periodic/update-success-stamp
       vim.tiny /etc/resolv.conf
       vim.tiny /etc/apt/sources.list
       history -c
       ```

9. 退出chroot前最后一个操作：

      ```shell
      umount -l /sys
      umount -l /dev/pts
      umount -l /dev
      umount -l /proc
      ```

10. 退出chroot环境:

      `exit`

11. 删除旧的filesystem.squashfs，创建新的filesystem.squashfs，命令如下：

   ```
   sudo rm filesystem.squashfs
   sudo mksquashfs squashfs-root/ filesystem.squashfs
   ```

12. 更新filesystem.squashfs.size

     `sudo du -sx --block-size=1 squashfs-root | cut -f1 > filesystem.size`

13. 删除squashfs-root目录：

   ```
   sudo rm -r squashfs-root/
   ```

14. 将filesytem.squashfs 和filesystem.size移动到casper目录，并修改新filesystem.squashfs文件属主和权限，跟其余文件一样：

    ```
    sudo mv filesystem.squashfs filesystem.size uk64/casper
    cd uk64/casper
    sudo chmod 444 filesystem.squashfs filesystem.size
    sudo chown feng:feng filesystem.squashfs filesystem.size
    ```

15. 定制ubiquity安装过程（可选）：

    ```
    sudo vim uk64/preseed/cli.seed
    sudo vim boot/grub/grub.cfg
    ```

16. 修改bootlogo（可选）:

    ```
    mv uk64/isolinux/bootlogo .
    mkdir bootlogo-tmp && cd bootlogo-tmp
    cpio -i < ../bootlogo
    sudo vim txt.cfg lang langlist
    ls -1 | cpio --quiet -o > ./bootlogo
    sudo cp * ../uk64/isolinux
    ```

17. 进入到image-iso目录，更新md5值：

    ```
    sudo rm md5sum.txt
    find -type f -print0 | sudo xargs -0 md5sum | grep -v isolinux/boot.cat | sudo tee md5sum.txt
    sudo chown feng:feng md5sum.txt
    sudo chmod -w md5sum.txt
    ```

18. 进入到uk64目录，压缩镜像

    ```
    xorriso -as mkisofs -r -checksum_algorithm_iso md5,sha1 -V Ubuntu-Kylin\ 19.04 -o ubuntukylin-19.04-amd64.iso -isohybrid-mbr /usr/lib/ISOLINUX/isohdpfx.bin -cache-inodes -J -l -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table -eltorito-alt-boot -e boot/grub/efi.img -no-emul-boot -isohybrid-gpt-basdat -isohybrid-apm-hfsplus uk64/
    ```

* 如果是32位:
    ```
    xorriso -as mkisofs -r -checksum_algorithm_iso md5,sha1 -V Ubuntu-Kylin\ 18.04.2 -o ubuntukylin-18.04.2-enhanced-i386.iso -isohybrid-mbr /usr/lib/ISOLINUX/isohdpfx.bin -partition_offset 16 -cache-inodes -J -l -b isolinux/isolinux.bin -c isolinux/boot.cat -no-emul-boot -boot-load-size 4 -boot-info-table uk32/
    ```

#### 其他
* pressed配置：

     https://help.ubuntu.com/lts/installation-guide/s390x/apbs04.html#preseed-l10n

     <https://wiki.ubuntu.com/UbiquityAutomation>

     <https://help.ubuntu.com/community/InstallCDCustomization>

     https://help.ubuntu.com/community/LiveCDCustomization

     https://help.ubuntu.com/community/LiveCDCustomizationFromScratch

* 修改/etc/sudoers,使得sudo不需要密码：

  kylin (ALL: ALL) NOPASSWD: ALL

  %sudo (ALL: ALL) NOPASSWD: ALL

* 解开initrd:

  unmkinitramfs initrd
  
* 自动化定制ISO工具：

     [Cubic](https://launchpad.net/cubic)
