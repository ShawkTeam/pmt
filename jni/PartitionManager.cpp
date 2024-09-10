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
#define INC_LIBGEN
#define INC_STRINGKEYS

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/Deprecates.h>
#include <PartitionManager/HelpFn.h>
#include <PartitionManager/VersionFnVars.h>

/* add value to variables that are added globally and are not worth */
namespace PartitionManager {
    namespace Strings {
        string OutputName = "";
        string CustomContext = "";
        string TargetPartition = "";
        string TargetFlashFile = "";
        string TargetFormatFS = "";
        string PartitionType = "";
        string ExecutingName = "";
        string CurrentLanguage = "";
    } /* namespace Strings */

    namespace Booleans {
        bool UseLogical = false;
        bool UseCustomContext = false;
        bool UsesSlots = false;
        bool UsesLogical = false;
        bool SilentEnabled = false;
        bool FlashMode = false;
        bool BackupMode = false;
        bool FormatMode = false;
        bool ForceMode = false;
        bool VerboseMode = false;
        bool InstalledOnTermux = false;
        bool ActivateRoot = false;
    } /* namespace Booleans */
} /* namespace PartitionManager */

/* variable for use in control of '-' expression */
static string common_symbol_rule;

namespace PartitionManager {
namespace Functions {

/**
 * He controls whether the '-' sign at 
 * the beginning of the given word
 */
static void
CheckOptSymbol(const string symbol)
{
    if (!symbol.empty())
    {
        if (strncmp(symbol.c_str(), "-", 1) == 0)
            LOGE("%s\n", common_symbol_rule.c_str());
    }
}

static bool
ControlArg(const char* argv_holder)
{
    if (argv_holder[0] != '-')
        return true;

    return false;
}

} /* namespace Functions */
} /* namespace PartitionManager */

static void
deprecated(const char opt, const char* deprecation_message, const char* opt_long = "ISNULL")
{
    VLOGE("Deprecated Option: -%c (--%s). Printing error...\n", opt, opt_long);
    DEPR_HANDLE(opt, opt_long, deprecation_message);
    exit(1);
}

static void
PrContextInput(const string& context)
{
    PartitionManager::Booleans::UseCustomContext = true;
    PartitionManager::Strings::CustomContext = context;
    PartitionManager::Functions::CheckOptSymbol(PartitionManager::Strings::CustomContext);
}

using namespace PartitionManager;

class PartitionManagerBase {
protected:
    char* BaseFunctionName = nullptr;
    int StartCode = -1;
    bool IsRequiredOnlyOneArg = false;

public:
    void CallTargetBaseFunction(void)
    {
        VLOGD("CallTargetBaseFunction [class]: Start(%d)\n", StartCode);
        Functions::Start(StartCode);
    }

    void GenericNumericalController(int searchOn, int total, const char* MissingArgMessage)
    {
        if (total <= searchOn)
        {
            VLOGE("ArgumentProcessor [class]: Missing argument total (for %s function).\n", BaseFunctionName);
            LOGE("%s 0.\n", MissingArgMessage);
        }

        if (!IsRequiredOnlyOneArg)
        {
            if (total <= (searchOn + 1))
            {
                VLOGE("ArgumentProcessor [class]: Missing argument total (for %s function).\n", BaseFunctionName);
                LOGE("%s 1.\n", MissingArgMessage);
            }
        }
    }

    virtual void ArgumentProcessor(int searchOn, int total, char** arguments) { /* dummy, it's place holder */ }
};

class PartitionManagerBackup : public PartitionManagerBase {
public:
    void ArgumentProcessor(int searchOn, int total, char** arguments) override
    {
        BaseFunctionName = "backup";
        StartCode = 1;
        IsRequiredOnlyOneArg = true;

        GenericNumericalController(searchOn, total, Display::UsingDispString->expected_backup_arg);

        if (Functions::ControlArg(arguments[searchOn]))
            Strings::TargetPartition = arguments[searchOn];
        else
            LOGE("%s.\n", Display::UsingDispString->not_spec_opt);

        Strings::OutputName = Strings::TargetPartition;

        if (total > (searchOn + 1) && Functions::ControlArg(arguments[(searchOn + 1)]))
        {
            VLOGD("ArgumentProcessor [class]: Non-mandatory argument was detected and retrieved (for %s function).\n", BaseFunctionName);
            Strings::OutputName = arguments[(searchOn + 1)];
        }

        Functions::CheckOptSymbol(Strings::TargetPartition);
        Functions::CheckOptSymbol(Strings::OutputName);
    }
};

