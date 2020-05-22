---
title: 优麒麟20.04远程桌面
---



server:

```
$ sudo apt install tightvncserver xfce4 openssh-server

$ vncserver #set password

$ vncserver -kill :1

$ cat ~/.vnc/xstartup
#!/bin/bash
xrdb %HOME/.Xresources
unset SESSION_MANAGER
unset DBUS_SESSION_BUS_ADDRESS
startxfce4 &

$ vncserver  #restart the VNC server

// open port 5901 if you have UFW firewall enabled
$ sudo ufw allow from any to any port 5901 proto tcp
```



client:

```
$ sudo apt instsall xtightvncviewer
$ sh -L 5901:127.0.0.1:5901 -N -f -l server_user_name vnc_server_ip
$ vncviewer vnc_server_ip:1
```



vnc server system startup script

```
$ cat /etc/systemd/system/vncserver@.server
[Unit]
Description=Systemd VNC server startup script for Ubuntu 20.04
After=syslog.target network.target

[Service]
Type=forking
User=feng
ExecStartPre=-/usr/bin/vncserver -kill :%i &> /dev/null
ExecStart=/usr/bin/vncserver -depth 24 -geometry 800x600 :%i
PIDFile=/home/feng/.vnc/%H:%i.pid
ExecStop=/usr/bin/vncserver -kill :%i

[Install]
WantedBy=multi-user.target
```

