/*
** libzbxlinux - A Linux kernel extension module for Zabbix
** Copyright (C) 2015 - Ryan Armstrong <ryan@cavaliercoder.com>
**
** This program is free software; you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation; either version 2 of the License, or
** (at your option) any later version.
**
** This program is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with this program; if not, write to the Free Software
** Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
**/

#ifndef LIBZBXLINUX_H
#define LIBZBXLINUX_H

// fix
#define HAVE_TIME_H	1

#include <stdio.h>
#include <errno.h>

// Zabbix source headers
#include <sysinc.h>
#include <module.h>
#include <common.h>
#include <log.h>
#include <zbxjson.h>

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

typedef unsigned long long int uint64;

int LINUX_KSM(AGENT_REQUEST *request, AGENT_RESULT *result);
int LINUX_FS_FILENR(AGENT_REQUEST *request, AGENT_RESULT *result);

#endif // LIBZBXLINUX_H
