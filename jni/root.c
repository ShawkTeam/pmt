/* By YZBruh | ShawkTeam */

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
#define INC_DEBUGERS

#include <pmt.h>

extern struct pmt_langdb_general* current;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;

/* root checker function */
void check_root(void)
{
    /* a quick, easy method for verifying root */
    if (getuid() != 0)
        LOGE("%s\n", current->no_root);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
