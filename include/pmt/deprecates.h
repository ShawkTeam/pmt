/* By YZBruh */

/**
 * Copyright 2024 Partition Manager
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef __PMT_DEPRECATED_H
#define __PMT_DEPRECATED_H

#include <sys/cdefs.h>

__BEGIN_DECLS

#define deprecated_opt   1
#define changed_opt      2
#define end_depr_pointer 0
#define not_changed      0
#define not_changed_long NULL

/* versions */
#define v150 "1.5.0"
#define v160 "1.6.0"
#define v170 "1.7.0"
#define v180 "1.8.0"
#define v190 "1.9.0"
#define v200 "2.0.0"
#define v210 "2.1.0"
#define v220 "2.2.0"
#define v230 "2.3.0"
#define v240 "2.4.0"
#define v250 "2.5.0"
#define vUNK NULL

struct pmt_deprecates {
    int depr_type;
    int option;
    int option_new;
    const char* option_long;
    const char* option_long_new;
    const char* depr_version;
};

static void
__deprecated_opt_handle(int opt, const char* opt_long, const char* depr_msg)
{
    static char long_e_msg[250];

    static struct pmt_deprecates depr_table[] = {
        {deprecated_opt, 'b', not_changed, "backup", not_changed_long, v210},
        {deprecated_opt, 'F', not_changed, "flash", not_changed_long, v210},
        {deprecated_opt, 'r', not_changed, "format", not_changed_long, v210},
        {deprecated_opt, 'L', not_changed, "license", not_changed_long, v250},
        {changed_opt, 'D', 'p', "list", not_changed_long, v210},
        {end_depr_pointer, not_changed, not_changed, not_changed_long, not_changed_long, vUNK}
    };

    if (opt_long == NULL)
        sprintf(long_e_msg, "%s", current->not_changed_opt);
    else
        sprintf(long_e_msg, "%s", opt_long);

    for (int optctrl = 0; depr_table[optctrl].depr_type != 0; optctrl++)
    {

        if (depr_table[optctrl].depr_type == 1)
        {
            if (opt == depr_table[optctrl].option || strcmp(opt_long, depr_table[optctrl].option_long) == 0)
                LOGD("%s [%s]: -%c (%s): %s\n", current->depr_opt_str, depr_table[optctrl].depr_version, (char)depr_table[optctrl].option, depr_table[optctrl].option_long, depr_msg);

        }
        else if (depr_table[optctrl].depr_type == 2)
        {
            if (opt == depr_table[optctrl].option || strcmp(opt_long, depr_table[optctrl].option_long) == 0)
                LOGD("%s [%s]: -%c (%s): %s\n", current->switched_opt_str, depr_table[optctrl].depr_version, (char)depr_table[optctrl].option, long_e_msg, depr_msg);

        }

    }
}

#define DEPR_HANDLE(x, y, z) __deprecated_opt_handle(x, y, z)

__END_DECLS

#endif

/* end of code */
