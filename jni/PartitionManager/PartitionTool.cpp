/* By YZBruh */

/**
 * Copyright 2024 Partition Manager
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *	 http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define INC_MAIN_LIBS 1

#include <PartitionManager/PartitionManager.h>
#include <sys/system_properties.h>

static int
GetProperty(const char* _Nonnull property, const char* _Nonnull val1, const char* _Nullable val2 = nullptr)
{
	char val[PROP_VALUE_MAX];
	int len = __system_property_get(property, val);

	VLOGD("Get property value: '%s'\n", property);
	if (len > 0)
	{
		VLOGD("%s=%s\n", property, val);

		VLOGD("Comparing '%s' property value '%s'\n", property, val1);
		if (strcmp(val, val1) == 0)
		{
			VLOGD("'%s' is '%s'. Stop (0).\n", property, val1);
			return 0;
		}
		else
		{
			VLOGE("'%s' property is not '%s'. Comparing desired value 2 (if speficed).\n", property, val1);

			if (val2 != nullptr)
			{
				if (strcmp(val, val2) == 0)
				{
					VLOGD("'%s' is '%s'.Stop (0).\n", property, val2);
					return 0;
				}
				else
				{
					VLOGE("'%s' is not '%s'. Stop (1).\n", property, val2);
					return 1;
				}
			}
			else
			{
				VLOGE("'%s' is not '%s'. Stop (1).\n", property, val1);
				return 1;
			}
		}
	}
	else
	{
		VLOGE("Cannot get property '%s'. No such property or empty. Stop (1).\n", property);
		return 1;
	}

	return 2;
}

using namespace PartitionManager;

/* check parts */
void PartitionManager::CheckDevPoint(void)
{
	/* true = ab | false = a only */
	Config.UsesSlots = (GetProperty("ro.boot.slot_suffix", "_a", "_b") == 0 || GetProperty("ro.boot.slot", "_a", "_b") == 0) ? true : false;

	if (Config.UsesSlots)
		VLOGW("1 warning generated: A/B partitions status.\n");

	/* true = logical | false = normal */
	Config.UsesLogical = (GetProperty("ro.boot.dynamic_partitions", "true") == 0) ? true : false;

	if (Config.UsesLogical)
		VLOGW("1 warning generated: logical partitions status.\n");
}

/* end of code */
