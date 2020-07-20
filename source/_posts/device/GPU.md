查看显卡

lspci -k | grep -A 2 -i "VGA"

ls /dev/dri/

查看显卡驱动

sudo lshw -c display

安装显卡驱动

1. 软件与更新 -> 附加驱动

2. sudo ubuntu-drivers devices

   sudo ubuntu-drivers autoinstall

   or

   sudo apt install nvidia-driver-[num]

查看在使用哪个显卡

prime-select query

切换显卡

sudo prime-select intel

sudo prime-select nvidia

或者

sudo apt install nvidia-settings



禁止N卡：

sudo vim /etc/modprobe.d/blacklist.conf

添加 blacklist nouveau



显卡消失：

Step 1 : Remove all NVIDIA related software you installed.

Highlight the Ubuntu menu entry and press the E key.
Add `nouveau.modeset=0` to the end of the linux line.
Press the F10 key to boot into the Ubuntu system.

When the login screen appears press Ctrl+Alt+F1.
Enter your user name and password ... then execute :

```
sudo apt-get purge nvidia* bumblebee
sudo reboot
```

Step 2 : Reinstall the NVIDIA drivers and Optimus support.

Highlight the Ubuntu menu entry and press the E key.
Add `nouveau.modeset=0` to the end of the linux line.
Press the F10 key to boot into the Ubuntu system.

When the login screen appears press Ctrl+Alt+F1.
Enter your user name and password ... then execute :

```
sudo apt-get update
sudo apt-get install nvidia-352 nvidia-prime
sudo reboot
```

在nvidia-settings里切换到inter显卡，重启，再切换到n卡，再重启，就回来了