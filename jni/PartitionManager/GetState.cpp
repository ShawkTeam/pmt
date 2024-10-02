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

#include <PartitionManager/PartitionManager.h>

/**
 * The target file is controlled by the stat function. 
 * Files, directories, links and blocks (disks) are for. 
 * If it is never found, it returns 1 value.
 * If he finds 0 value is returned. 
 * If the desired type is not in -1 value is returned.
 * If the search type is unknown, 3 value is returned
 */
int PartitionManager::Functions::GetState(const string& filepath, const string& stype)
{
    static struct stat GetStat;

    VLOGD("GetStat: checking `%s' with 'stat <sys/stat.h>'...\n", filepath.c_str());
    if (stat(filepath.c_str(), &GetStat) != 0)
        return 1;

    if (stype == "dir") 
        return (S_ISDIR(GetStat.st_mode)) ? 0 : -1;
    else if (stype == "file")
        return (S_ISREG(GetStat.st_mode)) ? 0 : -1;
    else if (stype == "blk")
        return (S_ISBLK(GetStat.st_mode)) ? 0 : -1;
    else if (stype == "link")
        return (S_ISLNK(GetStat.st_mode)) ? 0 : -1;
    else
        return 3;

    return 2;
}

/* end of code */
