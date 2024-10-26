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
#define INC_DEBUGERS
#define INC_STAT
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>

using namespace PartitionManager;

/* pmt's man doc file path on termux */
#define INTERNAL_STORAGE_DIR "/sdcard"
#define TERMUX_PMT_MANDOC "/data/data/com.termux/files/usr/share/man/man8/pmt.8.gz"
#define PMTLANG_CONF "/sdcard/.pmtlang.conf"
#define PMT_SW_POINT "/sdcard/.pmtlangsw"

struct langdb_general* Display::UsingDispString = nullptr;
static fstream langconf;
string supp_langs[] = {
    "en",
    "tr",
    ""
};

static bool
InternalStorageDirFound(void)
{
    return (GetState(INTERNAL_STORAGE_DIR, "dir") == 0) ? true : false;
}

static bool
LanguageControl(const string& lang)
{
    for (int i = 0; !supp_langs[i].empty(); i++)
    {
        if (lang == supp_langs[i])
            return true;
    }

    return false;
}

bool PartitionManager::LoadLanguage(void)
{
    string lang_fpr = "en";
    langconf.close();

    VLOGD("Checking install type...\n");
    if (GetState(TERMUX_PMT_MANDOC) == 0)
        Config.InstalledOnTermux = true;

    VLOGD("Checking internal storage dir: `%s'\n", INTERNAL_STORAGE_DIR);
    if (!InternalStorageDirFound())
        LOGE("PartitionManagerLanguageTools: İnternal storage directory (`%s') not found or accessible.\n", INTERNAL_STORAGE_DIR);

    VLOGD("Trying to open `%s' with 'open <fstream>'\n", PMTLANG_CONF);
    langconf.open(PMTLANG_CONF, ios::in | ios::out);

    VLOGD("Checking status: `%s'...\n", PMTLANG_CONF);
    if (!langconf.is_open())
    {
        langconf.open(PMTLANG_CONF, ios::out | ios::trunc);

        VLOGD("Calling SetLanguage()...\n");
        SetLanguage("en", 1);
        Display::UsingDispString = &Display::LangEn;
        Strings::CurrentLanguage = "en";

        if (langconf.is_open())
            langconf.close();

        return true;
    }
    else
    {
        VLOGD("Reading `%s'\n", PMTLANG_CONF);
        while (getline(langconf, lang_fpr))
        {
            if (lang_fpr == "en")
                goto SetEn;
            else if (lang_fpr == "tr")
                goto SetTr;
            else
            {
                VLOGD("Calling SetLanguage()\n");
                SetLanguage("en", 1);
                VLOGD("Re-calling LoadLanguage()\n");
                PartitionManager::LoadLanguage();
                return true;
            }
        }

        if (!getline(langconf, lang_fpr))
        {
            VLOGD("Calling SetLanguage()\n");
            SetLanguage("en", 1);
            VLOGD("Re-calling LoadLanguage()\n");
            PartitionManager::LoadLanguage();
            return true;
        }
    }

SetEn:
    langconf.close();
    Display::UsingDispString = &Display::LangEn;
    Strings::CurrentLanguage = "en";
    VLOGD("Loaded \"en\"\n");
    return true;

SetTr:
    langconf.close();
    Display::UsingDispString = &Display::LangTr;
    Strings::CurrentLanguage = "tr";
    VLOGD("Loaded \"tr\"\n");
    return true;

    return false;
}

void PartitionManager::SetLanguage(const string& lang, ushort_t null_conf_stat)
{
    VLOGD("Checking speficed language (from input).\n");
    if (!LanguageControl(lang))
        LOGE("Unknown language: %s.\n", lang.c_str());

    langconf.close();

    VLOGD("Checking internal storage dir: `%s'\n", INTERNAL_STORAGE_DIR);
    if (!InternalStorageDirFound())
        LOGE("PartitionManagerSetLanguage: Internal storage directory (`%s') not found or accessible.\n", INTERNAL_STORAGE_DIR);

    VLOGD("Trying to open `%s' with 'open <fstream>'\n", PMTLANG_CONF);
    langconf.open(PMTLANG_CONF, ios::out | ios::trunc);

    if (!langconf.is_open())
        LOGE("PartitionManagerLanguageTools: Cannot open/write config file!!!\n");

    VLOGD("Write \"%s\" to `%s' with 'std <iostream>'\n", lang.c_str(), PMTLANG_CONF);
    langconf << lang;
    if (!langconf)
        LOGE("PartitionManagerLanguageTools: Couldn't write config!!!\n");
    else
        langconf.close();

    if (null_conf_stat != 1)
    {
        VLOGD("Generating dummy file `%s' with 'ofstream <fstream>'\n", PMT_SW_POINT);
        ofstream sw_point(PMT_SW_POINT, ios::trunc);
        if (sw_point.is_open())
            sw_point.close();
    }
}

bool PartitionManager::CleanSWPoint(void)
{
    if (GetState(PMT_SW_POINT) == 0)
    {
        VLOGD("Removing (force) `%s' with 'remove <unistd.h>'\n", PMT_SW_POINT);
        remove(PMT_SW_POINT);
        return true;
    }

    return false;
}

/* end of code */
