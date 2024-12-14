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
#define INC_DEBUGERS 1
#define INC_STAT 1
#define INC_STRINGKEYS 1

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/LanguageConfigs.h>

using namespace PartitionManager;

/* pmt's man doc file path on termux */
#define INTERNAL_STORAGE_DIR "/sdcard"
#define TERMUX_PMT_MANDOC "/data/data/com.termux/files/usr/share/man/man8/pmt.8.gz"
#define PMTLANG_CONF "/sdcard/.pmtlang.conf"
#define PMT_SW_POINT "/sdcard/.pmtlangsw"

static fstream LanguageConfigFile;
static bool LanguageApplied = false;
static int StructSize = static_cast<int>(sizeof(LanguageConfig) / sizeof(LanguageConfig[0]));

static bool
InternalStorageDirFound(void)
{
	return (GetState(INTERNAL_STORAGE_DIR, "dir") == 0) ? true : false;
}

static inline void
LoadLanguageAs(const string& Name, struct langdb_general* &Language)
{
	if (LanguageConfigFile.is_open())
		LanguageConfigFile.close();

	VLOGD("Load language as '%s'...\n", Name.c_str());

	Display::UsingDispString = Language;
	Strings::CurrentLanguage = Name;
	LanguageApplied = true;
}

static inline bool
LanguageIsSupport(const string& Name)
{
	for (int i = 0; (i < StructSize && !LanguageConfig[i].Name.empty()); i++)
		if (Name == LanguageConfig[i].Name) return true;

	return false;
}

static int
IfLanguageIsSupport_Load(const string& Name)
{
	for (int i = 0; i < StructSize; i++) {
		if (Name == LanguageConfig[i].Name) {
			VLOGD("'Name' ('%s') is '%s'.\n", Name.c_str(), LanguageConfig[i].Name.c_str());
			LoadLanguageAs(LanguageConfig[i].Name, LanguageConfig[i].LanguageStructure);
			return 0;
		}
	}

	return -1;
}

bool PartitionManager::LoadLanguage(void)
{
	string TargetLanguage = "en";
	LanguageConfigFile.close();

	VLOGD("Checking install type...\n");
	if (GetState(TERMUX_PMT_MANDOC) == 0)
		Config.InstalledOnTermux = true;

	VLOGD("Checking internal storage dir: `%s'\n", INTERNAL_STORAGE_DIR);
	if (!InternalStorageDirFound())
		LOGE("PartitionManagerLanguageTools: İnternal storage directory (`%s') not found or accessible.\n", INTERNAL_STORAGE_DIR);

	VLOGD("Trying to open `%s' with 'open <fstream>'\n", PMTLANG_CONF);
	LanguageConfigFile.open(PMTLANG_CONF, ios::in | ios::out);

	VLOGD("Checking status: `%s'...\n", PMTLANG_CONF);
	if (!LanguageConfigFile.is_open()) {
		LanguageConfigFile.open(PMTLANG_CONF, ios::out | ios::trunc);

		VLOGD("Calling SetLanguage()...\n");
		SetLanguage(LanguageConfig[0].Name, 1);
		LoadLanguageAs(LanguageConfig[0].Name, LanguageConfig[0].LanguageStructure); // english - "en"

		return true;
	} else {
		VLOGD("Reading `%s'\n", PMTLANG_CONF);
		while (getline(LanguageConfigFile, TargetLanguage))
			IfLanguageIsSupport_Load(TargetLanguage);

		if (!LanguageApplied) {
			VLOGD("Calling SetLanguage()\n");
			SetLanguage(LanguageConfig[0].Name, 1);
			LoadLanguageAs(LanguageConfig[0].Name, LanguageConfig[0].LanguageStructure); // english - "en"
			return true;
		}
	}

	if (LanguageApplied) return true;

	return false;
}

void PartitionManager::SetLanguage(const string& Language, ushort_t NullConfigState)
{
	VLOGD("Checking speficed language (from input).\n");
	if (!LanguageIsSupport(Language))
		LOGE("Unknown language: %s.\n", Language.c_str());

	LanguageConfigFile.close();

	VLOGD("Checking internal storage dir: `%s'\n", INTERNAL_STORAGE_DIR);
	if (!InternalStorageDirFound())
		LOGE("PartitionManagerSetLanguage: Internal storage directory (`%s') not found or accessible.\n", INTERNAL_STORAGE_DIR);

	VLOGD("Trying to open `%s' with 'open <fstream>'\n", PMTLANG_CONF);
	LanguageConfigFile.open(PMTLANG_CONF, ios::out | ios::trunc);

	if (!LanguageConfigFile.is_open())
		LOGE("PartitionManagerLanguageTools: Cannot open/write config file!!!\n");

	VLOGD("Write \"%s\" to `%s' with 'std <iostream>'\n", Language.c_str(), PMTLANG_CONF);
	LanguageConfigFile << Language;
	if (!LanguageConfigFile)
		LOGE("PartitionManagerLanguageTools: Couldn't write config!!!\n");
	else
		LanguageConfigFile.close();

	if (NullConfigState != 1) {
		VLOGD("Generating dummy file `%s' with 'ofstream <fstream>'\n", PMT_SW_POINT);
		ofstream sw_point(PMT_SW_POINT, ios::trunc);
		if (sw_point.is_open()) sw_point.close();
	}
}

void DisplaySupportedLanguages(void)
{
	VLOGD("Listing supported languages...\n");
	LOGD("List of supported languages: \n");

	for (int i = 0; i < StructSize; i++)
		LOGD("    - %s (%s)\n",
			LanguageConfig[i].ExName,
			LanguageConfig[i].Name);
}

bool PartitionManager::CleanSWPoint(void)
{
	if (GetState(PMT_SW_POINT) == 0) {
		VLOGD("Removing (force) `%s' with 'remove <unistd.h>'\n", PMT_SW_POINT);
		remove(PMT_SW_POINT);
		return true;
	}

	return false;
}

/* end of code */
