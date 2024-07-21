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

#ifdef __cplusplus
extern "C" {
#endif

#define INC_MAIN_LIBS

#include <pmt/pmt.h>
#include <pmt/stringkeys.h>
#include <pmt/docs.h>

extern char* bin_name;
extern char* curr_lang;

struct pmt_langdb_docs* curr_docs = NULL;

static void
prepare_langconf_docs(void)
{
    if (strcmp(curr_lang, "en") == 0)
        curr_docs = &en_docs;
    else if (strcmp(curr_lang, "tr") == 0)
        curr_docs = &tr_docs;
}

void help(void)
{
    prepare_langconf_docs();
    printf("%s:  %s %s\n", curr_docs->usage_docstr, bin_name, curr_docs->docs_strs_l1);
    printf("  %s:   %s %s\n", curr_docs->or_str, bin_name, curr_docs->docs_strs_l2);
    printf("  %s:   %s %s\n\n", curr_docs->or_str, bin_name, curr_docs->docs_strs_l3);
    printf("%s: \n", curr_docs->docs_strs_l4);
    printf("   -l, --logical     %s\n", curr_docs->docs_strs_l5);
    printf("   -c, --context     %s\n", curr_docs->docs_strs_l6);
    printf("   -p, --list        %s\n", curr_docs->docs_strs_l7);
    printf("   -s, --silent      %s\n", curr_docs->docs_strs_l8);
    printf("   -f, --force       %s\n", curr_docs->docs_strs_l9);
    printf("   -S, --set-lang    %s\n", curr_docs->docs_strs_l10);
    printf("   -v, --version     %s\n", curr_docs->docs_strs_l11);
    printf("       --help        %s\n\n", curr_docs->docs_strs_l12);
    printf("%s:\n", curr_docs->docs_strs_l13);
    printf("   %s backup boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s flash /sdcard/twrp/boot.img boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s format ext4 system_a --logical\n", bin_name);
    printf("   %s -c /dev/block/platform/bootdevice/by-name --list\n\n", bin_name);
    printf("%s <t.me/ShawkTeam | Topics | pmt>\n", curr_docs->docs_strs_l14);
}

#ifdef __cplusplus
}
#endif /* __cplusplus */

/* end of code */
