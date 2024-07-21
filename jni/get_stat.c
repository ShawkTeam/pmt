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
#define INC_STAT

#include <pmt/pmt.h>
#include <pmt/stringkeys.h>

/**
 * The target file is controlled by the stat function. 
 * Files, directories, links and blocks (disks) are for. 
 * If it is never found, it returns 1 value.
 * If he finds 0 value is returned. 
 * If the desired type is not in -1 value is returned.
 */
int get_stat(const char* _Nonnull filepath, const char* _Nonnull stype)
{
    static struct stat get_stat;

    if (stat(filepath, &get_stat) != 0)
        return 1;

    if (strcmp(stype, "dir") == 0) 
    {
        if (S_ISDIR(get_stat.st_mode))
            return 0;
        else
            return -1;
    }
    else if (strcmp(stype, "file") == 0)
    {
        if (S_ISREG(get_stat.st_mode))
            return 0;
        else
            return -1;
    }
    else if (strcmp(stype, "blk") == 0)
    {
        if (S_ISBLK(get_stat.st_mode))
            return 0;
        else
            return -1;
    }
    else if (strcmp(stype, "link") == 0)
    {
        if (S_ISLNK(get_stat.st_mode))
            return 0;
        else
            return -1;
    }

    return 2;
}

#ifdef __cplusplus
}
#endif

/* end of code */
