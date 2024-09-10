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

#include <PartitionManager/PartitionManager.h>

using namespace PartitionManager;

static bool
accf(const string fp)
{
    VLOGD("accf <local function>: trying to access `%s' with 'access <unistd.h>'\n", fp.c_str());

    return (access(fp.c_str(), F_OK) == 0) ? true : false;
}

/* check parts */
void Functions::CheckDevPoint(void)
{
    VLOGD("CheckDevPoint: selecting context...\n");
    string dpoint = (Booleans::UseCustomContext) ? Strings::CustomContext : "/dev/block/by-name";

    /* true = ab | false = a only */
    Booleans::UsesSlots = (accf(dpoint + "/boot_a")) ? true : false;

    if (Booleans::UsesSlots)
        VLOGW("CheckDevPoint: 1 warning generated: A/B status.\n");

    /* true = logical | false = normal */
    Booleans::UsesLogical = (accf(dpoint + "/super")) ? true : false;

    if (Booleans::UsesLogical)
        VLOGW("CheckDevPoint: 1 warning generated: logical partitions status.\n");
}

/* end of code */
