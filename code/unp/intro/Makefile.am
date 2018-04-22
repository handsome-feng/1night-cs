bin_PROGRAMS = \
    cli \
	srv1 \
	$(NULL)

AM_CPPFLAGS = \
    -I$(top_builddir)/lib \
	$(NULL)

LDADD = \
    $(top_builddir)/lib/libunp.la \
	$(NULL)

cli_SOURCES = \
    daytimetcpcli.c \
	$(NULL)

srv1_SOURCES = \
    daytimetcpsrv1.c \
	$(NULL)
