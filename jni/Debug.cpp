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

#include <PartitionManager/PartitionManager.h>

using namespace PartitionManager;

/* it's prints standart logs */
void Functions::DisplayLog(LogLevel status, const char* _Nullable fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    switch (status)
    {
        case LOG_LEVEL_ERROR:
            if (!Booleans::SilentEnabled)
            {
                fprintf(stderr, "%s: ", Strings::ExecutingName.c_str());
                vfprintf(stderr, fmt, args);
            }
            exit(1);
            break;
        case LOG_LEVEL_WARN:
            if (!Booleans::SilentEnabled)
            {
                fprintf(stdout, "%s: ", Display::UsingDispString->warn);
                vfprintf(stdout, fmt, args);
            }
            break;
        case LOG_LEVEL_FATAL:
            if (!Booleans::SilentEnabled)
            {
                fprintf(stderr, "%s: ", Display::UsingDispString->fatal);
                vfprintf(stderr, fmt, args);
            }
            abort();
            break;
        case LOG_LEVEL_DEBUG:
            if (!Booleans::SilentEnabled)
                vfprintf(stdout, fmt, args);
            break;
    }

    va_end(args);
}

/* it's prints verbose logs */
void Functions::DisplayVerboseLog(LogLevel status, const char* fmt, ...)
{
    va_list args;
    va_start(args, fmt);

    switch (status)
    {
        case LOG_LEVEL_ERROR:
            if (Booleans::VerboseMode)
            {
                fprintf(stderr, "E:[stderr]: ");
                vfprintf(stderr, fmt, args);
            }
            break;
        case LOG_LEVEL_WARN:
            if (Booleans::VerboseMode)
            {
                fprintf(stdout, "W:[stdout]: ");
                vfprintf(stdout, fmt, args);
            }
            break;
        case LOG_LEVEL_FATAL:
            if (Booleans::VerboseMode)
            {
                fprintf(stderr, "F:[stderr]: ");
                vfprintf(stderr, fmt, args);
                abort();
            }
            break;
        case LOG_LEVEL_DEBUG:
            if (Booleans::VerboseMode)
            {
                fprintf(stdout, "D:[stdout]: ");
                vfprintf(stdout, fmt, args);
            }
            break;
    }

    va_end(args);
}

/**
 * Last error is taken from strerror by taking 
 * the contents of errno or taking a special entry 
 */
char* strqerror(int errno_macro) { return strerror(errno_macro); }

/* end of code */
