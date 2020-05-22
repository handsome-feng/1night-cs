Server:
```bash
sudo apt install xrdp
sudo adduser xrdp ssl-cert
sudo systemctl restart xrdp

sudo ufw allow 3389
```

log: /var/log/xrdp.log
configure: /etc/xrdp/xrdp.ini
startup: /etc/xrdp/startwm which invode /etc/X11/Xsession
