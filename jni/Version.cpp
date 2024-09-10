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
#define INC_STRINGKEYS
#define VERSIONING

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/VersionFnVars.h>

using namespace PartitionManager;

void Functions::DisplayVersion(void)
{
    VLOGD("DisplayVersion: printing main info...\n");
    LOGD("%s %s %d.%d.%d (C++) (%d%d%d) ", Strings::ExecutingName.c_str(), Display::UsingDispString->version_str, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL);

#if __SIZEOF_POINTER__ == 4
    LOGD("32-bit %s\n", Display::UsingDispString->bin_str);
#elif __SIZEOF_POINTER__ == 8
    LOGD("64-bit %s\n", Display::UsingDispString->bin_str);
#else
    LOGD("<%s> %s\n", Display::UsingDispString->unknw_str, Display::UsingDispString->bin_str);
#endif

    VLOGD("DisplayVersion: build type: ");

#if defined(__clang__) && !defined(__NDK_BUILD)
    if (Booleans::VerboseMode)
        printf("clang (manual).\n");
    LOGD("%s: clang %d.%d.%d\n", Display::UsingDispString->compiler_str, __clang_major__, __clang_minor__, __clang_patchlevel__);
#elif defined(__NDK_BUILD)
    if (Booleans::VerboseMode)
        printf("NDK.\n");
    LOGD("%s\n", __NDK_CXX_VERSION__);
#endif
}

/* end of code */
