EXTRA_DIST = module_linux.conf

install-exec-local:
	$(MKDIR_P) $(DESTDIR)$(sysconfdir)/zabbix/zabbix_agentd.d/
	$(INSTALL) -m 0640 module_linux.conf $(DESTDIR)$(sysconfdir)/zabbix/zabbix_agentd.d/module_linux.conf
