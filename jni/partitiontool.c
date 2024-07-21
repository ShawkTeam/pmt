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

#ifdef __cplusplus
extern "C" {
#endif

#define INC_MAIN_LIBS

#include <pmt/pmt.h>

static int
accf(const char* _Nonnull target) { return access(target, F_OK); }

/* check parts */
void check_dev_point(void)
{
    /* true = ab | false = a */
    if (pmt_use_cust_cxt)
    {
        static char cust_cxt_ck_path[150];
        sprintf(cust_cxt_ck_path, "%s/boot_a", cust_cxt);

        if (accf(cust_cxt_ck_path) != 0)
            pmt_ab = false;
        else
            pmt_ab = true;
    }
    else
    {
        if (accf("/dev/block/by-name/boot_a") != 0)
            pmt_ab = false;
        else
            pmt_ab = true;
    }

    /* true = logical | false = classic */
    if (pmt_use_cust_cxt)
    {
        static char cust_cxt_ckl_path[150];
        sprintf(cust_cxt_ckl_path, "%s/super", cust_cxt);

        if (accf(cust_cxt_ckl_path) != 0)
            pmt_logical = false;
        else
            pmt_logical = true;
    }
    else
    {
        if (accf("/dev/block/by-name/super") != 0)
            pmt_logical = false;
        else
            pmt_logical = true;
    }
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* end */
