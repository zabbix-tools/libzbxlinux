ACLOCAL_AMFLAGS = -I m4

SUBDIRS = \
	conf \
	src

EXTRA_DIST = \
	COPYING \
	README.md

#install-exec-local:
#	$(INSTALL) -m 0644 COPYING $(DESTDIR)/usr/share/doc/$(PACKAGE_NAME)-$(PACKAGE_VERSION)/COPYING
#	$(INSTALL) -m 0644 README.md $(DESTDIR)/usr/share/doc/$(PACKAGE_NAME)-$(PACKAGE_VERSION)/README.md

rpm: dist
	mkdir -p ~/rpmbuild/SPECS
	mkdir -p ~/rpmbuild/SOURCES
	install -m 644 $(PACKAGE_NAME).spec ~/rpmbuild/SPECS/$(PACKAGE_NAME).spec
	install -m 644 \
		$(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz \
		~/rpmbuild/SOURCES/$(PACKAGE_NAME)-$(PACKAGE_VERSION).tar.gz
	rpmbuild -ba ~/rpmbuild/SPECS/$(PACKAGE_NAME).spec
