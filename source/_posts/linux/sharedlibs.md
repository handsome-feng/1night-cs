The following command, when run on a shared library, will output the name to be used for the Debian package containing that shared library:
```
objdump -p /usr/lib/x86_64-linux-gnu/libGLU.so.1.3.1  \
    | sed -n -e's/^[[:space:]]*SONAME[[:space:]]*//p' \
    | LC_ALL=C sed -r -e's/([0-9])\.so\./\1-/; s/\.so(\.|$)//; y/_/-/; s/(.*)/\L&/'
```
It is recommended that supporting files and run-time support programs that do not need to be invoked manually by users, but are nevertheless required for the package to function, be placed (if they are binary) in a subdirectory of /usr/lib, preferably under /usr/lib/package-name. If the program or file is architecture independent, the recommendation is for it to be placed in a subdirectory of /usr/share instead, preferably under /usr/share/package-name. Following the package-name naming convention ensures that the file names change when the shared object version changes.

symbols files are therefore recommended for most shared library packages since they provide more accurate dependencies. For most C libraries, the additional detail required by symbols files is not too difficult to maintain. However, maintaining exhaustive symbols information for a C++ library can be quite onerous, so shlibs files may be more appropriate for most C++ libraries. Libraries with a corresponding udeb must also provide a shlibs file, since the udeb infrastructure does not use symbols files.

dpkg-shlibdeps
dpkg-shlibdeps will use a program like **objdump** or **readelf** to find the libraries and the symbols in those libraries directly needed by the binaries or shared libraries in the package.

The easiest way to call `dpkg-shlibdeps` correctly is to use a package helper framework such as debhelper. If you are using debhelper, the `dh_shlibdeps` program will do this work for you. It will also correctly handle multi-binary packages.



${shlibs:Depends}



### The symbols system

### The shlibs system

https://www.debian.org/doc/debian-policy/ch-sharedlibs.html

A shared library is identified by the `SONAME` attribute stored in its dynamic section.

When a binary is linked against a shared library, the `SONAME` of the shared library is recorded in the binary’s `NEEDED` section so that the dynamic linker knows that library must be loaded at runtime. 

The shared library file’s full name (which usually contains additional version information not needed in the `SONAME`) is therefore normally not referenced directly. Instead, the shared library is loaded by its `SONAME`, which exists on the file system as a symlink pointing to the full name of the shared library. 