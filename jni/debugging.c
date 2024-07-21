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
#include <pmt/stringkeys.h>

void debug(LogLevel status, const char* _Nullable fmt, ...)
{
    if (fmt == NULL) exit(1);

    va_list args;
    va_start(args, fmt);

    switch (status)
    {
        case LOG_LEVEL_ERR:
            if (!pmt_silent)
            {
                fprintf(stderr, "%s: ", bin_name);
                vfprintf(stderr, fmt, args);
            }
            exit(1);
            break;
        case LOG_LEVEL_WARN:
            if (!pmt_silent)
            {
                fprintf(stderr, "%s: ", current->warn);
                vfprintf(stderr, fmt, args);
            }
            break;
        case LOG_LEVEL_FATAL:
            if (!pmt_silent)
            {
                fprintf(stderr, "%s: ", current->fatal);
                vfprintf(stderr, fmt, args);
            }
            abort();
            break;
        case LOG_LEVEL_DEBUG:
            if (!pmt_silent)
                vfprintf(stdout, fmt, args);
            break;
    }

    va_end(args);
}

#ifdef __cplusplus
}
#endif

/* end of code */
