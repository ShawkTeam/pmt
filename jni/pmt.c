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

/* force use C std (if default is C++) */
#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS
#define INC_DEBUGERS
#define INC_STAT
#define INC_GETOPT
#define INC_DOCS_REQS

#include <pmt.h>

/* add value to variables that are added globally and are not worth */
char* out = NULL;
char* cust_cxt = NULL;
char* target_partition = NULL;
char* target_flash_file = NULL;
char* partition_type = NULL;
char* format_fs = NULL;
char* bin_name = NULL;
bool pmt_use_logical = false;
bool pmt_use_cust_cxt = false;
bool pmt_ab = false;
bool pmt_logical = false;
bool pmt_silent = false;
bool pmt_flash = false;
bool pmt_backup = false;
bool pmt_format = false;
bool pmt_force_mode = false;
bool pmt_inst_on_termux = false;

/* import language structs etc. */
struct pmt_langdb_general* current = NULL;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;
extern const char* pmt_langdb_langs[];
extern int pmt_langdb_total;

/* variable for use in control of '-' expression */
static const char* opt_symbol = "-";
static char common_symbol_rule[350];

#if !defined(__clang__)

static char*
strdup(const char* s)
{
    size_t len = strlen(s) + 1;
    char* copy = malloc(len);
    if (copy) {
        memcpy(copy, s, len);
    }
    return copy;
}

#endif

/**
 * He controls whether the '-' sign at 
 * the beginning of the given word
 */
static void
check_optsym(const char* _Nonnull mystring)
{
    if (strncmp(mystring, opt_symbol, 1) == 0)
    {
        if (!pmt_force_mode)
            LOGE("%s\n", common_symbol_rule);
        else
            exit(1);
    }
}

