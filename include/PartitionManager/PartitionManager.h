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

#pragma once

#if !defined(__clang__) && !defined(__NDK_BUILD)
  #error "Your compiler is NOT clang. Please build with (LLVM) clang."
#endif

#ifdef INC_MAIN_LIBS
  #include <iostream>
  #include <stdbool.h>
  #include <cstdio>
  #include <string>
  #include <cstring>
  #include <cstdarg>

  #ifdef IS_MAIN
    #include <clocale>
  #endif
  #if !defined(HELP) || !defined(VERSIONING)
    #include <cstdlib>
    #include <unistd.h>
    #include <fcntl.h>
    #include <fstream>
  #endif
#endif
#ifdef INC_STRINGKEYS
  #include <PartitionManager/StringKeys.h>
#endif
#ifdef INC_DIRENT
  #include <dirent.h>
#endif
#ifdef INC_STAT
  #include <sys/stat.h>
#endif
#ifdef INC_DEBUGERS
  #include <cerrno>
#endif
#ifdef INC_TOOLS_REQS
  #include <sys/vfs.h>

  typedef unsigned short ushort_t;
#endif
#ifdef INC_LIBGEN
  #include <libgen.h>
#endif

using namespace std;

/* logging levels */
typedef enum {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERROR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_DEBUG
} LogLevel;

/**
 * Fast error processing without errno entry 
 * but errno can be given in the entrance
 */
extern "C" char* strqerror(int errno_macro = errno);

/* create a special namespace */
namespace PartitionManager {
    namespace Strings {
        extern string OutputName;
        extern string CustomSearchPath;
        extern string TargetPartition;
        extern string TargetFlashFile;
        extern string TargetFormatFS;
        extern string PartitionType;
        extern string ExecutingName;
        extern string CurrentLanguage;
    } /* namespace Strings */

    namespace Integers {
        extern int PartSizeViewType;
    } /* namespace Integers */

    namespace Booleans {
        extern bool UseLogical;
        extern bool UseCustomSearchPath;
        extern bool UsesSlots;
        extern bool UsesLogical;
        extern bool OnlyViewSize;
        extern bool SilentEnabled;
        extern bool FlashMode;
        extern bool BackupMode;
        extern bool FormatMode;
        extern bool PartSizeViewMode;
        extern bool ForceMode;
        extern bool VerboseMode;
        extern bool InstalledOnTermux;
    } /* namespace Booleans */

    namespace Display {
        extern struct langdb_general* UsingDispString;
        extern struct langdb_docs* UsingDocDispString;
        extern struct langdb_general LangEn;
        extern struct langdb_general LangTr;
        extern struct langdb_docs LangDocEn;
        extern struct langdb_docs LangDocTr;
    } /* namespace Display */

    namespace Functions {
        int ListPartitions(void);
        int GetState(const string& filepath, const string& stype = "file");
        int Start(unsigned short progress_code);
        void SetLanguage(const string& lang, unsigned short null_conf_stat);
        void DisplayLog(LogLevel status, const char* fmt, ...);
        void DisplayVerboseLog(LogLevel status, const char* fmt, ...);
        void CheckDevPoint(void);
        void CheckRoot(void);
        bool CleanSWPoint(void);
        bool LoadLanguage(void);
    } /* namespace Functions */

} /* namespace PartitionManager */

/* logging macros */
#define LOGF(fmt, ...) \
    PartitionManager::Functions::DisplayLog(LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) \
    PartitionManager::Functions::DisplayLog(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) \
    PartitionManager::Functions::DisplayLog(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) \
    PartitionManager::Functions::DisplayLog(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

/* verbose logging macros */
#define VLOGF(fmt, ...) \
    PartitionManager::Functions::DisplayVerboseLog(LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#define VLOGE(fmt, ...) \
    PartitionManager::Functions::DisplayVerboseLog(LOG_LEVEL_ERROR, fmt, ##__VA_ARGS__)
#define VLOGW(fmt, ...) \
    PartitionManager::Functions::DisplayVerboseLog(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define VLOGD(fmt, ...) \
    PartitionManager::Functions::DisplayVerboseLog(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

/* end of code */
