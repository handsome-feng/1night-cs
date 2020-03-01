---
title: Pbuilder
---



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

You  may create ~/.pbuilderrc if you want set options for pbuilder:

```
export DPKG_GENSYMBOLS_CHECK_LEVEL=4

# Codenames for Debian suites according to their alias. Update these when
# needed.
UNSTABLE_CODENAME="sid"
TESTING_CODENAME="bullseye"
STABLE_CODENAME="buster"
STABLE_BACKPORTS_SUITE="$STABLE_CODENAME-backports"

# List of Debian suites.
DEBIAN_SUITES=($UNSTABLE_CODENAME $TESTING_CODENAME $STABLE_CODENAME
    "unstable" "testing" "stable")

# List of Ubuntu suites. Update these when needed.
UBUNTU_SUITES=("focal" "bionic" "xenial")

# Mirrors to use. Update these to your preferred mirror.
DEBIAN_MIRROR="ftp.cn.debian.org"
UBUNTU_MIRROR="ftp.ubuntu.com"

# Optionally use the changelog of a package to determine the suite to use if
# none set.
if [ -z "${DIST}" ] && [ -r "debian/changelog" ]; then
    DIST=$(dpkg-parsechangelog | awk '/^Distribution: / {print $2}')
    DIST="${DIST%%-*}"
    # Use the unstable suite for certain suite values.
    if $(echo "experimental UNRELEASED" | grep -q $DIST); then
        DIST="$UNSTABLE_CODENAME"
    fi
fi

# Optionally set a default distribution if none is used. Note that you can set
# your own default (i.e. ${DIST:="unstable"}).
: ${DIST:="$(lsb_release --short --codename)"}

# Optionally change Debian release states in $DIST to their names.
case "$DIST" in
    unstable)
        DIST="$UNSTABLE_CODENAME"
        ;;
    testing)
        DIST="$TESTING_CODENAME"
        ;;
    stable)
        DIST="$STABLE_CODENAME"
        ;;
esac

# Optionally set the architecture to the host architecture if none set. Note
# that you can set your own default (i.e. ${ARCH:="i386"}).
: ${ARCH:="$(dpkg --print-architecture)"}

NAME="$DIST"
if [ -n "${ARCH}" ]; then
    NAME="$NAME-$ARCH"
    DEBOOTSTRAPOPTS=("--arch" "$ARCH" "${DEBOOTSTRAPOPTS[@]}")
fi
BASETGZ="/var/cache/pbuilder/$NAME-base.tgz"
# Optionally, set BASEPATH (and not BASETGZ) if using cowbuilder
# BASEPATH="/var/cache/pbuilder/$NAME/base.cow/"
DISTRIBUTION="$DIST"
BUILDRESULT="/var/cache/pbuilder/$NAME/result/"
APTCACHE="/var/cache/pbuilder/$NAME/aptcache/"
BUILDPLACE="/var/cache/pbuilder/build/"

if $(echo ${DEBIAN_SUITES[@]} | grep -q $DIST); then
    # Debian configuration
    MIRRORSITE="http://$DEBIAN_MIRROR/debian/"
    COMPONENTS="main contrib non-free"
    DEBOOTSTRAPOPTS=("${DEBOOTSTRAPOPTS[@]}" "--keyring=/usr/share/keyrings/debian-archive-keyring.gpg")

elif $(echo ${UBUNTU_SUITES[@]} | grep -q $DIST); then
    # Ubuntu configuration
    MIRRORSITE="http://$UBUNTU_MIRROR/ubuntu/"
    COMPONENTS="main restricted universe multiverse"
    DEBOOTSTRAPOPTS=("${DEBOOTSTRAPOPTS[@]}" "--keyring=/usr/share/keyrings/ubuntu-archive-keyring.gpg")
else
    echo "Unknown distribution: $DIST"
    exit 1
fi
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



### For multi-arch

If use pbuilder-dist:

```shell
pbuilder-dist unstable armhf create
pbuilder-dist unstable armhf bb_1.3rc1-8.3.dsc
```

Manually doing what pbuilder-dist can do:

```shell
#Create a base environment for Debian sid
sudo DIST=sid pbuilder create

#Create a base environment for Ubuntu eoan under the i386 architecture
sudo DIST=eoan ARCH=i386 pbuilder create

#Create a base environment for Ubuntu eoan
sudo DIST=eoan pbuilder create

#Update a base environment for Ubuntu eoan
sudo DIST=eoan pbuilder update

#Build a package using Ubuntu eoan as the base environment
DIST=eoan pdebuild

#Build a package using Ubuntu eoan as the base environment under the i386 architecture
DIST=eoan ARCH=i386 pdebuild
```



### Reference

https://wiki.ubuntu.com/PbuilderHowto

https://wiki.debian.org/PbuilderTricks