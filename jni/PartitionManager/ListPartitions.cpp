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

#define CUR_DEV_SP "/dev/block/by-name"
#define LGC_DEV_SP "/dev/block/mapper"

static DIR* Directory;

static int
ListDir(const string& TargetDir, const bool ListTargetDir = false)
{
    static int count;
    struct dirent **List;
    bool ListParts = (ListTargetDir) ? true : false;

    Directory = nullptr;
    Directory = opendir(TargetDir.c_str());

    if (ListParts)
    {
        count = scandir(TargetDir.c_str(), &List, nullptr, alphasort);

        if (count < 0)
            LOGE("%s: `%s': %s\n",
                Display::UsingDispString->not_readdir,
                TargetDir.c_str(),
                strqerror());

        for (int i = 0; i < count; i++)
        {
            if (List[i]->d_name[0] != '.'
                && strncmp(List[i]->d_name, "com.", 4) != 0
                && strcmp(List[i]->d_name, "by-uuid") != 0
                && strcmp(List[i]->d_name, "userdata") != 0)
                LOGD(" - [ %-16s ]\n", List[i]->d_name);

            free(List[i]);
        }

        free(List);
        List = nullptr;

        goto directory;
    }

directory:
    if (Directory != nullptr)
    {
        closedir(Directory);
        return 0;
    }
    else
        return -1;

    return 2;
}

/* list existing partitions */
int Functions::ListPartitions(void)
{
    VLOGD("ListPartitions: selecting search path...\n");
    string AccessDir = (Booleans::UseCustomSearchPath) ? Strings::CustomSearchPath : CUR_DEV_SP;

    VLOGD("ListPartitions: trying to access `%s'...\n", AccessDir.c_str());
    if (ListDir(AccessDir) != 0)
    {
        if (!Booleans::ForceMode)
            LOGE("%s: `%s': %s\n",
                Display::UsingDispString->not_open,
                AccessDir.c_str(),
                strqerror());
        else
            return 1;
    }
    else
    {
        LOGD("%s:\n", Display::UsingDispString->list_of_general);
        ListDir(AccessDir, true);
    }

    if (Booleans::UsesLogical)
    {
        VLOGD("ListPartitions: checking for listing `%s'...\n", LGC_DEV_SP);

        if (ListDir(LGC_DEV_SP) != 0)
            LOGE("%s: `%s': %s\n",
                Display::UsingDispString->not_open,
                LGC_DEV_SP,
                strqerror());
        else
        {
            LOGD("\n%s:\n", Display::UsingDispString->list_of_logc);
            ListDir(LGC_DEV_SP, true);
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
