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
#define INC_LIBGEN 1
#define INC_STRINGKEYS 1
#define IS_MAIN 1

#include <PartitionManager/PartitionManager.h>
#include <PartitionManager/Deprecates.h>
#include <PartitionManager/HelpFn.h>
#include <PartitionManager/VersionFnVars.h>
#include <PartitionManager/PartSizeMacros.h>

/* add value to variables that are added globally and are not worth */
namespace PartitionManager {
	namespace Strings {
		string OutputName = "";
		string CustomSearchPath = "";
		string TargetPartition = "";
		string TargetFlashFile = "";
		string TargetFormatFS = "";
		string PartitionType = "";
		string Device = "";
		string ExecutingName = "";
		string CurrentLanguage = "";
	} /* namespace Strings */

	namespace Integers {
		int PartSizeViewType = VIEW_AS_MIB;
	} /* namespace Integers */
} /* namespace PartitionManager */

/* configure struct body */
struct Configuration Config {
	/* general boolean tab */
	.UseLogical = false,
	.UseCustomSearchPath = false,
	.UsesSlots = false,
	.UsesLogical = false,
	.SilentEnabled = false,
	.FlashMode = false,
	.BackupMode = false,
	.FormatMode = false,
	.PartedMode = false,
	.PartSizeViewMode = false,
	.PartUtilMode = false,
	.ForceMode = false,
	.VerboseMode = false,
	.InstalledOnTermux = false,

	/* part-size argument bools */
	.OnlyViewSize = false,
};

/* some variables. for parsing and processing arguments */
static bool ViewHelp = false;
static bool ViewVersion = false;
static bool LogicalSpeficy = false;
static bool ListRequired = false;
static bool MultipleViewers = false;
static bool SetLanguageReq = false;
static bool SomeSpec = false;
static bool PartSizeArgSpeficed = false;
static bool ListSupportedLanguages = false;
static char* SpeficedLanguagePr;
static string Option;
static string Target;
static string SymbolRule;
static int StdinArgcTotal;
static int SearchOnMainInt;

namespace PartitionManager {

/**
 * He controls whether the '-' sign at 
 * the beginning of the given word
 */
static inline void
CheckOptSymbol(const string& Symbol)
{
	if (!Symbol.empty()) {
		if (strncmp(Symbol.c_str(), "-", 1) == 0)
			LOGE("%s\n", SymbolRule.c_str());
	}
}

static inline bool
ControlArg(char* &ArgvHolder)
{
	if (ArgvHolder[0] != '-') return true;

	return false;
}

} /* namespace PartitionManager */

static void
deprecated(const char &opt, const char* &deprecation_message, const char* opt_long = "IS_EMPTY")
{
	VLOGE("Deprecated Option: -%c (--%s). Printing error...\n", opt, opt_long);
	DEPR_HANDLE(opt, opt_long, deprecation_message);

	exit(1);
}

static inline void
PrSpInput(const string& sp)
{
	Config.UseCustomSearchPath = true;
	PartitionManager::Strings::CustomSearchPath = sp;
	PartitionManager::CheckOptSymbol(PartitionManager::Strings::CustomSearchPath);
}

class PartitionManagerBase {
protected:
	char* BaseFunctionName = nullptr;
	int StartCode = -1;
	bool IsRequiredOnlyOneArg = false;

public:
	void CallTargetBaseFunction(void)
	{
		VLOGD("[class]: Call PartitionManagerMain(%d)\n", StartCode);
		PartitionManager::PartitionManagerMain(StartCode);
	}

	void GenericNumericalController(int& searchOn, int& total, const char* &MissingArgMessage)
	{
		if (total <= searchOn) {
			VLOGE("[class]: Missing argument total (for %s function).\n", BaseFunctionName);
			LOGE("%s 0.\n", MissingArgMessage);
		}

		if (!IsRequiredOnlyOneArg) {
			if (total <= (searchOn + 1)) {
				VLOGE("[class]: Missing argument total (for %s function).\n", BaseFunctionName);
				LOGE("%s 1.\n", MissingArgMessage);
			}
		}
	}

