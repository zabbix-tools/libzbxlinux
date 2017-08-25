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

#include "libzbxlinux.h"

/*
 * See:
 *   https://www.kernel.org/doc/Documentation/sysctl/fs.txt
 */

#define FILENR_PATH "/proc/sys/fs/file-nr"

int LINUX_FS_FILENR(AGENT_REQUEST *request, AGENT_RESULT *result)
{
	int ret = SYSINFO_RET_FAIL;
	const char *metrics[] = { "allocated", "free", "max", NULL };
	char *metric = NULL;
	int i = 0;
	FILE *f = NULL;
	uint64 val[3];

    if(1 < request->nparam) {
		SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid number of parameters"));
		return ret;
    }

    if (metric = get_rparam(request, 0)) {
		for (i = 0; metrics[i]; i++)
			if (0 == strncmp(metrics[i], metric, 10)) // 10 = max len in metrics
				break;

		if (NULL == metrics[i]) {
			SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Unsupported parameter: %s", metric));
			return ret;
		}
	}

	if(NULL == (f = fopen(FILENR_PATH, "r"))) {
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot open " FILENR_PATH ": %s", zbx_strerror(errno)));
		return ret;
	}

	if(3 == fscanf(f, "%llu %llu %llu", &val[0], &val[1], &val[2])) {
		SET_UI64_RESULT(result, val[i]);
		ret = SYSINFO_RET_OK;
	} else {
		SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Error parsing " FILENR_PATH));
	}
	fclose(f);

	return ret;
}