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
#define INC_STRINGKEYS 1
#define INC_DEBUGERS 1
#define INC_PTHREAD 1

/* using by new devices */
#define DEFAULT_DEVICE_NEW "/dev/block/sda"

/* using by old devices */
#define DEFAULT_DEVICE_OLD "/dev/block/mmcblk0"

/**
 * These macros will be added/deleted/modified
 * according to user feedback.
 */

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/Parted.h>

static bool started = false, o_ended = false;
static int ret = 0;
static pthread_mutex_t plock = PTHREAD_MUTEX_INITIALIZER;

extern "C" void* __start_parted(void* dummy_arg);
extern "C" void* __watch_parted(void* dummy_arg);

bool PartitionManager::SearchDevice(const string& DevicePath)
{
	VLOGD("Check '%s'.\n", DevicePath.c_str());

	if (PartitionManager::GetState(DevicePath, "none") != 0) {
		VLOGD("Cannot find '%s'.\n", DevicePath.c_str());
		return false;
	} else VLOGD("Founded: '%s'.\n", DevicePath.c_str());

	return true;
}

bool PartitionManager::SearchDefaultDevices(void)
{
	VLOGD("Searching '%s'.\n", DEFAULT_DEVICE_NEW);
	if (PartitionManager::SearchDevice(DEFAULT_DEVICE_NEW)) {
		PartitionManager::Strings::Device = DEFAULT_DEVICE_NEW;
		return true;
	}

	VLOGD("Searching '%s'.\n", DEFAULT_DEVICE_NEW);
	if (PartitionManager::SearchDevice(DEFAULT_DEVICE_OLD)) {
		PartitionManager::Strings::Device = DEFAULT_DEVICE_OLD;
		return true;
	}

	return false;
}

void* __watch_parted(void* dummy_arg)
{
	while (1) {
		pthread_mutex_lock(&plock);

		if (started) {
			if (o_ended) {
				pthread_mutex_unlock(&plock);
				return NULL;
			}
			if (set_ret) {
				LOGD("%s: %d.\n",
					PartitionManager::Display::UsingDispString->exited_with,
					parted_ret);
				pthread_mutex_unlock(&plock);
				return NULL;
			}
		} else {
			VLOGD("Parted is still not started...\n");
			sleep(1);
		}

		pthread_mutex_unlock(&plock);
		usleep(1000);
	}
}

void* __start_parted(void* dummy_arg)
{
	VLOGD("Generating arguments...\n");
	char* arguments[] = {
		"parted-pmt",
		(char*)PartitionManager::Strings::Device.c_str(),
	};

	LOGD("%s...\n", PartitionManager::Display::UsingDispString->starting_parted);
	VLOGD("Calling parted_main...\n");

	pthread_mutex_lock(&plock);
	started = true;
	pthread_mutex_unlock(&plock);
	ret = parted_main(2, arguments);
	pthread_mutex_lock(&plock);
	o_ended = true;
	pthread_mutex_unlock(&plock);
	sleep(1);

	return NULL;
}

int PartitionManager::StartParted(void)
{
	pthread_t t1, t2;

	pthread_create(&t1, NULL, __start_parted, NULL);
	pthread_create(&t2, NULL, __watch_parted, NULL);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);

	return ret;
}

/* end of code */
