/* By YZBruh */

/*
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

#pragma once

#ifdef __NDK_BUILD
  #include <android/ndk-version.h>
  #include <PartitionManager/generated/clang-version.h>
#endif
#include <e2fsprogs/version.h>

/* versioning */
#define PMT_MAJOR            2
#define PMT_MINOR            9
#define PMT_PATCHLEVEL       1

namespace PartitionManager {
    namespace Functions {
        void DisplayVersion(void);
    }
}

/* end */
