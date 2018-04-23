bin_PROGRAMS = \
    tcpserv01 \
	tcpcli01 \
	$(NULL)

AM_CPPFLAGS = \
    -I$(top_builddir)/lib \
	-g -O0 \
	$(NULL)

LDADD = \
    $(top_builddir)/lib/libunp.la \
	$(NULL)

tcpserv01_SOURCES = \
    tcpserv01.c \
	$(NULL)

tcpcli01_SOURCES = \
    tcpcli01.c\
    $(NULL)
