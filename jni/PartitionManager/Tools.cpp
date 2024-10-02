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
#define INC_LIBGEN
#define INC_DEBUGERS
#define INC_TOOLS_REQS
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/PartSizeMacros.h>
#include <PartitionManager/FileSystemUtils.h>

namespace PartitionManager {
namespace Functions {

/**
 * it is meant to calculate the size of the quickly given file. 
 * its purpose is for rapid processing
 */
static long long
CalculateSizeLongLong(const string& fp)
{
    VLOGD("CalculateSizeLongLong: calculating file size: `%s'\n", fp.c_str());

    VLOGD("CalculateSizeLongLong: reading `%s' with 'ifstream <fstream>'\n", fp.c_str());
    ifstream file(fp, ios::binary | ios::ate);

    return (!file) ? -1 : static_cast<long long>(file.tellg());
}

/**
 * error that the partition is not found. 
 * It's for quick action.
 */
static void
PartitionNotFound(const char* p) { LOGE("%s: %s\n", p, Display::UsingDispString->part_not_found); }

/* the partitions are meant to quickly find. */
static void
SearchPartition(const string& fp)
{
    VLOGD("SearchPartition: calling GetState()...\n");
    static int op = GetState(fp, "blk");

    if (op == 1)
        PartitionNotFound(basename(fp.c_str()));
    else if (op == -1 && !Booleans::ForceMode)
        LOGE("%s\n", Display::UsingDispString->not_block);
}

static void
PrintInfo(ushort_t pcode, double psz, double fsz)
{
    LOGD("##########################################\n");
    LOGD("# --> %s: %s\n",
        Display::UsingDispString->part_name,
        Strings::TargetPartition.c_str());
    LOGD("# --> %s: %s\n",
        Display::UsingDispString->part_type,
        (Booleans::UseLogical) ? Display::UsingDispString->yes : Display::UsingDispString->no);

    if (psz != -1)
        LOGD("# --> %s: %.2fMB\n", 
            Display::UsingDispString->part_disk_sz,
            psz);
    else
        LOGD("# --> %s: %s\n",
            Display::UsingDispString->warn,
            Display::UsingDispString->part_disk_sz_fail);

    if (pcode == 3)
    {
        if (fsz != -1)
            LOGD("# --> %s: %.2fMB\n",
                Display::UsingDispString->flash_file_sz,
                fsz);
        else
            LOGW("# --> %s: %s\n",
                Display::UsingDispString->warn,
                Display::UsingDispString->flash_file_sz_fail);
    }

    LOGD("##########################################\n");
}

static bool
IsDoubleOf1024(float size)
{
    float num = size / 1024;
    char str[35];
    sprintf(str, "%f", num);

    return (strstr(str, ".000000") != nullptr) ? true : false;
}

} /* namespace Functions */
} /* namespace PartitionManager */

using namespace PartitionManager;

int Functions::Start(ushort_t progress_code)
{
    /* Some required variables */
    fstream sourceF, targetF;
    string accessPrefix, opName;
    long long copiedData = 0;
    bool IsFirstProcessOnTarget = true;

    if (Booleans::UseLogical)
        accessPrefix = "/dev/block/mapper/" + Strings::TargetPartition;
    else
        accessPrefix = (Booleans::UseCustomSearchPath) ? (Strings::CustomSearchPath) + ("/") + (Strings::TargetPartition) : ("/dev/block/by-name/") + (Strings::TargetPartition);

    VLOGD("PartitionManager: calling SearchPartition() for searching partition (path); `%s'\n", accessPrefix.c_str());
    Functions::SearchPartition(accessPrefix);

    static long long count = (long long)(CalculateSizeLongLong(accessPrefix) + ((1024 * 1024) * 4));
    const int BFSIZE = (Functions::IsDoubleOf1024((float)Functions::CalculateSizeLongLong(accessPrefix))) ? 1024 : 1;
    char buffer[BFSIZE];
    double FlashFileSize = 0;

    double PartitionSize = (double)(static_cast<double>(Functions::CalculateSizeLongLong(accessPrefix)) / (1024 * 1024));
    if (!Strings::TargetFlashFile.empty())
        FlashFileSize = (double)(static_cast<double>(Functions::CalculateSizeLongLong(Strings::TargetFlashFile)) / (1024 * 1024));

    if (progress_code != 4) PrintInfo(progress_code, PartitionSize, FlashFileSize);

    if (progress_code == 1)
    {
        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", accessPrefix.c_str());
        sourceF.open(accessPrefix, ios::binary | ios::in);
        if (!sourceF.is_open())
            LOGE("%s: %s: %s\n", 
                Display::UsingDispString->not_read,
                accessPrefix.c_str(),
                strqerror());

        /* determine output */
        if (Strings::OutputName == Strings::TargetPartition)
        {
            opName = Strings::OutputName + ".img";
            VLOGW("PartitionManager: output not speficed. Selecting automaticly.\n");
            LOGW("%s: %s\n",
                Display::UsingDispString->out_not_spec,
                opName.c_str());
        }
        else
            opName = Strings::OutputName;

        VLOGD("Checking output status...\n");
        if (GetState(opName) == 0)
            LOGE("'%s': File exits.\n", opName.c_str());

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", opName.c_str());
        targetF.open(opName, ios::binary | ios::out);
        if (!targetF.is_open())
            LOGE("%s: %s: %s\n",
            Display::UsingDispString->not_gen,
            opName.c_str(),
            strqerror());

        VLOGD("PartitionManager: read (partition) and write (output) 'read, write <fstream>'\n");
        /* start writing */
        while (sourceF.read(buffer, BFSIZE) && copiedData < count)
        {
            if (GetState(opName) != 0 && IsFirstProcessOnTarget)
                LOGE("%s\n", Display::UsingDispString->no_found_on_process);

            streamsize readed_data = sourceF.gcount();
            targetF.write(buffer, readed_data);

            if (targetF.fail() || targetF.bad())
            {
                if (Functions::GetState(opName) == 0)
                    remove(opName.c_str());
                LOGF("%s: %s: %s\n",
                    Display::UsingDispString->not_write,
                    opName.c_str(),
                    strqerror());
            }

            IsFirstProcessOnTarget = false;
            copiedData += readed_data;
        }

        /* close files */
        sourceF.close();
        targetF.close();

        LOGD("%s: %s\n", 
            Display::UsingDispString->success_backup,
            opName.c_str());
    }
    else if (progress_code == 2)
    {
        if (PartitionSize != -1 && FlashFileSize != -1)
        {
            if (FlashFileSize > PartitionSize && !Booleans::ForceMode)
                LOGE("%s\n", Display::UsingDispString->ffile_more_part);
        }

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", Strings::TargetFlashFile.c_str());
        sourceF.open(Strings::TargetFlashFile, ios::binary | ios::in);
        if (!sourceF.is_open())
            LOGF("%s: %s: %s\n", 
                Display::UsingDispString->not_read,
                Strings::TargetFlashFile.c_str(),
                strqerror());

        VLOGD("PartitionManager: trying to open `%s' with 'open <fstream>'.\n", accessPrefix.c_str());
        targetF.open(accessPrefix, ios::binary | ios::in | ios::out | ios::trunc);
        if (!targetF.is_open())
            LOGF("%s: %s: %s\n",
                Display::UsingDispString->not_read,
                accessPrefix.c_str(),
                strqerror());

        VLOGD("PartitionManager: read (flash file) and write (partition) 'read, write <fstream>'\n");
        /* start writing */
        while (sourceF.read(buffer, BFSIZE) && copiedData < count)
        {
            streamsize readed_data = sourceF.gcount();
            targetF.write(buffer, readed_data);

            if (targetF.fail() || targetF.bad())
                LOGF("%s: %s: %s\n", 
                    Display::UsingDispString->not_write,
                    accessPrefix.c_str(),
                    strqerror());

            copiedData += readed_data;
        }

        sourceF.close();
        targetF.close();

        LOGD("%s.\n", Display::UsingDispString->success_flash);
    }
    else if (progress_code == 3)
    {
        /* get target partition block size */
        VLOGD("PartitionManager: getting block size `%s' with 'statfs <sys/vfs.h>'\n", accessPrefix.c_str());

        struct statfs file_sys_inf;
        if (statfs(accessPrefix.c_str(), &file_sys_inf) != 0)
            LOGE("%s\n", Display::UsingDispString->cannot_get_bsz);

        /* generate mke2fs argument list */
        VLOGD("PartitionManager: generating mke2fs argument list...\n");
        char bsize[25] = "";
        sprintf(bsize, "%lu", file_sys_inf.f_bsize);
        char* arguments[] = {
            "mke2fs-static",
            "-Fq",
            "-t",
            (char*)Strings::TargetFormatFS.c_str(),
            "-b",
            (char*)bsize,
            (char*)accessPrefix.c_str(),
        };

        LOGD("%s: `%s'. %s: %s\n",
            Display::UsingDispString->formatting,
            accessPrefix.c_str(),
            Display::UsingDispString->fs_str,
            Strings::TargetFormatFS.c_str());

        /* run mke2fs */
        VLOGD("PartitionManager: calling mke2fs_main...\n");
        if (mke2fs_main(sizeof(arguments), arguments) != 0)
            LOGF("%s\n", Display::UsingDispString->format_fail);

        LOGD("%s.\n", Display::UsingDispString->success_format);
    }
    else if (progress_code == 4)
    {
        VLOGD("PartitionManager: getting size of '%s' (long long)\n", accessPrefix.c_str());
        long long psize = (long long)CalculateSizeLongLong(accessPrefix);

        if (psize == -1)
        {
            VLOGE("PartitionManager: cannot get partition size!\n");
            LOGE("%s: %s\n",
                Display::UsingDispString->fail_get_psize,
                strqerror());
        }

        static char* SizeType;
        static char Holder[50];

        if (!Booleans::OnlyViewSize)
        {
            sprintf(Holder, "%s: ", Strings::TargetPartition.c_str());

            if (Integers::PartSizeViewType == VIEW_AS_BYTE) SizeType = "B";
            else if (Integers::PartSizeViewType == VIEW_AS_KIB)  SizeType = "KB";
            else if (Integers::PartSizeViewType == VIEW_AS_MIB)  SizeType = "MB";
            else if (Integers::PartSizeViewType == VIEW_AS_GIB)  SizeType = "GB";
        }
        else
            SizeType = "";

        VLOGD("PartitionManager: Displaying partition size...\n");

        if (Integers::PartSizeViewType == VIEW_AS_BYTE)
            LOGD("%s%llu%s\n",
                Holder,
                (long long)psize,
                SizeType);
        else if (Integers::PartSizeViewType == VIEW_AS_KIB)
            LOGD("%s%lu%s\n",
                Holder,
                (long)(psize / 1024),
                SizeType);
        else if (Integers::PartSizeViewType == VIEW_AS_MIB)
            LOGD("%s%.2f%s\n",
                Holder,
                (double)(static_cast<double>(psize) / (1024 * 1024)),
                SizeType);
        else if (Integers::PartSizeViewType == VIEW_AS_GIB)
            LOGD("%s%.2f%s\n",
                Holder,
                (double)(static_cast<double>(psize) / (1024 * 1024 * 1024)),
                SizeType);
    }

    return 0;
}

/* end of code */