class PartitionManagerFlash : public PartitionManagerBase {
public:
    void ArgumentProcessor(int searchOn, int total, char** arguments) override
    {
        BaseFunctionName = "flash";
        StartCode = 2;
        IsRequiredOnlyOneArg = false;

        GenericNumericalController(searchOn, total, Display::UsingDispString->expected_flash_arg);

        if (Functions::ControlArg(arguments[searchOn]))
            Strings::TargetPartition = arguments[searchOn ];
        else
            LOGE("%s.\n", Display::UsingDispString->not_spec_opt);

        if (Functions::ControlArg(arguments[(searchOn + 1)]))
            Strings::TargetFlashFile = arguments[(searchOn + 1)];
        else
            LOGE("%s.\n", Display::UsingDispString->not_spec_opt);

        Functions::CheckOptSymbol(Strings::TargetFlashFile);
        Functions::CheckOptSymbol(Strings::TargetPartition);
    }
};

class PartitionManagerFormat : public PartitionManagerBase {
public:
    void ArgumentProcessor(int searchOn, int total, char** arguments) override
    {
        BaseFunctionName = "format";
        StartCode = 3;
        IsRequiredOnlyOneArg = false;

        GenericNumericalController(searchOn, total, Display::UsingDispString->expected_format_arg);

        if (Functions::ControlArg(arguments[searchOn]))
            Strings::TargetPartition = arguments[searchOn];
        else
            LOGE("%s.\n", Display::UsingDispString->not_spec_opt);

        if (Functions::ControlArg(arguments[(searchOn + 1)]))
            Strings::TargetFormatFS = arguments[(searchOn + 1)];
        else
            LOGE("%s.\n", Display::UsingDispString->not_spec_opt);

        Functions::CheckOptSymbol(Strings::TargetFormatFS);
        Functions::CheckOptSymbol(Strings::TargetPartition);
    }
};