	virtual void ArgumentProcessor(int& searchOn, int& total, char** &arguments) { /* dummy */ }
};

class PartitionManagerBackup : public PartitionManagerBase {
public:
	void ArgumentProcessor(int& searchOn, int& total, char** &arguments) override
	{
		BaseFunctionName = "backup";
		StartCode = 1;
		IsRequiredOnlyOneArg = true;

		GenericNumericalController(searchOn, total, PartitionManager::Display::UsingDispString->expected_backup_arg);

		if (PartitionManager::ControlArg(arguments[searchOn]))
			PartitionManager::Strings::TargetPartition = arguments[searchOn];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		PartitionManager::Strings::OutputName = PartitionManager::Strings::TargetPartition;

		if (total > (searchOn + 1) && PartitionManager::ControlArg(arguments[(searchOn + 1)])) {
			VLOGD("[class]: Non-mandatory argument was detected and retrieved (for %s function).\n", BaseFunctionName);
			PartitionManager::Strings::OutputName = arguments[(searchOn + 1)];
		}

		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetPartition);
		PartitionManager::CheckOptSymbol(PartitionManager::Strings::OutputName);
	}
};

class PartitionManagerFlash : public PartitionManagerBase {
public:
	void ArgumentProcessor(int& searchOn, int& total, char** &arguments) override
	{
		BaseFunctionName = "flash";
		StartCode = 2;
		IsRequiredOnlyOneArg = false;

		GenericNumericalController(searchOn, total, PartitionManager::Display::UsingDispString->expected_flash_arg);

		if (PartitionManager::ControlArg(arguments[searchOn]))
			PartitionManager::Strings::TargetPartition = arguments[searchOn];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		if (PartitionManager::ControlArg(arguments[(searchOn + 1)]))
			PartitionManager::Strings::TargetFlashFile = arguments[(searchOn + 1)];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetFlashFile);
		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetPartition);
	}
};

class PartitionManagerFormat : public PartitionManagerBase {
public:
	void ArgumentProcessor(int& searchOn, int& total, char** &arguments) override
	{
		BaseFunctionName = "format";
		StartCode = 3;
		IsRequiredOnlyOneArg = false;

		GenericNumericalController(searchOn, total, PartitionManager::Display::UsingDispString->expected_format_arg);

		if (PartitionManager::ControlArg(arguments[searchOn]))
			PartitionManager::Strings::TargetPartition = arguments[searchOn];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		if (PartitionManager::ControlArg(arguments[(searchOn + 1)]))
			PartitionManager::Strings::TargetFormatFS = arguments[(searchOn + 1)];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetFormatFS);
		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetPartition);
	}
};

class PartitionManagerPartSize : public PartitionManagerBase {
public:
	void ArgumentProcessor(int& searchOn, int& total, char** &arguments) override
	{
		BaseFunctionName = "partition-size";
		StartCode = 4;
		IsRequiredOnlyOneArg = true;

		GenericNumericalController(searchOn, total, PartitionManager::Display::UsingDispString->expected_partsz_arg);

		if (PartitionManager::ControlArg(arguments[searchOn]))
			PartitionManager::Strings::TargetPartition = arguments[searchOn];
		else
			LOGE("%s.\n", PartitionManager::Display::UsingDispString->not_spec_opt);

		PartitionManager::CheckOptSymbol(PartitionManager::Strings::TargetPartition);
	}
};

/* Generate classes */
PartitionManagerBase* Base;
PartitionManagerBase BaseTemplate;
PartitionManagerBackup BackupArgProcessorBase;
PartitionManagerFlash FlashArgProcessorBase;
PartitionManagerFormat FormatArgProcessorBase;
PartitionManagerPartSize PartSizeArgProcessorBase;

