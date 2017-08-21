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
 * Requires: >= v2.6.32
 *
 * See:
 *   https://www.kernel.org/doc/Documentation/vm/ksm.txt
 *   https://www.kernel.org/doc/ols/2009/ols2009-pages-19-28.pdf
 */
int LINUX_KSM(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    const char *ksm_dir = "/sys/kernel/mm/ksm";
    const char *ksm_files[] = {
        "full_scans",
        "merge_across_nodes",
        "pages_shared",
        "pages_sharing",
        "pages_to_scan",
        "pages_unshared",
        "pages_volatile",
        "run",
        "sleep_millisecs",
        NULL
    };

    int         ret = SYSINFO_RET_FAIL;
    FILE        *f = NULL;
    const char  *metric = NULL, *c = NULL;
    char        path[64];
    uint64      val = 0;

    if(1 != request->nparam) {
        SET_MSG_RESULT(result, zbx_strdup(NULL, "Invalid number of parameters"));
        goto OUT;
    }

    metric = get_rparam(request, 0);
    if (NULL == metric || '\0' == *metric) {
        SET_MSG_RESULT(result, zbx_strdup(NULL, "No metric defined"));
        goto OUT;
    }

    for (c = ksm_files[0]; *c; c++)
        if (0 == strncmp(c, metric, 19)) // 19 = max len in ksm_files
            break;

    if (NULL == c) {
        SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Unsupported parameter: %s", metric));
        goto OUT;
    }

    zbx_snprintf(path, sizeof(path), "%s/%s", ksm_dir, metric);
    if(NULL == (f = fopen(path, "r"))) {
        SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot open %s: %s", path, zbx_strerror(errno)));
        goto OUT;
    }

    if(1 != fscanf(f, "%llu", &val)) {
        SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Error parsing %s", path));
        goto OUT;
    }

    SET_UI64_RESULT(result, val);
    ret = SYSINFO_RET_OK;

OUT:
    if (NULL != f) {
        fclose(f);
    }
    return ret;
}
