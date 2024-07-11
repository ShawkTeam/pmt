/* By YZBruh | ShawkTeam */

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

#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_DOCS_REQS

#include <pmt.h>

extern char* bin_name;
extern char* pmt_langdb_langs_docs[];

struct pmt_langdb_docs* curr_docs = NULL;
extern struct pmt_langdb_docs en_docs;
extern struct pmt_langdb_docs tr_docs;

static void
prepare_langconf_docs(void)
{
    static char* langctrl_str;
    langctrl_str = loadlang();

    if (strcmp(langctrl_str, "en") == 0)
        curr_docs = &en_docs;
    else if (strcmp(langctrl_str, "tr") == 0)
        curr_docs = &tr_docs;
}

void licenses(void)
{
    printf("Copyright 2024 Partition Manager\n");
    printf("Licensed under the Apache License, Version 2.0 (the \"License\");\n");
    printf("you may not use this file except in compliance with the License.\n");
    printf("You may obtain a copy of the License at\n\n");
    printf("    http://www.apache.org/licenses/LICENSE-2.0\n\n");
    printf("Unless required by applicable law or agreed to in writing, software\n");
    printf("distributed under the License is distributed on an \"AS IS\" BASIS,\n");
    printf("WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.\n");
    printf("See the License for the specific language governing permissions and limitations under the License.\n");
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
    printf("       --help        %s\n", curr_docs->docs_strs_l12);
    printf("   -L, --license     %s\n\n", curr_docs->docs_strs_l13);
    printf("%s:\n", curr_docs->docs_strs_l14);
    printf("   %s backup boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s flash /sdcard/twrp/boot.img boot_a -c /dev/block/platform/bootdevice/by-name\n", bin_name);
    printf("   %s format ext4 system_a --logical\n", bin_name);
    printf("   %s -c /dev/block/platform/bootdevice/by-name --list\n\n", bin_name);
    printf("%s <t.me / ShawkTeam | Community / Topics -- pmt>\n", curr_docs->docs_strs_l15);
}

#if defined(__cplusplus)
}
#endif /* __cplusplus */

/* end of code */