namespace PartitionManager {

static void
ParseMainOperations(int argc, char** argv)
{
	SearchOnMainInt = -1;
	Base = &BaseTemplate;

	VLOGD("Starting cycle for trapping main options...\n");
	while (1) {
		if ((argc - 1) == 0) {
			VLOGD("argc - 1 = 0. Breaking...\n");
			break;
		}

		if (argv[(argc - 1)][0] == '-') {
			VLOGD("argv[%d] starts with '-'. Continue.\n", (argc - 1));
			argc--;
			continue;
		} else {
			Target = argv[(argc - 1)];
			SearchOnMainInt = argc;
			VLOGD("argv[%d] = %s\n", (argc - 1), argv[(argc - 1)]);
			VLOGD("Variable of \"Target\" (string): %s\n", Target.c_str());

			if (Target == "backup") {
				Base = &BackupArgProcessorBase;
				Config.BackupMode = true;
				break;
			} else if (Target == "flash") {
				Base = &FlashArgProcessorBase;
				Config.FlashMode = true;
				break;
			} else if (Target == "format") {
				Base = &FormatArgProcessorBase;
				Config.FormatMode = true;
				break;
			} else if (Target == "partition-size") {
				Base = &PartSizeArgProcessorBase;
				Config.PartSizeViewMode = true;
				break;
			} else if (Target == "start-parted") {
				Config.PartedMode = true;
				break;
			} else {
				Target = "";
				SearchOnMainInt = -1;
				argc--;
				continue;
			}
		}

		break;
	}
}

static char**
ParseStdin(int argc, char** argv)
{
	StdinArgcTotal = 0;
	char buf[256];

	VLOGD("Checking stdin status...\n");
	if (!isatty(fileno(stdin))) {
		VLOGD("stdin is not empty.\n");
		VLOGD("Parsing stdin arguments...\n");

		while (fgets(buf, sizeof(buf), stdin) != nullptr) {
			buf[strcspn(buf, "\n")] = 0;

			argv[argc] = strdup(buf);
			argc++;
			StdinArgcTotal++;
		}

		VLOGD("Parsing completed.\n");
	}

	VLOGD("stdin empty.\n");
	return argv;
}

static void
ParseOptions(int argc, char** argv)
{
	argc--;
	argv++;

	VLOGD("Parsing standart arguments...\n");
	while (argc && argv[0] != nullptr) {
		if (argv[0][0] != '-') {
			argc--;
			argv++;
			continue;
		}

		for (int x = 1; true; x++) {
			Option = argv[0];
			SomeSpec = true;

			switch (argv[0][x]) {
				case '-':
					if (Option == "--backup")
						deprecated('b',
							PartitionManager::Display::UsingDispString->depr_backup_opt,
							"backup");
					else if (Option == "--flash")
						deprecated('F',
							PartitionManager::Display::UsingDispString->depr_flash_opt,
							"flash");
					else if (Option == "--format")
						deprecated('r',
							PartitionManager::Display::UsingDispString->depr_format_opt,
							"format");
					else if (Option == "--license")
						deprecated('L',
							PartitionManager::Display::UsingDispString->depr_Vlicense_opt,
							"license");
					else if (Option == "--context")
						deprecated('c',
							PartitionManager::Display::UsingDispString->depr_ch_sp_opt,
							"context");
					else if (Option == "--logical") {
						VLOGD("Logical partition type specified.\n");
						LogicalSpeficy = true;
						break;
					} else if (Option == "--search-path") {
						VLOGD("Custom search path specified.\n");
						if (argc > 1)
							PrSpInput(argv[1]);
						else
							LOGE("--search-path: %s.\n%s `%s --help' %s.\n", \
							PartitionManager::Display::UsingDispString->is_requires_arg, \
							PartitionManager::Display::UsingDispString->try_h, \
							PartitionManager::Strings::ExecutingName.c_str(), \
							PartitionManager::Display::UsingDispString->for_more);
						break;
					} else if (Option == "--list") {
						VLOGD("It was requested to list the partitions.\n");
						ListRequired = true;
						if (ViewVersion || ViewHelp)
							MultipleViewers = true;
						break;
					} else if (Option == "--force") {
						VLOGD("Force mode speficed.\n");
						Config.ForceMode = true;
						break;
					} else if (Option == "--verbose") {
						VLOGD("Verbose mode speficed.\n");
						Config.VerboseMode = true;
						break;
					} else if (Option == "--silent") {
						VLOGD("Silent mode speficed.\n");
						Config.SilentEnabled = true;
						break;
					} else if (Option == "--set-language") {
						VLOGD("It was requested to adjust the language.\n");
						if (argc > 1) {
							VLOGE("Language inputs: getting inputs...\n");
							SetLanguageReq = true;
							SpeficedLanguagePr = argv[1];
						}
						else
							LOGE("--set-language: %s.\n%s `%s --help' %s.\n",
								PartitionManager::Display::UsingDispString->is_requires_arg,
								PartitionManager::Display::UsingDispString->try_h,
								PartitionManager::Strings::ExecutingName.c_str(),
								PartitionManager::Display::UsingDispString->for_more);
						break;
					} else if (Option == "--view-languages") {
						ListSupportedLanguages = true;
					} else if (Option == "--as-byte") {
						PartSizeArgSpeficed = true;
						PartitionManager::Integers::PartSizeViewType = VIEW_AS_BYTE;
						break;
					} else if (Option == "--as-kilobyte") {
						PartSizeArgSpeficed = true;
						PartitionManager::Integers::PartSizeViewType = VIEW_AS_KIB;
						break;
					} else if (Option == "--as-megabyte") {
						PartSizeArgSpeficed = true;
						PartitionManager::Integers::PartSizeViewType = VIEW_AS_MIB;
						break;
					} else if (Option == "--as-gigabyte") {
						PartSizeArgSpeficed = true;
						PartitionManager::Integers::PartSizeViewType = VIEW_AS_GIB;
						break;
					} else if (Option == "--only-size") {
						PartSizeArgSpeficed = true;
						Config.OnlyViewSize = true;
						break;
					} else if (Option == "--version") {
						VLOGD("The version info was requested to be displayed.\n");
						ViewVersion = true;
						if (ListRequired || ViewHelp)
							MultipleViewers = true;
						break;
					} else if (Option == "--help") {
						VLOGD("The help message was requested to be displayed.\n");
						ViewHelp = true;
						if (ViewVersion || ListRequired)
							MultipleViewers = true;
						break;
					} else {
						VLOGE("Unknown Option: %s\n", argv[0]);
						LOGE("%s: %s.\n%s `%s --help' %s.\n", argv[0],
							PartitionManager::Display::UsingDispString->unknw_arg,
							PartitionManager::Display::UsingDispString->try_h,
							PartitionManager::Strings::ExecutingName.c_str(),
							PartitionManager::Display::UsingDispString->for_more);
					}
					break;
				case 'b':
					deprecated('b',
						PartitionManager::Display::UsingDispString->depr_backup_opt,
						"backup");
					break;
				case 'F':
					deprecated('F',
						PartitionManager::Display::UsingDispString->depr_flash_opt,
						"flash");
					break;
				case 'r':
					deprecated('r',
						PartitionManager::Display::UsingDispString->depr_format_opt,
						"format");
					break;
				case 'L':
					deprecated('L',
						PartitionManager::Display::UsingDispString->depr_Vlicense_opt,
						"license");
					break;
				case 'D':
					deprecated('D',
						PartitionManager::Display::UsingDispString->depr_ch_list_opt);
					break;
				case 'c':
					deprecated('c',
						PartitionManager::Display::UsingDispString->depr_ch_sp_opt,
						"context");
				case 'l':
					VLOGD("Logical partition type specified.\n");
					LogicalSpeficy = true;
					continue;
				case 'P':
					VLOGD("Custom search path speficed.\n");
					if (argc > 1) {
						VLOGE("Search-path inputs: getting inputs...\n");
						PrSpInput(argv[1]);
						continue;
					} else
						LOGE("-P: %s.\n%s `%s --help' %s.\n",
							PartitionManager::Display::UsingDispString->is_requires_arg,
							PartitionManager::Display::UsingDispString->try_h,
							PartitionManager::Strings::ExecutingName.c_str(),
							PartitionManager::Display::UsingDispString->for_more);
					break;
				case 'p':
					VLOGD("It was requested to list the partitions.\n");
					ListRequired = true;
					if (ViewVersion || ViewHelp)
						MultipleViewers = true;
					continue;
				case 'f':
					VLOGD("Force mode speficed.\n");
					Config.ForceMode = true;
					continue;
				case 'V':
					VLOGD("Verbose mode speficed.\n");
					Config.VerboseMode = true;
					continue;
				case 's':
					VLOGD("Silent mode speficed.\n");
					Config.SilentEnabled = true;
					continue;
				case 'S':
					VLOGD("It was requested to adjust the language.\n");
					if (argc > 1) {
						VLOGE("Language inputs: getting inputs...\n");
						SetLanguageReq = true;
						SpeficedLanguagePr = argv[1];
						continue;
					} else
						LOGE("-S: %s.\n%s `%s --help' %s.\n",
							PartitionManager::Display::UsingDispString->is_requires_arg,
							PartitionManager::Display::UsingDispString->try_h,
							PartitionManager::Strings::ExecutingName.c_str(),
							PartitionManager::Display::UsingDispString->for_more);
				case 'v':
					VLOGD("The version info was requested to be displayed.\n");
					ViewVersion = true;
					if (ListRequired || ViewHelp)
						MultipleViewers = true;
					continue;
				case '\0':
					break;
				default:
					VLOGE("Unknown Option: -%c\n", argv[0][x]);
					LOGE("-%c: %s.\n%s `%s --help' %s.\n",
						argv[0][x],
						PartitionManager::Display::UsingDispString->unknw_arg,
						PartitionManager::Display::UsingDispString->try_h,
						PartitionManager::Strings::ExecutingName.c_str(),
						PartitionManager::Display::UsingDispString->for_more);
			}

			break;
		}

		argc--;
		argv++;
	}
}

static bool
GetDeviceFromArguments(int argc, char** argv)
{
	VLOGD("Checking arguments for finding device path...\n");

	if (argc <= 2) return false;
	if (argc < 3)  return false;

	if (strncmp(argv[2], "/dev", 4) != 0) return false;
	else PartitionManager::Strings::Device = argv[2];

	VLOGD("Device path founded in arguments.\n");
	return true;
}

} /* namespace PartitionManager */

