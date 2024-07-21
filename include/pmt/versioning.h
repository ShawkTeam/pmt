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

#ifndef __PMT_VERSIONING_H
#define __PMT_VERSIONING_H

__BEGIN_DECLS

#ifdef __NDK_BUILD
  #include <android/ndk-version.h>
  #include <pmt/generated/clang-version.h>
#endif

/* versioning */
#define PMT_MAJOR            2
#define PMT_MINOR            5
#define PMT_PATCHLEVEL       0

__END_DECLS

#endif

/* end */
