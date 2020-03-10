---
title: Debug Symbol Pakcages
---



## Debug Symbol Packages

1. Create an /etc/apt/sources.list.d/ddebs.list by running the following line at a terminal:

   ```shell
   echo "deb http://ddebs.ubuntu.com $(lsb_release -cs) main restricted universe multiverse
   deb http://ddebs.ubuntu.com $(lsb_release -cs)-updates main restricted universe multiverse
   deb http://ddebs.ubuntu.com $(lsb_release -cs)-proposed main restricted universe multiverse" | \
   sudo tee -a /etc/apt/sources.list.d/ddebs.list
   ```

2. Import the debug symbol archive signing key from the Ubuntu server:

   ```shell
   $ sudo apt install ubuntu-dbgsym-keyring   
   $ sudo apt update
   ```

3. Install debug packages

   ```shell
   $ sudo apt install xxx-dbgsym
   ```

4. Automatic resolution

   ```shell
   #!/bin/bash -x
   progname=`basename "$0"`
   
   explain() {
       cat << EOF
   Usage: $progname [-adt] [-p pid] | [exectable]
   
   You must specify a pid (-p) or an executable name/path.
   
   This scripts list the dbug symbols packages you need to install for a complete dump of the give executable. Already installed symbols packages are not shown.
   
   Options are:
     -p pid  uses the running process with the given pid to get the list.
                   If specified, you may omit the executable name.
     -a          show all the required symbol packages (not only the not-installed
                   ones)
     -d          prefer XXX-dbg symbol packages over XXX-dbgsym ones
     -t           terse: print the packages names only (no package description).
                   Useful to pass output directly to apt-get install.
   
   NOTE: in some cases $progname may report already installed
   packages. This currently happens with binaries using libpthread.so as
   libc6-i686-dbgsym apparently doesn't contain debug symbols for it.
   
   To examine a running server process by pid, you will need to run this script
   using sudo.
   EOF
       exit -1
   }
   
   all=false
   preferred="dbgsym dbg"
   debug=false
   terse=false
   pid=
   while getopts :adgp:t opt; do
       case $opt in
           a)
               all=true
               ;;
           d)
               preferred="dbg dbgsym"
               ;;
           g)
               debug=true
               ;;
           p)
               pid="$OPTARG"
               binary=$(readlink /proc/$pid/exe)
               [ -z "$binary" ]&& echo "Unable to get binary path for pid $pid" && exit -1
           t)
               terse=true
               ;;
           \?)
               explain
               ;;
       esac
   done
   
   if [ -z "$binary" ]; then
       shift $(( $OPTIND - 1 ))
       [ $# -ne 1 ] && explain
       binary="$1"
       [ ! -x "$binary" -a `basename @"$binary"` = @"$binary" -a -n "`which $binary`" ] && binary=`which $binary`
   fi
   
   find-debug() {
       while read i; do
           for ext in $preferred; do
               i=$(echo "$i"|cut -f 1 -d:) #remove the architecture suffix
               apt-cache search "^$i-$ext\$"
           done |head -1
       done
   }
   
   if [ ! -z "$pid" ]; then
      Args="--pid=$pid"
   else
      Args="$binary"
   fi
   
   echo q| gdb "$Args" | \
   grep 'Reading symbols from '| \
   if $all; then cat; else grep 'no debugging symbols found'; fi | \
   sed -e 's/^Reading symbols from \(.*\)\.\.\.\((\|Reading \).*$/\1/' | \
   while read i; do \
       #dpkg -S "$i" |while read j; do if $debug; then echo '!' $i '-->' $j 1>&2; fi; echo $j; done
       ( if ! dpkg -S "$i" 2>/dev/null; then [ -L "$i" ] && dpkg -S `readlink "$i"`; fi ) | \
       while read j; do if $debug; then echo '!' $i '-->' $j 1>&2; fi; echo $j; done \
   done| sed -e 's/^\(.*\): .*$/\1/' | sort -u | \
   find-debug | if $terse; then sed -e 's/ - .*$//'; else cat; fi |sort -u
   ```

5. Set generate core dump:

   ```
   ulimit -c unlimited
   sudo service apport stop // modify /proc/sys/kernle/core_pattern or sysctl.conf
   ```

6. gdb ./a.out core



## Debian

https://wiki.debian.org/AutomaticDebugPackages



## Principle

`/usr/lib/.build-id` contains the main build-id files for installed packages. 

Debug info packages are used in many distributions to provide a way for users to install debugging information when necessary, without bloating binaries for everyone. When a program or library is built and linked, it can be built with debugging information, which debuggers can then use to map locations in the binary with locations in its source code; but this information takes up a lot of room. So debugging information is typically stripped from binaries before they're packaged. In recent years, [`strip`](https://sourceware.org/binutils/docs-2.29/binutils/strip.html#strip) and [`objcopy`](https://sourceware.org/binutils/docs-2.29/binutils/objcopy.html#objcopy) have been enhanced so that debugging information can be extracted and stored separately — that's how debug info packages are built. All that's needed then is some way of ensuring that a binary and its debug information correspond, and that's where build ids come in — they are unique identifiers calculated by [`ld`](https://sourceware.org/binutils/docs-2.29/ld/Options.html#Options) (look for `--build-id` there) over the significant portions of a binary. “Main build-id files” are symlinks from a build id to the corresponding binary or debug info file; they allow two-way mappings to be implemented, so that core dumps can be usefully debugged (there's a link from binaries to their build ids in the binaries themselves, in the `.gnu_debuglink` section). You'll find a detailed explanation of the reasoning behind all this in the [Fedora build-id feature description](https://fedoraproject.org/wiki/Releases/FeatureBuildId).



```
$ readelf -S ukui-indicators //没啥用
[28] .gnu_debuglink    PROGBITS         0000000000000000  0001b0f4
       0000000000000034  0000000000000000           0     0     4
 
 $ dpkg -L ukui-indicators-dbgsym
 /usr/lib/debug/.build-id/04/165df8cff97ce4a70ce9cb3738812bcee72c07.debug
 
 $ readelf -all ukui-indicators
 Displaying notes found in: .note.gnu.build-id
  所有者            Data size 	     Description
  GNU                0x00000014	NT_GNU_BUILD_ID (unique build ID bitstring)
  Build ID: 04165df8cff97ce4a70ce9cb3738812bcee72c07
```