int main(int argc, char** argv)
{
	PartitionManager::Strings::ExecutingName = basename(argv[0]);

	for (int i = 0; i <= (argc - 1); i++) {
		if (strncmp(argv[i], "-V", 2) == 0 || strcmp(argv[i], "--verbose") == 0)
			Config.VerboseMode = true;
		else
			continue;
	}

	VLOGD("Main function started. Setting up locale. Calling 'setlocale <clocale>'\n");
	setlocale(LC_ALL, "");

	char** args = PartitionManager::ParseStdin(argc, argv);
	argc = (argc + StdinArgcTotal);
	/* It's not gonna be okay even 0. */

	/* load language */
	VLOGD("Loading language... Calling LoadLanguage()...\n");
	if (!PartitionManager::LoadLanguage()) {
		cout << "LoadLanguage() process failed..!" << endl;
		cout << "Loading english language!!! (pmt-defaults)" << endl;
		PartitionManager::Display::UsingDispString = &PartitionManager::Display::LangEn;
		PartitionManager::Strings::CurrentLanguage = "en";
	}

	SymbolRule = PartitionManager::Display::UsingDispString->symbol_rule;
	int SearchResult = 3;

	PartitionManager::ParseOptions(argc, argv);
	PartitionManager::ParseMainOperations(argc, argv);

	if (Config.SilentEnabled && Config.VerboseMode) {
		VLOGE("Silent and verbose mode is one-way.\n");
		cout << PartitionManager::Strings::ExecutingName << ": " << PartitionManager::Display::UsingDispString->s_and_v << endl;
		exit(1);
	}

	VLOGD("Checking last language switch status...\n");
	if (PartitionManager::CleanSWPoint()) {
		VLOGD("Last transactions found that language was changed between.\n");

		if (PartitionManager::Display::UsingDispString->welcome_ != nullptr)
			LOGD("%s", PartitionManager::Display::UsingDispString->welcome_);

		LOGD("%s %s %s %s.\n",
			PartitionManager::Display::UsingDispString->language,
			PartitionManager::Display::UsingDispString->welcome,
			PartitionManager::Display::UsingDispString->by_str,
			PartitionManager::Display::UsingDispString->lang_by_s);
	}

	/* check argument total */
	VLOGD("argc (arguments) total: %d.\n", argc);
	if (argc < 2)
		LOGE("%s.\n%s '%s --help' %s.\n",
			PartitionManager::Display::UsingDispString->missing_operand,
			PartitionManager::Display::UsingDispString->try_h,
			PartitionManager::Strings::ExecutingName.c_str(),
			PartitionManager::Display::UsingDispString->for_more);

	/* stop the program if multiple viewer is used */
	if (MultipleViewers) {
		VLOGE("Multiple viewer option selected!\n");
		LOGE("%s\n", PartitionManager::Display::UsingDispString->multiple_wiewers);
	}

	if (!Config.PartSizeViewMode && PartSizeArgSpeficed) {
		VLOGE("Related flags were detected, although some partition size was not requested.\n");
		LOGE("%s.\n", PartitionManager::Display::UsingDispString->only_partsz_args);
	}

	if (ListSupportedLanguages) {
		DisplaySupportedLanguages();
		return 0;
	}

	/* controller to handle viewer */
	if (ViewHelp) {
		VLOGD("The help message was asked to display. It's displayed... Calling DisplayHelp()\n");
		PartitionManager::DisplayHelp();
		return 0;
	} else if (ViewVersion) {
		VLOGD("The version info message was asked to display. It's displayed... Calling DisplayVersion()\n");
		PartitionManager::DisplayVersion();
		return 0;
	} else if (ListRequired) {
		VLOGD("Partitions were asked to be listed. It's listed... Calling CheckRoot() (root check is required), CheckDevPoint() (for generating warnings etc.) and ListPartitions()\n");
		PartitionManager::CheckRoot();
		VLOGD("CheckRoot() completed.\n");
		PartitionManager::CheckDevPoint();
		VLOGD("CheckDevPoint() completed.\n");
		return PartitionManager::ListPartitions();
	}

	if (SetLanguageReq) {
		VLOGD("The language was asked to adjust. Calling SetLanguage()...\n");
		LOGD("%s: %s\n",
			PartitionManager::Strings::ExecutingName.c_str(),
			PartitionManager::Display::UsingDispString->switching_lang);
		PartitionManager::SetLanguage(SpeficedLanguagePr, 0);

		sleep(2);

		VLOGD("SetLanguage() completed.\n");
		LOGD("%s: %s.\n",
			PartitionManager::Strings::ExecutingName.c_str(),
			PartitionManager::Display::UsingDispString->please_rerun);

		return 0;
	}

	if (Target.empty()) {
		VLOGE("There's no job to do.\n");
		LOGD("%s: %s.\n",
			PartitionManager::Strings::ExecutingName.c_str(),
			PartitionManager::Display::UsingDispString->missing_operand);

		if (SomeSpec)
			LOGD("%s.\n", PartitionManager::Display::UsingDispString->some_spec);

		LOGD("%s '%s --help' %s.\n",
			PartitionManager::Display::UsingDispString->try_h,
			PartitionManager::Strings::ExecutingName.c_str(),
			PartitionManager::Display::UsingDispString->for_more);

		exit(1);
	}

	if (Config.PartedMode) {
		VLOGD("Checking root status... Calling CheckRoot()...\n");
		PartitionManager::CheckRoot();

		VLOGD("Parted terminal open requested.\n");

		if (!PartitionManager::GetDeviceFromArguments(argc, argv)) {
			LOGW("%s...\n", PartitionManager::Display::UsingDispString->not_spec_device_on_args);
			VLOGD("Device path not found in arguments. Searching default devices...\n");

			if (!PartitionManager::SearchDefaultDevices())
				LOGE("%s.\n", PartitionManager::Display::UsingDispString->cannot_find_any_defdevice);
		} else {
			if (!PartitionManager::SearchDevice(PartitionManager::Strings::Device))
				LOGE("'%s': %s: %s\n",
					PartitionManager::Strings::Device.c_str(),
					PartitionManager::Display::UsingDispString->cannot_find_device,
					strqerror());
		}

		int ret = PartitionManager::StartParted();
		LOGD("%s: %d.\n",
			PartitionManager::Display::UsingDispString->exited_with,
			ret);

		return ret;
	}

	Base->ArgumentProcessor(SearchOnMainInt, argc, args);

	if (Config.FormatMode) {
		VLOGD("File system name specified for formatting is being contaminated...\n");
		if (PartitionManager::Strings::TargetFormatFS != "ext4" \
		&& PartitionManager::Strings::TargetFormatFS != "ext3" \
		&& PartitionManager::Strings::TargetFormatFS != "ext2") {
			VLOGE("Unsupported file system: %s.\n", PartitionManager::Strings::TargetFormatFS.c_str());
			LOGE("%s: %s\n",
				PartitionManager::Display::UsingDispString->unsupported_fs,
				PartitionManager::Strings::TargetFormatFS.c_str());
		}
	}

	/* checks */
	VLOGD("Checking root status... Calling CheckRoot()...\n");
	PartitionManager::CheckRoot();
	VLOGD("Checking A/B and logical device status... Calling CheckDevPoint()...\n");
	PartitionManager::CheckDevPoint();

	if (LogicalSpeficy) {
		VLOGD("Logical partition type speficed. Checking partition statust's...\n");
		if (Config.UsesLogical)
			Config.UseLogical = true;
		else
			LOGE("%s\n", PartitionManager::Display::UsingDispString->not_logical);
	}

	if (Config.FlashMode) {
		VLOGD("The status of the specified file for flashing is being checked...\n");
		SearchResult = PartitionManager::GetState(PartitionManager::Strings::TargetFlashFile);

		if (SearchResult == 1)
			LOGE("%s: `%s': %s\n",
				PartitionManager::Display::UsingDispString->cannot_stat,
				PartitionManager::Strings::TargetFlashFile.c_str(),
				strqerror());
		else if (SearchResult == -1)
			LOGE("`%s': %s\n",
				PartitionManager::Strings::TargetFlashFile.c_str(),
				PartitionManager::Display::UsingDispString->not_file);
	}

	/* custom search path checker */
	if (Config.UseCustomSearchPath) {
		VLOGD("The status of the \"dev\" is controlled in the specified custom /dev search path...\n");
		if (strncmp(PartitionManager::Strings::CustomSearchPath.c_str(), "/dev", 4) != 0) {
			if (!Config.ForceMode)
				LOGE("%s\n", PartitionManager::Display::UsingDispString->not_in_dev);
		}

		VLOGD("The specified custom /dev search path is being put in countless...\n");
		SearchResult = PartitionManager::GetState(PartitionManager::Strings::CustomSearchPath, "dir");

		if (SearchResult == 1)
			LOGE("%s: `%s': %s\n",
				PartitionManager::Display::UsingDispString->cannot_stat,
				PartitionManager::Strings::CustomSearchPath.c_str(),
				strqerror());
		else if (SearchResult == -1)
			LOGE("`%s': %s\n",
				PartitionManager::Strings::CustomSearchPath.c_str(),
				PartitionManager::Display::UsingDispString->not_dir);
	}

	VLOGD("The partition specification status is controlled...\n");
	if (PartitionManager::Strings::TargetPartition.empty()) {
		if (!Config.ForceMode)
			LOGE("%s\n%s `%s --help' %s\n",
				PartitionManager::Display::UsingDispString->req_part_name,
				PartitionManager::Display::UsingDispString->try_h,
				PartitionManager::Strings::ExecutingName.c_str(),
				PartitionManager::Display::UsingDispString->for_more);
	} else {
		VLOGD("The call of main operations is being checked in case of the call...\n");
		if (!Target.empty())
			Base->CallTargetBaseFunction();
	}
}

/* end of code */
