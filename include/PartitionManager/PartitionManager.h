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

#pragma once

#if INC_MAIN_LIBS
	#include <iostream>
	#include <stdbool.h>
	#include <cstdio>
	#include <string>
	#include <cstring>
	#include <cstdarg>
	#if IS_MAIN
		#include <clocale>
	#endif
	#if !defined(HELP_CPP) || !defined(VERSION_CPP)
		#include <cstdlib>
		#include <unistd.h>
		#include <fcntl.h>
		#include <fstream>
	#endif
#endif
#if INC_STRINGKEYS
	#include <PartitionManager/StringKeys.h>
#endif
#if INC_DIRENT
	#include <dirent.h>
#endif
#if INC_STAT
	#include <sys/stat.h>
#endif
#if INC_DEBUGERS
	#include <cerrno>
#endif
#if INC_TOOLS_REQS
	#include <sys/vfs.h>
#endif
#if INC_LIBGEN
	#include <libgen.h>
#endif
#if INC_PTHREAD
	#include <pthread.h>
#endif

using namespace std;

/* logging levels */
typedef enum {
	LOG_LEVEL_FATAL,
	LOG_LEVEL_ERROR,
	LOG_LEVEL_WARN,
	LOG_LEVEL_DEBUG
} LogLevel;

/* config structure */
struct Configuration {
	/* general boolean tab */
	bool UseLogical;
	bool UseCustomSearchPath;
	bool UsesSlots;
	bool UsesLogical;
	bool SilentEnabled;
	bool FlashMode;
	bool BackupMode;
	bool FormatMode;
	bool PartedMode;
	bool PartSizeViewMode;
	bool PartUtilMode;
	bool ForceMode;
	bool VerboseMode;
	bool InstalledOnTermux;

	/* part-size argument bools */
	bool OnlyViewSize;
};

/**
 * Fast error processing without errno entry
 * but errno can be given in the entrance
 */
extern "C" char* strqerror(int __qerrno = errno);

/**
 * ushort_t = unsigned short type
 */
typedef unsigned short ushort_t;

/**
 * bool type configurations
 */
extern struct Configuration Config;

/* create a special namespace */
namespace PartitionManager {
	namespace Strings {
		extern string OutputName;
		extern string CustomSearchPath;
		extern string TargetPartition;
		extern string TargetFlashFile;
		extern string TargetFormatFS;
		extern string PartitionType;
		extern string Device;
		extern string ExecutingName;
		extern string CurrentLanguage;
	} /* namespace Strings */

	namespace Integers {
		extern int PartSizeViewType;
	} /* namespace Integers */

	namespace Display {
		extern struct langdb_general* UsingDispString;
		extern struct langdb_docs* UsingDocDispString;
		extern struct langdb_general LangEn;
		extern struct langdb_general LangTr;
		extern struct langdb_docs LangDocEn;
		extern struct langdb_docs LangDocTr;
	} /* namespace Display */

	/* functions */
	int ListPartitions(void);
	int GetState(const string& filepath, const string& stype = "file");
	int PartitionManagerMain(const ushort_t& progress_code);
	int StartParted(void);
	void SetLanguage(const string& lang, ushort_t null_conf_stat);
	void DisplaySupportedLanguages(void);
	void DisplayLog(LogLevel LogPriority, const char* fmt, ...);
	void DisplayVerboseLog(LogLevel LogPriority, const char* func, const int& line, const char* fmt, ...);
	void CheckDevPoint(void);
	void CheckRoot(void);
	bool CleanSWPoint(void);
	bool LoadLanguage(void);
	bool SearchDevice(const string& DevicePath);
	bool SearchDefaultDevices(void);
} /* namespace PartitionManager */

/* logging macros */
#define LOGF(fmt, ...) \
	((void)PartitionManager::DisplayLog(LOG_LEVEL_FATAL, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define LOGE(fmt, ...) \
	((void)PartitionManager::DisplayLog(LOG_LEVEL_ERROR, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define LOGW(fmt, ...) \
	((void)PartitionManager::DisplayLog(LOG_LEVEL_WARN, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define LOGD(fmt, ...) \
	((void)PartitionManager::DisplayLog(LOG_LEVEL_DEBUG, (fmt)__VA_OPT__(, ) __VA_ARGS__))

/* verbose logging macros */
#define VLOGF(fmt, ...) \
	((void)PartitionManager::DisplayVerboseLog(LOG_LEVEL_FATAL, __func__, __LINE__, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define VLOGE(fmt, ...) \
	((void)PartitionManager::DisplayVerboseLog(LOG_LEVEL_ERROR, __func__, __LINE__, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define VLOGW(fmt, ...) \
	((void)PartitionManager::DisplayVerboseLog(LOG_LEVEL_WARN, __func__, __LINE__, (fmt)__VA_OPT__(, ) __VA_ARGS__))
#define VLOGD(fmt, ...) \
	((void)PartitionManager::DisplayVerboseLog(LOG_LEVEL_DEBUG, __func__, __LINE__, (fmt)__VA_OPT__(, ) __VA_ARGS__))

/* end of code */
