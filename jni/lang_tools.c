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
#define INC_DEBUGERS
#define INC_STAT

#include <pmt/pmt.h>
#include <pmt/stringkeys.h>

/* pmt's man doc file path on termux */
#define TERMUX_PMT_MANDOC "/data/data/com.termux/files/usr/share/man/man8/pmt.8.gz"

#define PMTLANG_CONF "/sdcard/.pmtlang.conf"

#define PMT_SW_POINT "/sdcard/.pmtlangsw"

extern struct pmt_langdb_langs lang[];
struct pmt_langdb_general* current = NULL;

char* curr_lang;
static FILE *langconf;

static const char*
langctrl(const char* _Nonnull lang_)
{
    for (int langct = 0; lang[langct].lang_pr != NULL; langct++)
    {
        if (strcmp(lang_, lang[langct].lang_pr) == 0)
            return lang_;
    }

    return NULL;
}

int loadlang(void)
{
    static char lang_fpr[10] = "en";
    langconf = NULL;

    if (get_stat(TERMUX_PMT_MANDOC, "file") == 0)
        pmt_inst_on_termux = true;


    langconf = fopen(PMTLANG_CONF, "r+");

    if (langconf == NULL)
    {
        langconf = fopen(PMTLANG_CONF, "w+");

        if (langconf == NULL || langconf != NULL)
        {
            setlang("en", 1);
            current = &en;
            curr_lang = "en";

            if (langconf != NULL)
                fclose(langconf);

            return 0;
        }

    }
    else
    {
        while (fgets(lang_fpr, sizeof(lang_fpr), langconf) != NULL)
        {
            if (strcmp(lang_fpr, "en") == 0)
            {
                fclose(langconf);
                current = &en;
                curr_lang = "en";
                return 0;
            }
            else if (strcmp(lang_fpr, "tr") == 0)
            {
                fclose(langconf);
                current = &tr;
                curr_lang = "tr";
                return 0;
            }
            else
            {
                fclose(langconf);
                setlang("en", 0);
                loadlang();
                return 0;
            }
        }

        if (fgets(lang_fpr, sizeof(lang_fpr), langconf) == NULL)
        {
            setlang("en", 1);
            loadlang();
            return 0;
        }
    }

    return 1;
}

void setlang(const char* _Nonnull lang, int null_conf_stat)
{
    if (langctrl(lang) == NULL)
        LOGE("Unknown language: %s.\n", lang);

    if (get_stat(PMTLANG_CONF, "file") == 0)
        remove(PMTLANG_CONF);

    langconf = NULL;
    langconf = fopen(PMTLANG_CONF, "w");

    if (langconf == NULL)
        LOGE("Failed!!! Cannot open/write config file.\n");

    if (fprintf(langconf, "%s", lang) < 2)
        LOGE("Failed!!! Couldn't write config!\n");
    else
        fclose(langconf);

    static int status;

    if (null_conf_stat != 1)
    {
        status = open(PMT_SW_POINT, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (status == 0)
            close(status);
    }
}

int search_sls(void)
{
    if (get_stat(PMT_SW_POINT, "file") == 0)
    {
        remove(PMT_SW_POINT);
        return 0;
    }
    else
        return 1;
}

#ifdef __cplusplus
}
#endif

/* end of code */
