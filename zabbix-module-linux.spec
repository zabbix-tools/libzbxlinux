Name          : zabbix-module-linux
Vendor        : cavaliercoder
Version       : 0.0.1
Release       : 1
Summary       : Linux kernel internals monitoring with Zabbix

Group         : Applications/Internet
License       : GNU GPLv2
URL           : https://github.com/cavaliercoder/libzbxlinux

Source0       : %{name}-%{version}.tar.gz
Buildroot     : %{_tmppath}/%{name}-%{version}-%{release}-root-%(%{__id_u} -n)
Requires      : zabbix-agent >= 3.2.0
#BuildRequires : selinux-policy-devel

%define module libzbxlinux

%description
zabbix-module-linux is a loadable Zabbix module and monitoring template that
enables Zabbix to interrogate the Linux kernel.

%prep
%setup0 -q -n %{name}-%{version}

# fix up some lib64 issues
sed -i.orig -e 's|_LIBDIR=/usr/lib|_LIBDIR=%{_libdir}|g' configure

%build
%configure --enable-dependency-tracking
make %{?_smp_mflags}

%install
rm -rf $RPM_BUILD_ROOT
make DESTDIR=$RPM_BUILD_ROOT install

%clean
rm -rf $RPM_BUILD_ROOT

%files
%{_libdir}/zabbix/modules/%{module}.so
%{_sysconfdir}/zabbix/zabbix_agentd.d/module_linux.conf
#%{_docdir}/%{name}-%{version}/README.md
#%{_docdir}/%{name}-%{version}/COPYING

%changelog
* Fri Aug 25 2017 Ryan Armstrong <ryan@cavaliercoder.com> 0.0.1-1
- Initial release
