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