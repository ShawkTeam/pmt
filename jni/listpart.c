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

#ifdef __cplusplus
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_DEBUGERS
#define INC_DIRENT

#include <pmt/PartitionManager.h>
#include <pmt/StringKeys.h>

/* current /dev context */
#define CUR_DEV_CNTX "/dev/block/by-name"

/* for logical partitions */
#define LGC_DEV_CNTX "/dev/block/mapper"

static DIR *dir;

static int
list(const char* operation, const char* target_dir)
{
    static bool list = false;
    static int count;
    struct dirent **nlist;
    dir = NULL;

    if (strcmp(operation, "access") == 0)
        list = false;
    else if (strcmp(operation, "print") == 0)
        list = true;
    else
        return -1;

    dir = opendir(target_dir);

    if (dir != NULL)
    {
        closedir(dir);
        return 0;
    }
    else
        return -1;

    if (list)
    {
        count = scandir(target_dir, &nlist, NULL, alphasort);

        if (count < 0)
            LOGE("%s: `%s': %s\n", current->not_readdir, target_dir, strerror(errno));

        for (int cont_count = 0; cont_count < count; cont_count++)
        {
            if (nlist[cont_count]->d_name[0] != '.')
                LOGD("%s\n", nlist[cont_count]->d_name);

            free(nlist[cont_count]);
        }

        free(nlist);

        return 0;
    }

    return 2;
}

/* list existing partitions */
int listpart(void)
{
    static char acc_cxt[350];

    if (pmt_use_cust_cxt)
        sprintf(acc_cxt, "%s", cust_cxt);
    else
        sprintf(acc_cxt, "%s", CUR_DEV_CNTX);

    if (list("access", acc_cxt) != 0)
    {
        if (!pmt_force_mode)
            LOGE("%s: `%s': %s\n", current->not_open, acc_cxt, strerror(errno));
        else
            return 1;
    }
    else
        list("print", acc_cxt);

    if (pmt_logical)
    {
        if (list("access", LGC_DEV_CNTX) != 0) 
            LOGE("%s: `%s': %s\n", current->not_open, LGC_DEV_CNTX, strerror(errno));
        else
            list("print", LGC_DEV_CNTX);
    }

    if (pmt_ab)
        LOGD("%s: %s\n", bin_name, current->ab_warn);

    if (pmt_logical)
        LOGD("%s: %s\n", bin_name, current->logical_warn);

    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* end of code */
