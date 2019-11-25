grub修复：

假如你的Ubuntu的 / 分区是sda9，又假如 /boot分区是 sda6，在终端下输入
sudo -i
mount /dev/sda7 /mnt
mount /dev/sda6 /mnt/boot （如果没 /boot 单独分区这步跳过）
grub-install --root-directory=/mnt/ /dev/sda
做完后grub就修复了。

如果grub里没有windows的菜单了，那么进入Ubuntu系统，打开终端，
重建GRUB列表 sudo update-grub
重新写入第一分区mbr sudo grub-install /dev/sda

