/* By YZBruh */

/*
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
#define HELP_CPP 1

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/HelpFn.h>

using namespace PartitionManager;

struct langdb_docs* Display::UsingDocDispString = nullptr;

static void
PrepareLangconfDocs(void)
{
	if (Strings::CurrentLanguage == "en")
		Display::UsingDocDispString = &Display::LangDocEn;
	else if (Strings::CurrentLanguage == "tr")
		Display::UsingDocDispString = &Display::LangDocTr;
}

void PartitionManager::DisplayHelp(void)
{
	VLOGD("Loading language for help messages... Calling PrepareLangconfDocs() <local function>...\n");
	PrepareLangconfDocs();
	VLOGD("Printing...\n");
	LOGD("%s:  %s %s\n", Display::UsingDocDispString->usage_docstr, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l1);
	LOGD("  %s:   %s %s\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l2);
	LOGD("  %s:   %s %s\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l3);
	LOGD("  %s:   %s %s\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l4);
	LOGD("  %s:   %s %s\n\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l5);
	LOGD("%s:\n", Display::UsingDocDispString->docs_strs_l6);
	LOGD("   -l, --logical     %s\n", Display::UsingDocDispString->docs_strs_l7);
	LOGD("   -P, --search-path %s\n", Display::UsingDocDispString->docs_strs_l8);
	LOGD("   -p, --list        %s\n", Display::UsingDocDispString->docs_strs_l9);
	LOGD("   -s, --silent      %s\n", Display::UsingDocDispString->docs_strs_l10);
	LOGD("   -f, --force       %s\n", Display::UsingDocDispString->docs_strs_l11);
	LOGD("   -V, --verbose     %s\n", Display::UsingDocDispString->docs_strs_l12);
	LOGD("   -S, --set-lang    %s\n", Display::UsingDocDispString->docs_strs_l13);
	LOGD("   -U, --view-langs  %s\n", Display::UsingDocDispString->docs_strs_l14);
	LOGD("   -v, --version     %s\n", Display::UsingDocDispString->docs_strs_l15);
	LOGD("       --help        %s\n\n", Display::UsingDocDispString->docs_strs_l16);
	LOGD("%s:\n", Display::UsingDocDispString->docs_strs_l17);
	LOGD("       --only-size   %s\n", Display::UsingDocDispString->docs_strs_l18);
	LOGD("       --as-byte     %s\n", Display::UsingDocDispString->docs_strs_l19);
	LOGD("       --as-kilobyte %s\n", Display::UsingDocDispString->docs_strs_l20);
	LOGD("       --as-megabyte %s\n", Display::UsingDocDispString->docs_strs_l21);
	LOGD("       --as-gigabyte %s\n\n", Display::UsingDocDispString->docs_strs_l22);
	LOGD("%s:\n", Display::UsingDocDispString->docs_strs_l23);
	LOGD("   %s backup boot_a -P /dev/block/platform/bootdevice/by-name\n", Strings::ExecutingName.c_str());
	LOGD("   %s flash boot_a /sdcard/twrp/boot.img -c /dev/block/platform/bootdevice/by-name\n", Strings::ExecutingName.c_str());
	LOGD("   %s format system_a ext4 --logical\n", Strings::ExecutingName.c_str());
	LOGD("   %s -P /dev/block/platform/bootdevice/by-name --list\n", Strings::ExecutingName.c_str());
	LOGD("   %s partition-size boot --as-byte\n", Strings::ExecutingName.c_str());
	LOGD("   %s partition-size system --only-size --as-gigabyte --logical\n\n", Strings::ExecutingName.c_str());
	LOGD("%s <t.me/ShawkTeam | Topics | pmt>\n", Display::UsingDocDispString->docs_strs_l24);
}

/* end of code */
