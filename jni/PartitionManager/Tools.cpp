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
#define INC_STAT 1
#define INC_LIBGEN 1
#define INC_DEBUGERS 1
#define INC_TOOLS_REQS 1
#define INC_STRINGKEYS 1

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/PartSizeMacros.h>
#include <PartitionManager/FileSystemUtils.h>

static fstream sourceF, targetF;
static long long Count;

namespace PartitionManager {

/**
 * it is meant to calculate the size of the quickly given file. 
 * its purpose is for rapid processing
 */
static inline long long
CalculateSizeLongLong(const string& fp)
{
	VLOGD("Calculating file size: `%s'\n", fp.c_str());

	VLOGD("Reading `%s' with 'ifstream <fstream>'\n", fp.c_str());
	ifstream file(fp, ios::binary | ios::ate);

	return (!file) ? -1 : static_cast<long long>(file.tellg());
}

/**
 * error that the partition is not found. 
 * It's for quick action.
 */
static inline void
PartitionNotFound(const string& part) { LOGE("%s: %s\n", part.c_str(), Display::UsingDispString->part_not_found); }

/* the partitions are meant to quickly find. */
static inline void
SearchPartition(const string& fp)
{
	VLOGD("Calling GetState()...\n");
	static int op = GetState(fp, "blk");

	if (op == 1)
		PartitionNotFound(basename(fp.c_str()));
	else if (op == -1 && !Config.ForceMode)
		LOGE("%s\n", Display::UsingDispString->not_block);
}

static void
PrintInfo(const ushort_t& pcode, const double& psz, const double& fsz)
{
	LOGD("##########################################\n");
	LOGD("# --> %s: %s\n",
		Display::UsingDispString->part_name,
		Strings::TargetPartition.c_str());
	LOGD("# --> %s: %s\n",
		Display::UsingDispString->part_type,
		(Config.UseLogical) ? Display::UsingDispString->yes : Display::UsingDispString->no);

	if (psz != -1)
		LOGD("# --> %s: %.2fMB\n", 
			Display::UsingDispString->part_disk_sz,
			psz);
	else
		LOGD("# --> %s: %s\n",
			Display::UsingDispString->warn,
			Display::UsingDispString->part_disk_sz_fail);

	if (pcode == 3) {
		if (fsz != -1)
			LOGD("# --> %s: %.2fMB\n",
				Display::UsingDispString->flash_file_sz,
				fsz);
		else
			LOGW("# --> %s: %s\n",
				Display::UsingDispString->warn,
				Display::UsingDispString->flash_file_sz_fail);
	}

	LOGD("##########################################\n");
}

template <typename T>
static bool
IsDoubleOf1024(T size) { return size % (T)1024 == 0; }

static void
ReadAndWrite(const string& FNameForMsg, const int& bfsize)
{
	long long copiedData = 0;
	char buffer[bfsize];

	while (sourceF.read(buffer, bfsize) && copiedData < Count) {
		streamsize readed_data = sourceF.gcount();
		targetF.write(buffer, readed_data);

		if (targetF.fail() || targetF.bad())
			LOGF("%s: %s: %s\n", 
				Display::UsingDispString->not_write,
				FNameForMsg.c_str(),
				strqerror());

		copiedData += readed_data;
	}
}

static void
OpenSourceFile(const string& fp)
{
	VLOGD("Trying to open `%s' with 'open <fstream>'.\n", fp.c_str());

	sourceF.open(fp, ios::binary | ios::in);
	if (!sourceF.is_open())
		LOGE("%s: %s: %s\n", 
			Display::UsingDispString->not_read,
			fp.c_str(),
			strqerror());
}

static void
OpenTargetFile(const string& fp)
{
	VLOGD("Trying to open `%s' with 'open <fstream>'.\n", fp.c_str());

	targetF.open(fp, ios::binary | ios::out);
	if (!targetF.is_open())
		LOGE("%s: %s: %s\n",
		Display::UsingDispString->not_gen,
		fp.c_str(),
		strqerror());
}

} /* namespace PartitionManager */

using namespace PartitionManager;

