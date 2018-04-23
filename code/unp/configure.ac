AC_INIT([unp], [1.0.0])
AC_CONFIG_HEADERS(config.h)

AM_INIT_AUTOMAKE([1.9])

LT_INIT
AC_PROG_CC
dnl The following cpu_vendor_os string goes into config.h.
AC_DEFINE_UNQUOTED(CPU_VENDOR_OS, "$host", [CPU, vendor, and operating system])

LIBUNP_CFLAGS=""
AC_SUBST(LIBUNP_CFLAGS)

AC_OUTPUT(
Makefile
lib/Makefile
intro/Makefile
tcpcliserv/Makefile)
