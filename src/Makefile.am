lib_LTLIBRARIES = libzbxlinux.la

libzbxlinux_la_SOURCES = \
	libzbxlinux.h \
	libzbxlinux.c \
	ksm.c

libzbxlinux_la_CFLAGS = \
	$(ZABBIX_CPPFLAGS)

libzbxlinux_la_LDFLAGS = \
	-shared \
	-avoid-version

# Prevent install of the redundant *.la files
install-exec-hook:
	rm -f $(DESTDIR)$(libdir)/libzbxlinux.la

# Fix "files left after uninstall" issue
uninstall-local:
	rm -f $(DESTDIR)$(libdir)/libzbxlinux.so
