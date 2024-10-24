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
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>

/* root checker function */
void PartitionManager::Functions::CheckRoot(void)
{
    VLOGD("CheckRoot: trying to get UID with 'getuid <unistd.h>'\n");

    if (getuid() != 0)
    {
        VLOGE("CheckRoot: cannot get UID. Not executed with root!\n");
        LOGE("%s\n", PartitionManager::Display::UsingDispString->no_root);
    }
}

/* end of code */
