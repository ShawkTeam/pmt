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
#define INC_STAT
#define INC_DEBUGERS
#define INC_TOOLS_REQS
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>

namespace PartitionManager {
namespace Functions {

/**
 * it is meant to calculate the size of the quickly given file. 
 * its purpose is for rapid processing
 */
static double
CalculateSizeDouble(const string& fp)
{
    VLOGD("CalculateSizeDouble: calculating file size: `%s'\n", fp.c_str());

    VLOGD("CalculateSizeDouble: reading `%s' with 'ifstream <fstream>'\n", fp.c_str());
    ifstream target(fp, ios::binary | ios::ate);

    return (!target) ? -1 : static_cast<double>(target.tellg()) / (1024 * 1024);
}

static long long
CalculateSizeLongLong(const string& fp)
{
    VLOGD("CalculateSizeLongLong: calculating file size: `%s'\n", fp.c_str());

    VLOGD("CalculateSizeLongLong: reading `%s' with 'ifstream <fstream>'\n", fp.c_str());
    ifstream target(fp, ios::binary | ios::ate);

    return (!target) ? -1 : static_cast<long long>(target.tellg());
}

/**
 * error that the partition is not found. 
 * It's for quick action.
 */
static void
PartitionNotFound(const char* p) { LOGE("`%s': %s\n", p, Display::UsingDispString->part_not_found); }

/* the partitions are meant to quickly find. */
static void
SearchPartition(const string& fp)
{
    VLOGD("SearchPartition: calling GetState()...\n");
    static int op = GetState(fp, "blk");

    if (op == 1)
        PartitionNotFound(fp.c_str());
    else if (op == -1 && !Booleans::ForceMode)
        LOGE("%s\n", Display::UsingDispString->not_block);
}

} /* namespace Functions */
} /* namespace PartitionNotFound */

using namespace PartitionManager;

/* to stop use of function type */
#define PartitionNotFound Functions::PartitionNotFound()

