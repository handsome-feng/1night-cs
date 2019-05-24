#### SRU:

https://wiki.ubuntu.com/StableReleaseUpdates
http://people.canonical.com/~ubuntu-archive/pending-sru.html



debdiff:

$ apt-get source kylin-nm

$ pull-lp-source <package_name> trusty

Import a patch

$ quilt import -P fix-foobar.patch /tmp/patch
$ quilt push

Or create a new patch

$ quilt new fix-foobar.patch

$ quilt edit foobar.c

or

$ quilt add file-to-modify  && $ vim file-to-modify

$ quilt refresh



$ update-maintainer



$ debuild -S

$ debdiff kylin-nm_1.0.0-1.dsc kylin-nm_1.0.0-1ubuntu0.1.dsc > kylin-nm_1.0.0-1ubuntu0.1.debdiff