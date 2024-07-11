/* By YZBruh | ShawkTeam */

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

#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_DEBUGERS
#define INC_STAT

#include <pmt.h>

/* pmt's man doc file path on termux */
#define TERMUX_PMT_MANDOC "/data/data/com.termux/files/usr/share/man/man8/pmt.8.gz"

/* language configuration paths */

/* for termux */
#define TERMUX_PMTLANG_CONF "/data/data/com.termux/files/usr/etc/pmtlang.conf"

/* for internal storage */
#define INTRNL_PMTLANG_CONF "/sdcard/.pmtlang.conf"

/* shortcuts to check that language is changed */

/* for termux */
#define TERMUX_PMT_SW_POINT "/data/data/com.termux/files/usr/etc/pmtlangsw"

/* for internal storage */
#define INTRNL_PMT_SW_POINT "/sdcard/.pmtlangsw"

extern bool pmt_inst_on_termux;
extern char* bin_name;
extern char* pmt_langdb_langs[];
extern int pmt_langdb_total;
extern int pmt_langdb_ctrl;

FILE *langconf;

static int
langctrl(const char* _Nonnull lang_)
{
    if (strcmp(lang_, "en") == 0 || strcmp(lang_, "tr") == 0)
        return 0;

    return 1;
}

char* loadlang(void)
{
    static char lang_fpr[10] = "en";
    langconf = NULL;

    if (get_stat(TERMUX_PMT_MANDOC, "file") == 0)
        pmt_inst_on_termux = true;

    if (pmt_inst_on_termux)
    {
        if (get_stat(TERMUX_PMTLANG_CONF, "file") == 0)
        {
            langconf = fopen(TERMUX_PMTLANG_CONF, "r+");

            if (langconf == NULL)
            {
                langconf = fopen(TERMUX_PMTLANG_CONF, "w+");

                if (langconf == NULL)
                {
                    setlang("en");
                    return "en";
                }
                fclose(langconf);
            }
            else
            {
                while (fgets(lang_fpr, sizeof(lang_fpr), langconf) != NULL)
                {
                    if (strcmp(lang_fpr, "en") == 0)
                    {
                        fclose(langconf);
                        return "en";
                    }
                    else if (strcmp(lang_fpr, "tr") == 0)
                    {
                        fclose(langconf);
                        return "tr";
                    }
                }
                fclose(langconf);
            }
        }
    }
    else
    {
        if (get_stat(INTRNL_PMTLANG_CONF, "file") == 0)
        {
            langconf = fopen(INTRNL_PMTLANG_CONF, "r");

            if (langconf == NULL)
            {
                langconf = fopen(INTRNL_PMTLANG_CONF, "w+");

                if (langconf == NULL)
                {
                    setlang("en");
                    return "en";
                }
                fclose(langconf);
            }
            else
            {
                while (fgets(lang_fpr, sizeof(lang_fpr), langconf) != NULL)
                {
                    if (strcmp(lang_fpr, "en") == 0)
                    {
                        fclose(langconf);
                        return "en";
                    }
                    else if (strcmp(lang_fpr, "tr") == 0)
                    {
                        fclose(langconf);
                        return "tr";
                    }
                }
                fclose(langconf);
            }
        }
        else return "en";
    }

    return "en";
}

void setlang(const char* _Nonnull lang)
{
    static char* lcf_path;

    if (pmt_inst_on_termux)
        lcf_path = TERMUX_PMTLANG_CONF;
    else
        lcf_path = INTRNL_PMTLANG_CONF;

    if (get_stat(lcf_path, "file") == 0)
        remove(lcf_path);

    langconf = NULL;

    if (pmt_inst_on_termux)
        langconf = fopen(TERMUX_PMTLANG_CONF, "w");
    else
        langconf = fopen(INTRNL_PMTLANG_CONF, "w");

    if (langconf == NULL)
        LOGE("Failed!!! Cannot open/write config file.\n");

    if (langctrl(lang) == 0)
    {
        if (fprintf(langconf, "%s", lang) < 2)
            LOGE("Failed!!! Couldn't write config!\n");
        else
            fclose(langconf);
    }
    else
        LOGE("Unknown language: %s.\n", lang);

    static int status;

    if (pmt_inst_on_termux)
    {
        status = open(TERMUX_PMT_SW_POINT, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (status == 0)
            close(status);
    }
    else
    {
        status = open(INTRNL_PMT_SW_POINT, O_WRONLY | O_CREAT | O_TRUNC, 0666);
        if (status == 0)
            close(status);
    }
}

int search_sls(void)
{
    static char* sw_point_path;

    if (pmt_inst_on_termux)
        sw_point_path = TERMUX_PMT_SW_POINT;
    else
        sw_point_path = INTRNL_PMT_SW_POINT;

    if (get(sw_point_path, "file") == 0)
    {
        remove(sw_point_path);
        return 0;
    }
    else
        return 1;
}

#if defined(__cplusplus)
}
#endif

/* end of code */
