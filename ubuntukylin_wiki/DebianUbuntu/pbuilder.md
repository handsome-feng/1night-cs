You must use sudo for pbuilder. Hence you must make an entry in the sudoers file:

```
sudo visudo
```

and add the following entry (Not sure, encounter error in debian after add this): 

```
user_name ALL=(ALL) NOPASSWD:/usr/sbin/pbuilder
```

Now you need to set up a base tarball that will contain your chroot environment: 

```
sudo pbuilder create
```

The result will be found at  `/var/cache/pbuilder/base.tgz`

Note: If you are on Ubuntu or another GNU/Linux distribution, run 

```
sudo apt-get install debian-archive-keyring
sudo pbuilder create --distribution sid --mirror http://mirrors.ustc.edu.cn/debian/ --debootstrapopts "--keyring=/usr/share/keyrings/debian-archive-keyring.gpg"
```

and copy the base.tgz to another location for you to work in a debian environment. 

```
sudo pbuilder --login --save-after-login --basetgz <path to your base.tgz file>
```

 你可以使用 `pbuilder --login --save-after-login` 命令登录到这个 **chroot** 环境中并按照需要对其进行配置。通过 `^D` (Control-D)离开这个 shell 时环境会被保存。 

Note down the temporary build directory root which you can use to copy files to and from. For example,  

```
$ sudo pbuilder --login
I: Building the build Environment
I: extracting base tarball [/media/forge/debian/pbuilder/sid-base.tgz]
I: creating local configuration
I: copying local configuration
I: mounting /proc filesystem
I: mounting /run/shm filesystem
I: mounting /dev/pts filesystem
I: Mounting /media/forge/debian/pbuilder/ccache
I: policy-rc.d already exists
I: Obtaining the cached apt archive contents
I: entering the shell
File extracted to: /media/forge/debian/pbuilder/build/26975

root@savannah:/# 
```

Your  debian environment is at /media/forge/debian/pbuilder/build/26975. Any  file you copy there will be available to debian chroot. 

You  may create ~/.pbuilderrc if you want set options for pbuilder, for  example if you want to keep pbuilder files in an external hard drive, 

```
BASETGZ=/media/forge/debian/pbuilder/sid-base.tgz
BUILDPLACE=/media/forge/debian/pbuilder/build
CCACHEDIR=/media/forge/debian/pbuilder/ccache
BASEPATH=/media/forge/debian/pbuilder/base.cow
COWBUILDER_BASE=/media/forge/debian/pbuilder/
DISTRIBUTION=sid
BUILDRESULT=/media/forge/debian/pbuilder/results
APTCACHE=/media/forge/debian/pbuilder/aptcache
DEBEMAIL="Your Name <email@yourprovide.domain>"
#AUTOCLEANAPTCACHE=yes
```

 

# Build

Update the chroot environment:

```
$ sudo pbuilder --update
```

Now it is  time to build the package you already created again, this time with  pbuilder. For that you will use the dsc file you created with  dpkg-buildpackage 

```
$ sudo pbuilder build ruby-devise_2.1.2-1.dsc
```

 如果你已经更新了源代码树但没有生成对应的源代码包，在存放 `debian` 目录的源码目录里执行： 

```
$ sudo pbuilder --update
$ pdebuild
```

The result will be found in  

```
/var/cache/pbuilder/result 
```

Again you have to make sure it is lintian clean: 

```
cd /var/cache/pbuilder/result
lintian -iIEcv --pedantic --color auto ruby-devise_2.1.2-1*.changes
```
 新构建的无 GPG 签名的软件包会被以非 root 属主放置于 `/var/cache/pbuilder/result/`。 

 `.dsc` 文件和 `.changes` 文件中的 GPG 签名可以用如下方法生成： 

```
$ cd /var/cache/pbuilder/result/
$ debsign foo_version_arch.changes
```

# Hook

 创建一个对用户可写的目录保存钩子脚本，例如 `*/var/cache/pbuilder/hooks*` 

 在 `~/.pbuilderrc` 或 `/etc/pbuilderrc` 中添加以下内容： 

```
AUTO_DEBSIGN=${AUTO_DEBSIGN:-no}
HOOKDIR=/var/cache/pbuilder/hooks
```

 最新版的 **lintian** 命令可以通过设置钩子脚本 `*/var/cache/pbuilder/hooks*/B90lintian` 在 `chroot` 环境中运行。脚本内容如下:

```
#!/bin/sh
set -e
install_packages() {
        apt-get -y --allow-downgrades install "$@"
        }
install_packages lintian
echo "+++ lintian output +++"
su -c "lintian -i -I --show-overrides /tmp/buildd/*.changes" - pbuilder
# use this version if you don't want lintian to fail the buildsudo
#su -c "lintian -i -I --show-overrides /tmp/buildd/*.changes; :" - pbuilder
echo "+++ end of lintian output +++"
```



### Reference

https://wiki.ubuntu.com/PbuilderHowto

https://wiki.debian.org/PbuilderTricks