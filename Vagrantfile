# -*- mode: ruby -*-
# vi: set ft=ruby :

Vagrant.configure(2) do |config|
  config.vm.box = "ubuntu/trusty64"
  config.vm.box_check_update = false

  config.vm.provision "shell", inline: <<-SHELL
    export DEBIAN_FRONTEND=noninteractive
    wget http://repo.zabbix.com/zabbix/3.0/ubuntu/pool/main/z/zabbix-release/zabbix-release_3.0-1+trusty_all.deb
    dpkg -i zabbix-release_3.0-1+trusty_all.deb
    apt-get update
    apt-get install -y \
      autoconf \
      automake \
      gcc \
      gdb \
      libtool \
      m4 \
      make \
      zabbix-agent
  SHELL
end
