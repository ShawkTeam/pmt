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

#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_VERSIONER_REQS

#include <pmt.h>

extern char* bin_name;

extern struct pmt_langdb_general* current;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;

void version(void)
{
    LOGD("%s %s %d.%d.%d (%d%d%d) ", bin_name, current->version_str, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL, PMT_MAJOR, PMT_MINOR, PMT_PATCHLEVEL);

    #if __SIZEOF_POINTER__ == 4
        LOGD("32-bit %s\n", current->bin_str);
    #elif __SIZEOF_POINTER__ == 8
        LOGD("64-bit %s\n", current->bin_str);
    #else
        LOGD("<%s> %s\n", current->unknw_str, current->bin_str);
    #endif

    #if defined(__clang__)
        LOGD("%s: clang %d.%d.%d (NDK r%d%s %s)\n", current->compiler_str, __clang_major__, __clang_minor__, __clang_patchlevel__, __NDK_MAJOR__, __NDK_MINOR_STATUS__, __NDK_BETA_STATUS__);
    #endif

    LOGD("%s\n", current->see_license);
}

#if defined(__cplusplus)
}
#endif

/* end of code */