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
#include <sys/system_properties.h>

static int
GetProperty(const char* _Nonnull property, const char* desired_val, const char* desired_val2 = nullptr)
{
    char val[PROP_VALUE_MAX];
    int len = __system_property_get(property, val);

    VLOGD("GetProperty: get property value: '%s'\n", property);
    if (len > 0)
    {
        VLOGD("GetProperty: %s=%s\n", property, val);

        VLOGD("GetProperty: comparing '%s' property value '%s'\n", property, desired_val);
        if (strcmp(val, desired_val) == 0)
        {
            VLOGD("GetProperty: '%s' is '%s'. Stop (0).\n", property, desired_val);
            return 0;
        }
        else
        {
            VLOGE("GetProperty: '%s' property is not '%s'. Comparing desired value 2 (if speficed).\n", property, desired_val);

            if (desired_val2 != nullptr)
            {
                if (strcmp(val, desired_val2) == 0)
                {
                    VLOGD("GetProperty: '%s' is '%s'.Stop (0).\n", property, desired_val2);
                    return 0;
                }
                else
                {
                    VLOGE("GetProperty: '%s' is not '%s'. Stop (1).\n", property, desired_val2);
                    return 1;
                }
            }
            else
            {
                VLOGE("GetProperty: '%s' is not '%s'. Stop (1).\n", property, desired_val);
                return 1;
            }
        }
    }
    else
    {
        VLOGE("GetProperty: cannot get property '%s'. No such property or empty. Stop (1).\n", property);
        return 1;
    }

    return 2;
}

using namespace PartitionManager;

/* check parts */
void Functions::CheckDevPoint(void)
{
    /* true = ab | false = a only */
    Booleans::UsesSlots = (GetProperty("ro.boot.slot_suffix", "_a", "_b") == 0 || GetProperty("ro.boot.slot", "_a", "_b") == 0) ? true : false;

    if (Booleans::UsesSlots)
        VLOGW("CheckDevPoint: 1 warning generated: A/B partitions status.\n");

    /* true = logical | false = normal */
    Booleans::UsesLogical = (GetProperty("ro.boot.dynamic_partitions", "true") == 0) ? true : false;

    if (Booleans::UsesLogical)
        VLOGW("CheckDevPoint: 1 warning generated: logical partitions status.\n");
}

/* end of code */