/* classic main function (C binary here xd) */
int main(int argc, char* argv[])
{
    bin_name = argv[0];

    /* load language */
    static char* langctrl_str;
    langctrl_str = loadlang();

    if (strcmp(langctrl_str, "en") == 0)
        current = &en;
    else if (strcmp(langctrl_str, "tr") == 0)
        current = &tr;

    sprintf(common_symbol_rule, "%s\n", current->common_symbol_rule);

    if (search_sls() == 0)
    {
        if (current->welcome_ != NULL)
            LOGD("%s", current->welcome_);

        LOGD("%s %s %s %s.\n", current->language, current->welcome, current->by_str, current->lang_by_s);
    }

    /* check argument total */
    if (argc < 2)
        LOGE("%s.\n%s `%s --help' %s.\n", current->missing_operand, current->try_h, argv[0], current->for_more);

    /* a structure for long arguments */
    struct option long_options[] = {
        {"logical", no_argument, 0, 'l'},
        {"context", required_argument, 0, 'c'},
        {"list", no_argument, 0, 'p'},
        {"silent", no_argument, 0, 's'},
        {"force", no_argument, 0, 'f'},
        {"set-language", required_argument, 0, 'S'},
        {"version", no_argument, 0, 'v'},
        {"help", no_argument, 0, 0},
        {"license", no_argument, 0, 'L'},
        {0, 0, 0, 0}
    };

    /* boolean statements (only valid in this file) to distinguish. and pointer from a shortcut for the symbol rule */
    static bool wiew_help = false;
    static bool wiew_licenses = false;
    static bool wiew_version = false;
    static bool list_partitions = false;
    static bool combo_wiewers = false;
    static bool pmt_setlang = false;
    static char* langpr;
    static int search_result = 3;
    static int opt;

    /* control for each argument */
    while ((opt = getopt_long(argc, argv, "lc:psfS:vL", long_options, NULL)) != -1)
    {
        /* process arguments */
        switch (opt)
        {
            /* logical partitions option */
            case 'l':
                check_root();
                check_dev_point();
                if (pmt_logical)
                    pmt_use_logical = true;
                else
                    LOGE("%s\n", current->not_logical);
                break;
            /* context selector option */
            case 'c':
                pmt_use_cust_cxt = true;
                cust_cxt = strdup(optarg);
                check_optsym(cust_cxt);
                break;
            /* partition lister function */
            case 'p':
                list_partitions = true;
                /* check combo wiewer options and progress */
                if (wiew_version || wiew_help || wiew_licenses) combo_wiewers = true;
                break;
            /* force mode option */
            case 'f':
                pmt_force_mode = true;
                break;
            /* silent mode option */
            case 's':
                pmt_silent = true;
                break;
            /* language setter option */
            case 'S':
                pmt_setlang = true;
                langpr = strdup(optarg);
                break;
            /* version info option */
            case 'v':
                wiew_version = true;
                /* check combo wiewer options and progress */
                if (list_partitions || wiew_help || wiew_licenses) combo_wiewers = true;
                break;
            /* help message opption */
            case 0:
                wiew_help = true;
                /* check combo wiewer options and progress */
                if (wiew_version || list_partitions || wiew_licenses) combo_wiewers = true;
                break;
            /* license wiewer option */
            case 'L':
                wiew_licenses = true;
                /* check combo wiewer options and progress */
                if (wiew_version || wiew_help || list_partitions) combo_wiewers = true;
                break;
            /* for invalid options */
            case '?':
                LOGD("%s `%s --help' %s\n", current->try_h, argv[0], current->for_more);
                return 1;
                break;
            default:
                LOGD("%s: %s [backup] [flash] [format] [-l | --logical] [-c | --context] [-p | --list] [-v | --version] [--help] [-L | --license]\n", current->usage_head, argv[0]);
                return 1;
        }
    }

    /* stop the program if multiple viewer is used */
    if (combo_wiewers)
        LOGE("%s", current->multiple_wiewers);

    /* controller to handle viewer */
    if (wiew_help)
    {
        help();
        return 0;
    }
    else if (wiew_version)
    {
        version();
        return 0;
    }
    else if (wiew_licenses)
    {
        licenses();
        return 0;
    }
    else if (list_partitions)
    {
        check_root();
        return listpart();
    }

    if (pmt_setlang)
    {
        LOGD("%s: %s\n", argv[0], current->switching_lang);
        setlang(langpr);
        sleep(2);
        LOGD("%s: %s.\n", argv[0], current->please_rerun);
        return 0;
    }

    /* detect target mode */
    static char arg1[20];
    sprintf(arg1, "%s", argv[1]);

    if (strcmp(argv[1], "backup") == 0)
    {
        if (argc == 2)
            LOGE("%s 0.\n", current->expected_backup_arg);

        target_partition = argv[2];

        if (argc == 3)
            out = target_partition;
        else
            out = argv[3];

        check_optsym(target_partition);
        check_optsym(out);

        pmt_backup = true;
    }
    else if (strcmp(argv[1], "flash") == 0)
    {
        if (argc == 2)
                LOGE("%s 0.\n", current->expected_flash_arg);

        if (argc == 2)
                LOGE("%s 1.\n", current->expected_flash_arg);

        target_flash_file = argv[2];

        target_partition = argv[3];

        check_optsym(target_flash_file);
        check_optsym(target_partition);

        pmt_flash = true;
    }
    else if (strcmp(argv[1], "format") == 0)
    {

        if (argc == 2)
                LOGE("%s 0.\n", current->expected_format_arg);

        if (argc == 3)
                LOGE("%s 1.\n", current->expected_format_arg);

        format_fs = argv[2];

        target_partition = argv[3];

        check_optsym(format_fs);
        check_optsym(target_partition);

        pmt_format = true;
    }

    /* target control is done */
    if (!pmt_backup && !pmt_flash && !pmt_format)
        LOGE("%s `%s --help` %s\n", current->missing_operand, current->try_h, current->for_more);

    /* checks */
    check_root();
    check_dev_point();

    if (pmt_format)
    {
        if (strcmp(format_fs, "ext4") != 0 || strcmp(format_fs, "ext3") != 0 || strcmp(format_fs, "ext2") != 0)
            LOGE("%s: %s\n", current->unsupported_fs, format_fs);
    }

    if (pmt_flash)
    {
        search_result = get_stat(target_flash_file, "file");

        if (search_result == 1)
            LOGE("%s `%s': %s\n", current->cannot_stat, target_flash_file, strerror(errno));
        else if (search_result == -1)
            LOGE("`%s': %s\n", target_flash_file, current->not_file);
    }

    /* custom context checker */
    if (pmt_use_cust_cxt)
    {
        search_result = get_stat(cust_cxt, "dir");

        if (search_result == 1)
            LOGE("%s `%s': %s\n", current->cannot_stat, cust_cxt, strerror(errno));
        else if (search_result == -1)
            LOGE("`%s': %s\n", cust_cxt, current->not_dir);

        if (strstr(cust_cxt, "/dev") == NULL && !pmt_force_mode)
            LOGE("%s\n", current->not_in_dev);
    }

    if (target_partition == NULL)
    {
        if (!pmt_force_mode)
            LOGE("%s\n%s `%s --help' %s\n", current->req_part_name, current->try_h, argv[0], current->for_more);
    }
    else
    {
        /**
         * 1 = backup mode 
         * 
         * 2 = flash mode 
         * 
         * 3 = format
         */
        if (pmt_backup)
            return pmt(1);
        else if (pmt_flash)
            return pmt(2);
        else if (pmt_format)
            return pmt(3);
        else
            LOGE("%s\n%s `%s --help' %s\n", current->no_target, current->try_h, argv[0], current->for_more);
    }
}

#if defined(__cplusplus)
}
#endif

/* end of code */