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

#define INC_MAIN_LIBS 1
#define INC_STRINGKEYS 1

#include <PartitionManager/PartitionManager.h>

using namespace PartitionManager;

/* it's prints standart logs */
void PartitionManager::DisplayLog(LogLevel LogPriority, const char* _Nonnull fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	if (!Config.SilentEnabled)
	{
		switch (LogPriority)
		{
		case LOG_LEVEL_ERROR:
			fprintf(stderr, "%s: ", Strings::ExecutingName.c_str());
			vfprintf(stderr, fmt, args);
			break;
		case LOG_LEVEL_WARN:
			fprintf(stdout, "%s: ", Display::UsingDispString->warn);
			vfprintf(stdout, fmt, args);
			break;
		case LOG_LEVEL_FATAL:
			fprintf(stderr, "%s: ", Display::UsingDispString->fatal);
			vfprintf(stderr, fmt, args);
			break;
		case LOG_LEVEL_DEBUG:
			vfprintf(stdout, fmt, args);
			break;
		}
	}

	if (LogPriority == LOG_LEVEL_ERROR) exit(1);
	else if (LogPriority == LOG_LEVEL_FATAL) abort();

	va_end(args);
}

/* it's prints verbose logs */
void PartitionManager::DisplayVerboseLog(LogLevel LogPriority, const char* func, const int& line, const char* _Nonnull fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	if (Config.VerboseMode)
	{
		switch (LogPriority)
		{
			case LOG_LEVEL_ERROR:
			fprintf(stderr, "<E> [%s() Line<%d>]: ", func, line);
			vfprintf(stderr, fmt, args);
			break;
		case LOG_LEVEL_WARN:
			fprintf(stdout, "<W> [%s() Line<%d>]: ", func, line);
			vfprintf(stdout, fmt, args);
			break;
		case LOG_LEVEL_FATAL:
			fprintf(stderr, "<F> [%s() Line<%d>]: ", func, line);
			vfprintf(stderr, fmt, args);
			break;
		case LOG_LEVEL_DEBUG:
			fprintf(stdout, "<D> [%s() Line<%d>]: ", func, line);
			vfprintf(stdout, fmt, args);
			break;
		}
	}

	va_end(args);
}

/**
 * Last error is taken from strerror by taking 
 * the contents of errno or taking a special entry 
 */
char* strqerror(int __qerrno) { return strerror(__qerrno); }

/* end of code */
