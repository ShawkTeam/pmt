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

#define INC_MAIN_LIBS
#define INC_DEBUGERS
#define INC_DIRENT
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>

using namespace PartitionManager;

#define CUR_DEV_CNTX "/dev/block/by-name"
#define LGC_DEV_CNTX "/dev/block/mapper"

static DIR *dir;

static int
list(const string& operation, const char* target_dir)
{
    static int count;
    struct dirent **list;
    bool list_parts = (operation == "print") ? true : false;

    dir = nullptr;
    dir = opendir(target_dir);

    if (list_parts)
    {
        count = scandir(target_dir, &list, nullptr, alphasort);

        if (count < 0)
            LOGE("%s: `%s': %s\n", Display::UsingDispString->not_readdir, target_dir, strqerror());

        for (int i = 0; i < count; i++)
        {
            if (list[i]->d_name[0] != '.' \
            && strncmp(list[i]->d_name, "com.", 4) != 0 \
            && strcmp(list[i]->d_name, "by-uuid") != 0 \
            && strcmp(list[i]->d_name, "userdata") != 0)
                LOGD(" - [ %-16s ]\n", list[i]->d_name);

            free(list[i]);
        }

        free(list);
        list = nullptr;

        goto directory;
    }

directory:
    if (dir != nullptr)
    {
        closedir(dir);
        return 0;
    }
    else
        return -1;

    return 2;
}

/* list existing partitions */
int Functions::ListPartitions(void)
{
    VLOGD("ListPartitions: selecting context...\n");
    string acc_cxt = (Booleans::UseCustomContext) ? Strings::CustomContext : CUR_DEV_CNTX;

    VLOGD("ListPartitions: trying to access `%s'...\n", acc_cxt.c_str());
    if (list("access", acc_cxt.c_str()) != 0)
    {
        if (!Booleans::ForceMode)
            LOGE("%s: `%s': %s\n", Display::UsingDispString->not_open, acc_cxt.c_str(), strqerror());
        else
            return 1;
    }
    else
    {
        LOGD("%s:\n", Display::UsingDispString->list_of_general);
        list("print", acc_cxt.c_str());
    }

    if (Booleans::UsesLogical)
    {
        VLOGD("ListPartitions: checking for listing `%s'...\n", LGC_DEV_CNTX);

        if (list("access", LGC_DEV_CNTX) != 0)
            LOGE("%s: `%s': %s\n", Display::UsingDispString->not_open, LGC_DEV_CNTX, strqerror());
        else
        {
            LOGD("\n%s:\n", Display::UsingDispString->list_of_logc);
            list("print", LGC_DEV_CNTX);
        }
    }

    VLOGD("ListPartitions: (if have) warnings are printed...\n");

    if (Booleans::UsesLogical)
    {
        LOGD("\n");
        LOGW("%s\n", Display::UsingDispString->logical_warn);
    }

    if (Booleans::UsesSlots)
    {
        if (!Booleans::UsesSlots)
            LOGD("\n");

        LOGW("%s\n", Display::UsingDispString->ab_warn);
    }

    return 0;
}

/* end of code */