int Functions::Start(unsigned short progress_code)
{
    /* required variables */
    static fstream sourceF;
    static fstream targetF;
    static string accessPrefix;
    static string opName;
    static int BFSIZE = 1;
    static char formatterCmd[200];
    static long long copiedData = 0;

    if (Booleans::UseLogical)
        accessPrefix = "/dev/block/mapper/" + Strings::TargetPartition;
    else
        accessPrefix = (Booleans::UseCustomContext) ? (Strings::CustomContext) + ("/") + (Strings::TargetPartition) : ("/dev/block/by-name/") + (Strings::TargetPartition);

    VLOGD("PartitionManager: calling SearchPartition() for searching partition (path); `%s'\n", accessPrefix.c_str());
    Functions::SearchPartition(accessPrefix);

    static long long count = (long long)(CalculateSizeLongLong(accessPrefix) + ((1024 * 1024) * 10));

    BFSIZE = (int)(CalculateSizeLongLong(accessPrefix) / (10240 * 10240));
    if (BFSIZE < 1)
        BFSIZE = 1;

    const int bfsize = BFSIZE;
    char buffer[bfsize];

    VLOGD("PartitionManager: calculating sizes...\n");
    double partition_size = Functions::CalculateSizeDouble(accessPrefix);
    double flashfile_size;

    if (!Strings::TargetFlashFile.empty())
        flashfile_size = Functions::CalculateSizeDouble(Strings::TargetFlashFile);

    if (progress_code < 3)
    {
        if (partition_size != -1)
            LOGD("%s: %.2fM\n", Display::UsingDispString->part_disk_sz, partition_size);
        else
            LOGW("%s\n", Display::UsingDispString->part_disk_sz_fail);
    }

    if (progress_code == 1)
    {
        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", accessPrefix.c_str());
        sourceF.open(accessPrefix, ios::binary | ios::in);
        if (!sourceF.is_open())
            LOGE("%s: %s: %s\n", Display::UsingDispString->not_read, accessPrefix.c_str(), strqerror());

        /* determine output */
        if (Strings::OutputName == Strings::TargetPartition)
        {
            opName = Strings::OutputName + ".img";
            VLOGW("PartitionManager: output not speficed. Selecting automaticly.\n");
            LOGW("%s: %s\n", Display::UsingDispString->out_not_spec, opName.c_str());
        }
        else
            opName = Strings::OutputName;

        VLOGD("Checking output status...\n");
        if (GetState(opName) == 0)
            LOGE("`%s': File exits.\n", opName.c_str());

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", opName.c_str());
        targetF.open(opName, ios::binary | ios::out);
        if (!targetF.is_open())
            LOGE("%s: %s: %s\n", Display::UsingDispString->not_gen, opName.c_str(), strqerror());

        VLOGD("PartitionManager: read (partition) and write (output) 'read, write <fstream>'\n");
        /* start writing */
        while (sourceF.read(buffer, bfsize) && copiedData < count)
        {
            streamsize readed_data = sourceF.gcount();
            targetF.write(buffer, readed_data);

            if (targetF.fail())
            {
                if (Functions::GetState(opName) == 0)
                    remove(opName.c_str());
                LOGF("%s: %s: %s\n", Display::UsingDispString->not_write, opName.c_str(), strqerror());
            }

            copiedData += readed_data;
        }

        /* close files */
        sourceF.close();
        targetF.close();

        LOGD("%s: %s\n", Display::UsingDispString->success_backup, opName.c_str());
    }
    else if (progress_code == 2)
    {
        if (flashfile_size != -1)
            LOGD("%s: %.2fM\n", Display::UsingDispString->flash_file_sz, flashfile_size);
        else
            LOGW("%s\n", Display::UsingDispString->flash_file_sz_fail);

        if (partition_size != -1 && flashfile_size != -1)
        {
            if (flashfile_size > partition_size && !Booleans::ForceMode)
                LOGE("%s\n", Display::UsingDispString->ffile_more_part);
        }

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", Strings::TargetFlashFile.c_str());
        sourceF.open(Strings::TargetFlashFile, ios::binary | ios::in);
        if (!sourceF.is_open())
            LOGF("%s: %s: %s\n", Display::UsingDispString->not_read, Strings::TargetFlashFile.c_str(), strqerror());

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", accessPrefix.c_str());
        targetF.open(accessPrefix, ios::binary | ios::in | ios::out | ios::trunc);
        if (!targetF.is_open())
            LOGF("%s: %s: %s\n", Display::UsingDispString->not_read, accessPrefix.c_str(), strqerror());

        VLOGD("PartitionManager: read (flash file) and write (partition) 'read, write <fstream>'\n");
        /* start writing */
        while (sourceF.read(buffer, bfsize) && copiedData < count)
        {
            streamsize readed_data = sourceF.gcount();
            targetF.write(buffer, readed_data);

            if (targetF.fail())
                LOGF("%s: %s: %s\n", Display::UsingDispString->not_write, accessPrefix.c_str(), strqerror());

            copiedData += readed_data;
        }

        sourceF.close();
        targetF.close();

        LOGD("%s.\n", Display::UsingDispString->success_flash);
    }
    else if (progress_code == 3)
    {
        /* get target partition block size */
        VLOGD("PartitionManager: getting block size `%s' with 'statvfs <sys/statvfs.h>'\n", accessPrefix.c_str());

        struct statvfs file_sys_inf;
        if (statvfs(accessPrefix.c_str(), &file_sys_inf) != 0)
            LOGE("%s\n", Display::UsingDispString->cannot_get_bsz);

        /* generate mke2fs command */
        VLOGD("PartitionManager: generating command...\n");
        sprintf(formatterCmd, "/system/bin/mke2fs -Fq -t %s -b %lu %s &>/data/local/tmp/mke2fs", Strings::TargetFormatFS.c_str(), file_sys_inf.f_bsize, accessPrefix.c_str());

        LOGD("%s: `%s'. %s: %s\n", Display::UsingDispString->formatting, accessPrefix.c_str(), Display::UsingDispString->fs_str, Strings::TargetFormatFS.c_str());

        /* run command */
        VLOGD("PartitionManager: executing command: \"%s\"\n", formatterCmd);
        if (system(formatterCmd) != 0)
            LOGF("%s\n", Display::UsingDispString->format_fail);

        LOGD("%s.\n", Display::UsingDispString->success_format);
    }

    return 0;
}

/* end of code */
