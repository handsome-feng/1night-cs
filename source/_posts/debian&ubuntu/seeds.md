---
title: seeds
---



cd ~/home/feng/seeds

git clone 

git clone

mv ubuntukylin ubuntukylin.disco

mv platform platform.disco

germinate -S file:///home/feng/seeds/ -s ubuntukylin.disco -d disco -a amd64 -c main,restricted,universe,multiverse -m http://mirrors.aliyun.com/ubuntu/

最后查看desktop文件，为桌面版本iso的包列表



This is an example of a seed file (minimized version of a real seed file):

```
Task-Per-Derivative: 1

Task-Section: user

Task-Description: 2D/3D creation and editing suite

Task-Key: ubuntustudio-graphics


* agave #This is a dependency

* (blender) #This is a recommend

# * (openclipart-svg) #Has been commented out, and will not be used


* ubuntukylin-desktop # Metapackage for everything here.
```

You can view the [current seeds](http://people.canonical.com/~ubuntu-archive/seeds/), and the current output of [germinate](http://people.canonical.com/~ubuntu-archive/germinate-output/).

refefence:

1. https://wiki.ubuntu.com/SeedManagement
2. https://wiki.ubuntu.com/Germinate