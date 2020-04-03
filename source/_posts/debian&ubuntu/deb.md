---
title: deb包
---

### 从源码构建deb包

dh_make

debuild

### 解包
```bash
# 解包
dpkg -X foo.deb extract/
dpkg -e foo.deb extract/DEBIAN
# 按需求修改
# 打包
dpkg-deb -b extract/ result/
```
