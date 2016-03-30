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
int     SYSTEM_KSM(AGENT_REQUEST *request, AGENT_RESULT *result)
{
    int         ret = SYSINFO_RET_FAIL;             // Request result code
    const char  *__function_name = "SYSTEM_KSM";    // Function name for log file

    // ksm files
    const char  *ksm_dir = "/sys/kernel/mm/ksm";
    const int   ksm_file_count = 9;
    const char  *ksm_files[] = { 
        "full_scans", 
        "merge_across_nodes", 
        "pages_shared", 
        "pages_sharing", 
        "pages_to_scan",
        "pages_unshared", 
        "pages_volatile",
        "run",
        "sleep_millisecs"
    };

    int     i = 0;
    FILE    *fp = NULL;
    char    *metric = NULL;
    char    buf[MAX_STRING_LEN];
    unsigned long long val = 0;
    
    zabbix_log(LOG_LEVEL_DEBUG, "In %s()", __function_name);

    // check parameter count
    if(1 != request->nparam) {
        SET_MSG_RESULT(result, strdup("Invalid number of parameters"));
        goto out;
    }

    // get requested metric
    metric = get_rparam(request, 0);
    if (NULL == metric || '\0' == *metric) {
        SET_MSG_RESULT(result, strdup("No metric defined"));
        goto out;        
    }
    
    // is request a known file in /sys/kernel/mm/ksm?
    for(i = 0; i < ksm_file_count; i++) {
        if (0 == strcmp(ksm_files[i], metric)) {
            // compute full path
            zbx_snprintf(buf, sizeof(buf), "%s/%s", ksm_dir, metric);

            // open file
            if(NULL == (fp = fopen(buf, "r"))) {
                SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Cannot open %s: %s", buf, zbx_strerror(errno)));
            } else {
                // read llu value
                if(1 != fscanf(fp, "%llu", &val)) {
                    SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Unsupported format in %s", buf));
                } else {
                    // set result value
                    SET_UI64_RESULT(result, val);
                    ret = SYSINFO_RET_OK;
                }

                // close file handle
                fclose(fp);
            }

            goto out;
        }
    }

    // if we're here, an unknown metric was requested
    SET_MSG_RESULT(result, zbx_dsprintf(NULL, "Unsupported parameter: %s", metric));
    goto out;

out:
    zabbix_log(LOG_LEVEL_DEBUG, "End of %s()", __function_name);
    return ret;
}