int PartitionManager::PartitionManagerMain(const ushort_t& progress_code)
{
	/* Some required variables */
	string accessPrefix, opName;

	if (Config.UseLogical)
		accessPrefix = "/dev/block/mapper/" + Strings::TargetPartition;
	else
		accessPrefix = (Config.UseCustomSearchPath) ? (Strings::CustomSearchPath) + ("/") + (Strings::TargetPartition) : ("/dev/block/by-name/") + (Strings::TargetPartition);

	VLOGD("Calling SearchPartition() for searching partition (path); `%s'\n", accessPrefix.c_str());
	SearchPartition(accessPrefix);

	Count = (long long)(CalculateSizeLongLong(accessPrefix) + ((1024 * 1024) * 4));
	const int BFSIZE = (IsDoubleOf1024(CalculateSizeLongLong(accessPrefix))) ? 1024 : 1;
	double FlashFileSize = 0;

	double PartitionSize = (double)(static_cast<double>(CalculateSizeLongLong(accessPrefix)) / (1024 * 1024));
	if (!Strings::TargetFlashFile.empty())
		FlashFileSize = (double)(static_cast<double>(CalculateSizeLongLong(Strings::TargetFlashFile)) / (1024 * 1024));

	if (progress_code != 4) PrintInfo(progress_code, PartitionSize, FlashFileSize);

	if (progress_code == 1) {
		OpenSourceFile(accessPrefix);

		/* determine output */
		if (Strings::OutputName == Strings::TargetPartition) {
			opName = Strings::OutputName + ".img";
			VLOGW("Output not speficed. Selecting automaticly.\n");
			LOGW("%s: %s\n",
				Display::UsingDispString->out_not_spec,
				opName.c_str());
		} else
			opName = Strings::OutputName;

		VLOGD("Checking output status...\n");
		if (GetState(opName) == 0)
			LOGE("'%s': File exits.\n", opName.c_str());

		OpenTargetFile(opName);

		VLOGD("Read (partition) and write (output) 'read, write <fstream>'\n");
		ReadAndWrite(opName.c_str(), BFSIZE);

		/* close files */
		sourceF.close();
		targetF.close();

		LOGD("%s: %s\n", 
			Display::UsingDispString->success_backup,
			opName.c_str());
	} else if (progress_code == 2) {
		if (PartitionSize != -1 && FlashFileSize != -1) {
			if (FlashFileSize > PartitionSize && !Config.ForceMode)
				LOGE("%s\n", Display::UsingDispString->ffile_more_part);
		}

		OpenSourceFile(Strings::TargetFlashFile);
		OpenTargetFile(accessPrefix);

		VLOGD("Read (flash file) and write (partition) 'read, write <fstream>'\n");
		ReadAndWrite(accessPrefix.c_str(), BFSIZE);

		sourceF.close();
		targetF.close();

		LOGD("%s.\n", Display::UsingDispString->success_flash);
	} else if (progress_code == 3) {
		/* get target partition block size */
		VLOGD("Getting block size '%s' with 'statfs <sys/vfs.h>'\n", accessPrefix.c_str());

		struct statfs file_sys_inf;
		if (statfs(accessPrefix.c_str(), &file_sys_inf) != 0)
			LOGE("%s\n", Display::UsingDispString->cannot_get_bsz);

		/* generate mke2fs argument list */
		VLOGD("Generating mke2fs argument list...\n");
		char bsize[25] = "";
#ifdef __LP64__
		sprintf(bsize, "%lu", file_sys_inf.f_bsize);
#else
		sprintf(bsize, "%u", file_sys_inf.f_bsize);
#endif
		char* arguments[] = {
			"mke2fs-static",
			"-Fq",
			"-t",
			(char*)Strings::TargetFormatFS.c_str(),
			"-b",
			(char*)bsize,
			(char*)accessPrefix.c_str(),
		};

		LOGD("%s: `%s'. %s: %s\n",
			Display::UsingDispString->formatting,
			accessPrefix.c_str(),
			Display::UsingDispString->fs_str,
			Strings::TargetFormatFS.c_str());

		/* run mke2fs */
		VLOGD("Calling mke2fs_main...\n");
		if (mke2fs_main(sizeof(arguments), arguments) != 0)
			LOGF("%s\n", Display::UsingDispString->format_fail);

		LOGD("%s.\n", Display::UsingDispString->success_format);
	} else if (progress_code == 4) {
		VLOGD("Getting size of '%s' (long long)\n", accessPrefix.c_str());
		long long psize = (long long)CalculateSizeLongLong(accessPrefix);

		if (psize == -1) {
			VLOGE("Cannot get partition size!\n");
			LOGE("%s: %s\n",
				Display::UsingDispString->fail_get_psize,
				strqerror());
		}

		static char* SizeType;
		static char Holder[50];

		if (!Config.OnlyViewSize) {
			sprintf(Holder, "%s: ", Strings::TargetPartition.c_str());

			if (Integers::PartSizeViewType == VIEW_AS_BYTE) SizeType = "B";
			else if (Integers::PartSizeViewType == VIEW_AS_KIB)  SizeType = "KB";
			else if (Integers::PartSizeViewType == VIEW_AS_MIB)  SizeType = "MB";
			else if (Integers::PartSizeViewType == VIEW_AS_GIB)  SizeType = "GB";
		} else
			SizeType = "";

		VLOGD("Displaying partition size...\n");

		if (Integers::PartSizeViewType == VIEW_AS_BYTE)
			LOGD("%s%llu%s\n",
				Holder,
				(long long)psize,
				SizeType);
		else if (Integers::PartSizeViewType == VIEW_AS_KIB)
			LOGD("%s%lu%s\n",
				Holder,
				(long)(psize / 1024),
				SizeType);
		else if (Integers::PartSizeViewType == VIEW_AS_MIB)
			LOGD("%s%.2f%s\n",
				Holder,
				(double)(static_cast<double>(psize) / (1024 * 1024)),
				SizeType);
		else if (Integers::PartSizeViewType == VIEW_AS_GIB)
			LOGD("%s%.2f%s\n",
				Holder,
				(double)(static_cast<double>(psize) / (1024 * 1024 * 1024)),
				SizeType);
	}

	return 0;
}

/* end of code */
