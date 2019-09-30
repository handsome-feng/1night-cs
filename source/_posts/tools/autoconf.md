---
title: autoconf
---



The configuration scripts produced by Autoconf are independent of Autoconf when they are run, so their users do not need to have Autoconf. 

 

Autoconf requirements_x000D_     AC_INIT(package, version, bug-report-address)_x000D_     information on the package_x000D_     checks for programs_x000D_     checks for libraries_x000D_     checks for header files_x000D_     checks for types_x000D_     checks for structures_x000D_     checks for compiler characteristics_x000D_     checks for library functions_x000D_     checks for system services_x000D_     AC_CONFIG_FILES([file...])_x000D_     AC_OUTPUT

 

 if you want the package to use a configuration header file, you must add a call to AC_CONFIG_HEADERS

 

When using autoscan to maintain a configure.ac, simply consider adding its suggestions. The file autoscan.log contains detailed information on why a macro is requested.

 

### **Using ifnames to List Conditionals**

 

. If you give autoconf an argument, it reads that file instead of configure.ac and writes the configuration script to the standard output instead of to configure. If you give autoconf the argument -, it reads from the standard input instead of configure.ac and writes the configuration script to the standard output.

 

Some of the files are distributed with Autoconf; autoconf reads them first. Then it looks for the optional file acsite.m4 in the directory that contains the distributed Autoconf macro files, and for the optional file aclocal.m4 in the current directory. 