---
title: kvm
---



检查是否支持硬件虚拟化：

$ egrep -c '(vmx|svm)' /proc/cpuinfo  #(>=1则支持)

或

$ kvm-ok



安装依赖：

$ sudo apt install qemu-kvm libvirt-clients qemu-utils libvirt-daemon-system



启动libvertd服务：

$ sudo systemctl enable libvirtd

$ sudo systemctl start libvirtd



In order to be able to manage virtual machines as regular user, that user needs to be added to some groups:

$ sudo add user feng libvirt

$ sudo add user feng libvirt-qemu



设置网络桥接：

$ sudo vim /etc/network/interfaces

```
auto lo

iface lo inet loopback



auto br0

iface br0 inet dhcp

bridge_ports enp2s0   //enp2s0 is the name of your interface
```



创建一个vm:

sudo virt-install --name kylin-1904 --memory 2048 --vcpus 1 --disk size=12 --cdrom /home/feng/ubuntukylin-1904-enhanced-desktop-amd64.iso --graphics vnc,listen=0.0.0.0 --noautoconsole --bridge br0



客户端通过remmina连接，并完成安装：

vnc: 10.0.0.100:5900



克隆vm:

$ sudo virt-clone -o kylin-1904 -n kylin-1904-1 -f /var/lib/libvirt/images/kylin-1904-1.qcow2



批量克隆：

```shell
#!/bin/bash

for i in `seq 1 50`
do
virt-clone -o kylin-1904 -n kylin-1904-$i -f /var/lib/libvirt/images/kylin-1904-$i.qcow2
echo "copying $i..."
done
```



配置文件路径：

/etc/libvirt/qemu



查看vnc端口号：

$ sudo virsh dumpxml kylin-1904 | grep vnc

或者

$ sudo virsh vncdisplay kylin-1904



管理VMs:

sudo virsh list --all

sudo virsh start kylin-19.04

sudo virsh suspend kylin-19.04

sudo virsh resume kylin-19.04

sudo virsh shutdown kylin-19.04

sudo virsh undefine kylin-19.04

sudo virsh destroy kylin-19.04