int main(int argc, char** argv)
{
    Strings::ExecutingName = basename(argv[0]);

    for (int i = 0; i <= (argc - 1); i++)
    {
        if (strncmp(argv[i], "-V", 2) == 0 || strcmp(argv[i], "--verbose") == 0)
            Booleans::VerboseMode = true;
        else
            continue;
    }

    /* Generate classes */
    VLOGD("Generating classes...\n");
    PartitionManagerBase* Base;
    PartitionManagerBase BaseTemplate;
    PartitionManagerBackup BackupArgProcessorBase;
    PartitionManagerFlash FlashArgProcessorBase;
    PartitionManagerFormat FormatArgProcessorBase;

    VLOGD("Main function started. Setting up locale. Calling 'setlocale <clocale>'\n");
    setlocale(LC_ALL, "");

    int argc_n = argc;
    char buf[256];
    char** args = argv;

    VLOGD("Checking stdin status...\n");
    if (!isatty(fileno(stdin)))
    {
        VLOGD("stdin is not empty.\n");
        VLOGD("Parsing stdin arguments...\n");

        while (fgets(buf, sizeof(buf), stdin) != nullptr)
        {
            buf[strcspn(buf, "\n")] = 0;

            args[argc_n] = strdup(buf);
            argc_n++;
        }

        VLOGD("Parsing completed.\n");
    }
    else
        VLOGD("stdin empty.\n");

    /* load language */
    VLOGD("Loading language... Calling LoadLanguage()...\n");
    if (!Functions::LoadLanguage())
    {
        cout << "LoadLanguage() process failed..!" << endl;
        abort();
    }

    common_symbol_rule = Display::UsingDispString->common_symbol_rule;
    argc = argc_n;
    int argc_parse = (argc - 1);
    char** args_ctrl = args;
    args_ctrl++;

    static bool ViewHelp = false;
    static bool ViewVersion = false;
    static bool LogicalSpeficy = false;
    static bool ListRequired = false;
    static bool MultipleViewers = false;
    static bool SetLanguageReq = false;
    static bool SomeSpec = false;
    static char* SpeficedLanguagePr;
    static string Option;
    static string Target;
    static int SearchResult = 3;
    static int SearchOnMainInt = -1;

    VLOGD("Parsing standart arguments...\n");
    while (argc_parse && args_ctrl[0] != nullptr)
    {
        if (args_ctrl[0][0] != '-')
        {
            argc_parse--;
            args_ctrl++;
            continue;
        }

        for (int x = 1; true; x++)
        {
            Option = args_ctrl[0];
            SomeSpec = true;

            switch (args_ctrl[0][x])
            {
                case '-':
                    if (Option == "--backup")
                        deprecated('b', Display::UsingDispString->depr_backup_opt, "backup");
                    else if (Option == "--flash")
                        deprecated('F', Display::UsingDispString->depr_flash_opt, "flash");
                    else if (Option == "--format")
                        deprecated('r', Display::UsingDispString->depr_format_opt, "format");
                    else if (Option == "--license")
                        deprecated('L', Display::UsingDispString->depr_Vlicense_opt, "license");
                    else if (Option == "--logical")
                    {
                        VLOGD("Logical partition type specified.\n");
                        LogicalSpeficy = true;
                        break;
                    }
                    else if (Option == "--context")
                    {
                        VLOGD("Custom context specified.\n");
                        if (argc_parse > 1)
                            PrContextInput(args_ctrl[1]);
                        else
                            LOGE("--context: %s.\n%s `%s --help' %s.\n", \
                            Display::UsingDispString->is_requires_arg, \
                            Display::UsingDispString->try_h, \
                            Strings::ExecutingName.c_str(), \
                            Display::UsingDispString->for_more);
                        break;
                    }
                    else if (Option == "--list")
                    {
                        VLOGD("It was requested to list the partitions.\n");
                        ListRequired = true;
                        if (ViewVersion || ViewHelp)
                            MultipleViewers = true;
                        break;
                    }
                    else if (Option == "--force")
                    {
                        VLOGD("Force mode speficed.\n");
                        Booleans::ForceMode = true;
                        break;
                    }
                    else if (Option == "--verbose")
                    {
                        VLOGD("Verbose mode speficed.\n");
                        Booleans::VerboseMode = true;
                        break;
                    }
                    else if (Option == "--silent")
                    {
                        VLOGD("Silent mode speficed.\n");
                        Booleans::SilentEnabled = true;
                        break;
                    }
                    else if (Option == "--set-language")
                    {
                        VLOGD("It was requested to adjust the language.\n");
                        if (argc_parse > 1)
                        {
                            VLOGE("Language inputs: getting inputs...\n");
                            SetLanguageReq = true;
                            SpeficedLanguagePr = args_ctrl[1];
                        }
                        else
                            LOGE("--set-language: %s.\n%s `%s --help' %s.\n", \
                            Display::UsingDispString->is_requires_arg, \
                            Display::UsingDispString->try_h, \
                            Strings::ExecutingName.c_str(), \
                            Display::UsingDispString->for_more);
                        break;
                    }
                    else if (Option == "--version")
                    {
                        VLOGD("The version info was requested to be displayed.\n");
                        ViewVersion = true;
                        if (ListRequired || ViewHelp)
                            MultipleViewers = true;
                        break;
                    }
                    else if (Option == "--help")
                    {
                        VLOGD("The help message was requested to be displayed.\n");
                        ViewHelp = true;
                        if (ViewVersion || ListRequired)
                            MultipleViewers = true;
                        break;
                    }
                    else
                    {
                        VLOGE("Unknown Option: %s\n", args_ctrl[0]);
                        LOGE("%s: %s.\n%s `%s --help' %s.\n", args_ctrl[0], \
                        Display::UsingDispString->unknw_arg, \
                        Display::UsingDispString->try_h, \
                        Strings::ExecutingName.c_str(), \
                        Display::UsingDispString->for_more);
                    }
                    break;
                case 'b':
                    deprecated('b', Display::UsingDispString->depr_backup_opt, "backup");
                    break;
                case 'F':
                    deprecated('F', Display::UsingDispString->depr_flash_opt, "flash");
                    break;
                case 'r':
                    deprecated('r', Display::UsingDispString->depr_format_opt, "format");
                    break;
                case 'L':
                    deprecated('L', Display::UsingDispString->depr_Vlicense_opt, "license");
                    break;
                case 'D':
                    deprecated('D', Display::UsingDispString->depr_ch_list_opt);
                    break;
                case 'l':
                    VLOGD("Logical partition type specified.\n");
                    LogicalSpeficy = true;
                    continue;
                case 'c':
                    VLOGD("Custom context speficed.\n");
                    if (argc_parse > 1)
                    {
                        VLOGE("Context inputs: getting inputs...\n");
                        PrContextInput(args_ctrl[1]);
                        continue;
                    }
                    else
                        LOGE("-c: %s.\n%s `%s --help' %s.\n", \
                        Display::UsingDispString->is_requires_arg, \
                        Display::UsingDispString->try_h, \
                        Strings::ExecutingName.c_str(), \
                        Display::UsingDispString->for_more);
                    break;
                case 'p':
                    VLOGD("It was requested to list the partitions.\n");
                    ListRequired = true;
                    if (ViewVersion || ViewHelp)
                        MultipleViewers = true;
                    continue;
                case 'f':
                    VLOGD("Force mode speficed.\n");
                    Booleans::ForceMode = true;
                    continue;
                case 'V':
                    VLOGD("Verbose mode speficed.\n");
                    Booleans::VerboseMode = true;
                    continue;
                case 's':
                    VLOGD("Silent mode speficed.\n");
                    Booleans::SilentEnabled = true;
                    continue;
                case 'S':
                    VLOGD("It was requested to adjust the language.\n");
                    if (argc_parse > 1)
                    {
                        VLOGE("Language inputs: getting inputs...\n");
                        SetLanguageReq = true;
                        SpeficedLanguagePr = args_ctrl[1];
                        continue;
                    }
                    else
                        LOGE("-S: %s.\n%s `%s --help' %s.\n", \
                        Display::UsingDispString->is_requires_arg, \
                        Display::UsingDispString->try_h, \
                        Strings::ExecutingName.c_str(), \
                        Display::UsingDispString->for_more);
                case 'v':
                    VLOGD("The version info was requested to be displayed.\n");
                    ViewVersion = true;
                    if (ListRequired || ViewHelp)
                        MultipleViewers = true;
                    continue;
                case '\0':
                    break;
                default:
                    VLOGE("Unknown Option: -%c\n", args_ctrl[0][x]);
                    LOGE("-%c: %s.\n%s `%s --help' %s.\n", args_ctrl[0][x], \
                    Display::UsingDispString->unknw_arg, \
                    Display::UsingDispString->try_h, \
                    Strings::ExecutingName.c_str(), \
                    Display::UsingDispString->for_more);
            }

            break;
        }

        argc_parse--;
        args_ctrl++;
    }

    Base = &BaseTemplate;
    argc_parse = argc;

    VLOGD("Starting cycle for trapping main options...\n");
    while (1)
    {
        if ((argc_parse - 1) == 0)
        {
            VLOGD("MainFnController: argc - 1 = 0. Breaking...\n");
            break;
        }

        if (args[(argc_parse - 1)][0] == '-')
        {
            VLOGD("MainFnController: args[%d] starts with '-'. Continue.\n", (argc_parse - 1));
            argc_parse--;
            continue;
        }
        else
        {
            Target = args[(argc_parse - 1)];
            SearchOnMainInt = argc_parse;
            VLOGD("MainFnController: args[%d] = %s\n", (argc_parse - 1), args[(argc_parse - 1)]);
            VLOGD("MainFnController: variable of \"Target\" (string): %s\n", Target.c_str());

            if (Target == "backup")
            {
                Base = &BackupArgProcessorBase;
                Booleans::BackupMode = true;
                break;
            }
            else if (Target == "flash")
            {
                Base = &FlashArgProcessorBase;
                Booleans::FlashMode = true;
                break;
            }
            else if (Target == "format")
            {
                Base = &FormatArgProcessorBase;
                Booleans::FormatMode = true;
                break;
            }
            else
            {
                Target = "";
                SearchOnMainInt = -1;
                argc_parse--;
                continue;
            }
        }

        break;
    }

    if (Booleans::SilentEnabled && Booleans::VerboseMode)
    {
        VLOGE("Silent and verbose mode is one-way.\n");
        cout << Strings::ExecutingName << ": " << Display::UsingDispString->s_and_v << endl;
        exit(1);
    }

    VLOGD("Checking last language switch status...\n");
    if (Functions::CleanSWPoint())
    {
        VLOGD("Last transactions found that language was changed between.\n");

        if (Display::UsingDispString->welcome_ != nullptr)
            LOGD("%s", Display::UsingDispString->welcome_);

        LOGD("%s %s %s %s.\n", Display::UsingDispString->language, Display::UsingDispString->welcome, Display::UsingDispString->by_str, Display::UsingDispString->lang_by_s);
    }

    /* check argument total */
    VLOGD("argc (arguments) total: %d.\n", argc);
    if (argc < 2)
        LOGE("%s.\n%s '%s --help' %s.\n", Display::UsingDispString->missing_operand, Display::UsingDispString->try_h, Strings::ExecutingName.c_str(), Display::UsingDispString->for_more);

    /* stop the program if multiple viewer is used */
    if (MultipleViewers)
    {
        VLOGE("Multiple viewer option selected!\n");
        LOGE("%s\n", Display::UsingDispString->multiple_wiewers);
    }

    /* controller to handle viewer */
    if (ViewHelp)
    {
        VLOGD("The help message was asked to display. It's displayed... Calling DisplayHelp()\n");
        Functions::DisplayHelp();
        return 0;
    }
    else if (ViewVersion)
    {
        VLOGD("The version info message was asked to display. It's displayed... Calling DisplayVersion()\n");
        Functions::DisplayVersion();
        return 0;
    }
    else if (ListRequired)
    {
        VLOGD("Partitions were asked to be listed. It's listed... Calling CheckRoot() (root check is required), CheckDevPoint() (for generating warnings etc.) and ListPartitions()\n");
        Functions::CheckRoot();
        VLOGD("CheckRoot() completed.\n");
        Functions::CheckDevPoint();
        VLOGD("CheckDevPoint() completed.\n");
        return Functions::ListPartitions();
    }

    if (SetLanguageReq)
    {
        VLOGD("The language was asked to adjust. Calling SetLanguage()...\n");
        LOGD("%s: %s\n", Strings::ExecutingName.c_str(), Display::UsingDispString->switching_lang);
        Functions::SetLanguage(SpeficedLanguagePr, 0);
        sleep(2);
        VLOGD("SetLanguage() completed.\n");
        LOGD("%s: %s.\n", Strings::ExecutingName.c_str(), Display::UsingDispString->please_rerun);
        return 0;
    }

    if (Target.empty())
    {
        VLOGE("There's no job to do.\n");
        LOGD("%s: %s.\n", Strings::ExecutingName.c_str(), Display::UsingDispString->missing_operand);

        if (SomeSpec)
            LOGD("%s.\n", Display::UsingDispString->some_spec);

        LOGD("%s '%s --help' %s.\n",Display::UsingDispString->try_h, Strings::ExecutingName.c_str(), Display::UsingDispString->for_more);
        exit(1);
    }

    Base->ArgumentProcessor(SearchOnMainInt, argc, args);

    if (Booleans::FormatMode)
    {
        VLOGD("File system name specified for formatting is being contaminated...\n");
        if (Strings::TargetFormatFS != "ext4" \
        && Strings::TargetFormatFS != "ext3" \
        && Strings::TargetFormatFS != "ext2")
        {
            VLOGE("Unsupported file system: %s.\n", Strings::TargetFormatFS.c_str());
            LOGE("%s: %s\n", Display::UsingDispString->unsupported_fs, Strings::TargetFormatFS.c_str());
        }
    }

    /* checks */
    VLOGD("Checking root status... Calling CheckRoot()...\n");
    Functions::CheckRoot();
    VLOGD("Checking A/B and logical device status... Calling CheckDevPoint()...\n");
    Functions::CheckDevPoint();

    if (LogicalSpeficy)
    {
        VLOGD("Logical partition type speficed. Checking partition statust's...\n");
        if (Booleans::UsesLogical)
            Booleans::UseLogical = true;
        else
            LOGE("%s\n", Display::UsingDispString->not_logical);
    }

    if (Booleans::FlashMode)
    {
        VLOGD("The status of the specified file for flashing is being checked...\n");
        SearchResult = Functions::GetState(Strings::TargetFlashFile);

        if (SearchResult == 1)
            LOGE("%s: `%s': %s\n", Display::UsingDispString->cannot_stat, Strings::TargetFlashFile.c_str(), strqerror());
        else if (SearchResult == -1)
            LOGE("`%s': %s\n", Strings::TargetFlashFile.c_str(), Display::UsingDispString->not_file);
    }

    /* custom context checker */
    if (Booleans::UseCustomContext)
    {
        VLOGD("The status of the \"dev\" is controlled in the specified custom /dev context...\n");
        if (strncmp(Strings::CustomContext.c_str(), "/dev", 4) != 0)
        {
            if (!Booleans::ForceMode)
                LOGE("%s\n", Display::UsingDispString->not_in_dev);
        }

        VLOGD("The specified custom /dev context is being put in countless...\n");
        SearchResult = Functions::GetState(Strings::CustomContext, "dir");

        if (SearchResult == 1)
            LOGE("%s: `%s': %s\n", Display::UsingDispString->cannot_stat, Strings::CustomContext.c_str(), strqerror());
        else if (SearchResult == -1)
            LOGE("`%s': %s\n", Strings::CustomContext.c_str(), Display::UsingDispString->not_dir);
    }

    VLOGD("The partition specification status is controlled...\n");
    if (Strings::TargetPartition.empty())
    {
        if (!Booleans::ForceMode)
            LOGE("%s\n%s `%s --help' %s\n", Display::UsingDispString->req_part_name, Display::UsingDispString->try_h, Strings::ExecutingName.c_str(), Display::UsingDispString->for_more);
    }
    else
    {
        VLOGD("The call of main operations is being checked in case of the call...\n");
        if (!Target.empty())
            Base->CallTargetBaseFunction();
    }
}

/* end of code */
