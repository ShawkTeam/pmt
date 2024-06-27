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

#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_DEBUGERS
#define INC_DIRENT

#include <pmt.h>

/* current /dev context */
#define CUR_DEV_CNTX "/dev/block/by-name"

/* for logical partitions */
#define LGC_DEV_CNTX "/dev/block/mapper"

extern bool pmt_use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_silent;
extern bool pmt_force_mode;
extern char* cust_cxt;
extern char* bin_name;

extern struct pmt_langdb_general* current;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;

DIR *dir;

static int
list(const char* operation, const char* target_dir)
{
    static bool list = false;
    struct dirent *entry;
    dir = NULL;

    if (strcmp(operation, "access") == 0) list = false;
    else if (strcmp(operation, "print") == 0) list = true;
    else return -1;

    dir = opendir(target_dir);
    if (dir != NULL)
    {
        if (!list)
        {
            closedir(dir);
            return 0;
        }
        else
        {
            printf("%s: `%s'\n", current->list_of_dir, target_dir);
            while ((entry = readdir(dir)) != NULL) printf("%s\n", entry->d_name);
            closedir(dir);
            return 0;
        }
    }
    else return -1;

    return 2;
}

/* list existing partitions */
int listpart(void) {
    if (pmt_use_cust_cxt)
    {
        if (list("access", cust_cxt) != 0)
        {
            if (!pmt_force_mode) error(1, "%s: `%s': %s", current->not_open, cust_cxt, strerror(errno));
            else return 1;
        }
        else list("print", cust_cxt);
    }
    else
    {
        if (list("access", CUR_DEV_CNTX) != 0)
        {
            if (!pmt_force_mode) error(1, "%s: `%s': %s", current->not_open, CUR_DEV_CNTX, strerror(errno));
            else return 1;
        }
        else list("print", CUR_DEV_CNTX);
    }

    if (pmt_logical)
    {
        if (list("access", LGC_DEV_CNTX) != 0) 
        {
            if (!pmt_silent) error(1, "%s: `%s': %s", current->not_open, LGC_DEV_CNTX, strerror(errno));
            else return 1;
        }
        else list("print", LGC_DEV_CNTX);
    }

    if (pmt_ab && !pmt_silent) printf("%s: %s\n", bin_name, current->ab_warn);

    if (pmt_logical && !pmt_silent) printf("%s: %s\n", bin_name, current->logical_warn);

    return 0;
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */