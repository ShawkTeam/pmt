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

#define BFSIZE 1024
#define INC_MAIN_LIBS
#define INC_STAT
#define INC_DEBUGERS
#define INC_TOOLS_REQS

#include <pmt/pmt.h>
#include <pmt/stringkeys.h>

/**
 * it is meant to calculate the size of the quickly given file. 
 * its purpose is for rapid processing
 */
static double
calc_flsz(const char* _Nonnull filepath)
{
    static int calc_flsz_file;
    calc_flsz_file = open(filepath, O_RDONLY);

    if (calc_flsz_file == -1)
        return calc_flsz_file;

    static off_t flsz;
    flsz = lseek(calc_flsz_file, 0, SEEK_END);
    close(calc_flsz_file);

    if (flsz == (off_t)-1)
        return -1;

    return (double)flsz / (1024 * 1024);
}

/**
 * error that the partition is not found. 
 * It's for quick action.
 */
static void
partition_not_found(void) { LOGE("%s\n", current->part_not_found); }

/* to stop use of function type */
#define partition_not_found partition_not_found()

/* the partitions are meant to quickly find. */
static void
search_partition(const char* _Nonnull partition)
{
    static int partition_results = 0;
    partition_results = get_stat(partition, "blk");

    if (partition_results == 1)
        partition_not_found;
    else if (partition_results == -1)
        LOGE("%s\n", current->not_block);
}

int pmt(unsigned short progress_code)
{
    /* required variables */
    static int srcf, targetf;
    static char backupper_path[512];
    static char ppath[100];
    static char formatter_cmd[200];
    static char outf[512];
    static char flasher_path[512];
    static char buffer[BFSIZE];
    static ssize_t readed_data;
    static unsigned long long copied_data = 0;
    static unsigned long long count = 1024 * 1024 * 1024;

    if (progress_code == 1)
    {
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt)
                sprintf(backupper_path, "%s/%s", cust_cxt, target_partition);
            else
                sprintf(backupper_path, "/dev/block/by-name/%s", target_partition);
        }
        else
            sprintf(backupper_path, "/dev/block/mapper/%s", target_partition);

        search_partition(backupper_path);

        if (calc_flsz(backupper_path) != -1)
            LOGD("%s: %.2f\n", current->part_disk_sz, calc_flsz(backupper_path));
        else
            LOGW("%s\n", current->part_disk_sz_fail);

        srcf = open(backupper_path, O_RDONLY);
        if (srcf == -1)
            LOGE("%s: %s: %s\n", current->not_read, backupper_path, strerror(errno));

        /* determine output */
        if (strcmp(out, target_partition) == 0)
        {
            sprintf(outf, "%s.img", out);
            LOGW("%s: %s\n", current->out_not_spec, outf);
        }
        else
            sprintf(outf, "%s", out);

        targetf = open(outf, O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (targetf == -1)
            LOGE("%s: %s: %s\n", current->not_gen, outf, strerror(errno));

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
            {
                if (get_stat(outf, "file") == 0)
                    remove(outf);
                LOGF("%s: %s: %s\n", current->not_write, backupper_path, strerror(errno));
            }

            copied_data += writed_data;
        }

        /* close files */
        close(srcf);
        close(targetf);

        LOGD("%s: %s\n", current->success_backup, outf);
    }
    else if (progress_code == 2)
    {
        /* determine device block */
        /* for classic */
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt)
                sprintf(flasher_path, "%s/%s", cust_cxt, target_partition);
            else
                sprintf(flasher_path, "/dev/block/by-name/%s", target_partition);
        /* for logical */
        }
        else
            sprintf(flasher_path, "/dev/block/mapper/%s", target_partition);

        /* check partition */
        search_partition(flasher_path);

        if (calc_flsz(target_flash_file) != -1)
            LOGD("%s: %.2f\n", current->flash_file_sz, calc_flsz(target_flash_file));
        else
            LOGW("%s\n", current->flash_file_sz_fail);

        if (calc_flsz(flasher_path) != -1)
            LOGD("%s: %.2f\n", current->part_disk_sz, calc_flsz(flasher_path));
        else
            LOGW("%s\n", current->part_disk_sz_fail);

        if (calc_flsz(target_flash_file) != -1 && calc_flsz(flasher_path) != -1)
        {
            if (calc_flsz(target_flash_file) > calc_flsz(flasher_path))
                LOGE("%s\n", current->ffile_more_part);
        }

        srcf = open(target_flash_file, O_RDONLY);
        if (srcf == -1)
            LOGF("%s: %s: %s\n", current->not_read, target_flash_file, strerror(errno));

        targetf = open(target_partition, O_WRONLY | O_CREAT | O_TRUNC, 0660);
        if (targetf == -1)
            LOGF("%s: %s: %s\n", current->not_read, target_partition, strerror(errno));

        /* start writing */
        while ((readed_data = read(srcf, buffer, BFSIZE)) > 0 && copied_data < count)
        {
            ssize_t writed_data = write(targetf, buffer, readed_data);
            if (writed_data != readed_data)
                LOGF("%s: %s: %s\n", current->not_write, backupper_path, strerror(errno));

            copied_data += writed_data;
        }

        close(srcf);
        close(targetf);

        LOGD("%s.\n", current->success_flash);
    }
    else if (progress_code == 3)
    {
        /* generate partition extn */
        if (!pmt_use_logical)
        {
            if (pmt_use_cust_cxt)
                sprintf(ppath, "%s/%s", cust_cxt, target_partition);
            else
                sprintf(ppath, "/dev/block/by-name/%s", target_partition);
        /* for logical */
        }
        else
            sprintf(ppath, "/dev/block/mapper/%s", target_partition);

        /* check partition */
        search_partition(ppath);

        /* get target partition block size */
        struct statvfs file_sys_inf;
        if (statvfs(ppath, &file_sys_inf) != 0)
            LOGE("%s\n", current->cannot_get_bsz);

        /* generate mke2fs command */
        sprintf(formatter_cmd, "mke2fs -Fq -t %s -b %lu %s", format_fs, file_sys_inf.f_bsize, ppath);

        /* run command */
        if (system(formatter_cmd) != 0)
            LOGF("%s\n", current->format_fail);
    }

    return 0;
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* end of code */
