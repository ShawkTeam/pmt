/* By YZBruh */

/*
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
#define HELP

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/HelpFn.h>

using namespace PartitionManager;

struct langdb_docs* Display::UsingDocDispString = nullptr;

static void
prepare_langconf_docs(void)
{
    if (Strings::CurrentLanguage == "en")
        Display::UsingDocDispString = &Display::LangDocEn;
    else if (Strings::CurrentLanguage == "tr")
        Display::UsingDocDispString = &Display::LangDocTr;
}

void Functions::DisplayHelp(void)
{
    VLOGD("DisplayHelp: Loading language for help messages... Calling prepare_langconf_docs() <local function>...\n");
    prepare_langconf_docs();
    VLOGD("DisplayHelp: Printing...\n");
    LOGD("%s:  %s %s\n", Display::UsingDocDispString->usage_docstr, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l1);
    LOGD("  %s:   %s %s\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l2);
    LOGD("  %s:   %s %s\n\n", Display::UsingDocDispString->or_str, Strings::ExecutingName.c_str(), Display::UsingDocDispString->docs_strs_l3);
    LOGD("%s: \n", Display::UsingDocDispString->docs_strs_l4);
    LOGD("   -l, --logical     %s\n", Display::UsingDocDispString->docs_strs_l5);
    LOGD("   -c, --context     %s\n", Display::UsingDocDispString->docs_strs_l6);
    LOGD("   -p, --list        %s\n", Display::UsingDocDispString->docs_strs_l7);
    LOGD("   -s, --silent      %s\n", Display::UsingDocDispString->docs_strs_l8);
    LOGD("   -f, --force       %s\n", Display::UsingDocDispString->docs_strs_l9);
    LOGD("   -V, --verbose     %s\n", Display::UsingDocDispString->docs_strs_l10);
    LOGD("   -S, --set-lang    %s\n", Display::UsingDocDispString->docs_strs_l11);
    LOGD("   -v, --version     %s\n", Display::UsingDocDispString->docs_strs_l12);
    LOGD("       --help        %s\n\n", Display::UsingDocDispString->docs_strs_l13);
    LOGD("%s:\n", Display::UsingDocDispString->docs_strs_l14);
    LOGD("   %s backup boot_a -c /dev/block/platform/bootdevice/by-name\n", Strings::ExecutingName.c_str());
    LOGD("   %s flash boot_a /sdcard/twrp/boot.img -c /dev/block/platform/bootdevice/by-name\n", Strings::ExecutingName.c_str());
    LOGD("   %s format system_a ext4 --logical\n", Strings::ExecutingName.c_str());
    LOGD("   %s -c /dev/block/platform/bootdevice/by-name --list\n\n", Strings::ExecutingName.c_str());
    LOGD("%s <t.me/ShawkTeam | Topics | pmt>\n", Display::UsingDocDispString->docs_strs_l15);
}

/* end of code */
