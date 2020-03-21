---
title: SRU
---

## SRU:

https://wiki.ubuntu.com/StableReleaseUpdates
http://people.canonical.com/~ubuntu-archive/pending-sru.html



### debdiff:

#### If source format is 'quilt'

```bash
$ apt-get source kylin-nm
$ pull-lp-source <package_name> trusty
```

Import a patch

```bash
$ quilt import -P fix-foobar.patch /tmp/patch
$ quilt push
```

Or create a new patch

```bash
$ quilt new fix-foobar.patch
# use the editor from quilt
$ quilt edit foobar.c
# or use your favorable editor
# $ quilt add file-to-modify  && $ vim file-to-modify
$ quilt refresh
```

```bash
$ update-maintainer
$ debuild -S
$ debdiff kylin-nm_1.0.0-1.dsc kylin-nm_1.0.0-1ubuntu0.1.dsc > kylin-nm_1.0.0-1ubuntu0.1.debdiff
```



#### if source format is 'native'
```bash
$ pull-lp-source kylin-nm trusty
# then edit it
$ debuild -sa -S
$ defdiff kylin-nm_1.0.0-1.dsc kylin-nm_1.0.0-1ubuntu0.1.dsc > kylin-nm_1.0.0-1ubuntu0.1.debdiff
```

reference: https://wiki.ubuntu.com/UbuntuStudio/DebDiff