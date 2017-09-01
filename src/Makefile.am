lib_LTLIBRARIES = libzbxlinux.la

libzbxlinux_la_SOURCES = \
	libzbxlinux.h \
	libzbxlinux.c \
	fs.c \
	ksm.c

libzbxlinux_la_CFLAGS = \
	$(ZABBIX_CPPFLAGS)

libzbxlinux_la_LDFLAGS = \
	-shared \
	-avoid-version

# Prevent install of the redundant *.la files
install-exec-hook:
	$(RM) $(DESTDIR)$(libdir)/libzbxlinux.la
	$(MKDIR_P) $(DESTDIR)/$(libdir)/zabbix/modules
	mv $(DESTDIR)$(libdir)/libzbxlinux.so $(DESTDIR)$(libdir)/zabbix/modules/libzbxlinux.so

# Fix "files left after uninstall" issue
uninstall-local:
	$(RM) $(DESTDIR)$(libdir)/libzbxlinux.so
