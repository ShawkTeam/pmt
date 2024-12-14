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

#pragma once

/* annotated macros */
#define DeprecatedOption   1
#define ChangedOption      2
#define EndDeprcationPoint 0
#define NotChanged         0
#define NotChangedLong     nullptr

/* versions */
#define v150     "1.5.0"
#define v160     "1.6.0"
#define v170     "1.7.0"
#define v180     "1.8.0"
#define v190     "1.9.0"
#define v200     "2.0.0"
#define v210     "2.1.0"
#define v220     "2.2.0"
#define v230     "2.3.0"
#define v240     "2.4.0"
#define v250     "2.5.0"
#define v260     "2.6.0"
#define v270     "2.7.0"
#define v280     "2.8.0"
#define v290     "2.9.0"
#define v291     "2.9.1"
#define v296     "2.9.6"
#define vUNKNOWN nullptr

struct DeprecationVarTab {
    const int DeprecationType;
    const int Option;
    const int Option_new;
    const char* Option_long;
    const char* Option_long_new;
    const char* DeprecatedOnVersion;
};

static struct DeprecationVarTab DeprecationTable[] = {
    {DeprecatedOption, 'b', NotChanged, "backup", NotChangedLong, v210},
    {DeprecatedOption, 'F', NotChanged, "flash", NotChangedLong, v210},
    {DeprecatedOption, 'r', NotChanged, "format", NotChangedLong, v210},
    {DeprecatedOption, 'L', NotChanged, "license", NotChangedLong, v250},
    {ChangedOption, 'D', 'p', "list", NotChangedLong, v210},
    {ChangedOption, 'c', 'P', "context", "search-path", v290},
    {EndDeprcationPoint, NotChanged, NotChanged, NotChangedLong, NotChanged, vUNKNOWN}
};

static void
__process_deprecated_opts(int Opt, const string& OptionLong, const char* DeprecationMsg)
{
    string LongErrMsg = (OptionLong.empty()) ? PartitionManager::Display::UsingDispString->not_changed_opt : OptionLong;

    for (int optctrl = 0; DeprecationTable[optctrl].DeprecationType != 0; optctrl++)
    {

        if (DeprecationTable[optctrl].DeprecationType == 1)
        {
            if (Opt == DeprecationTable[optctrl].Option || strcmp(OptionLong.c_str(), DeprecationTable[optctrl].Option_long) == 0)
                LOGD("%s [%s]: -%c (%s): %s\n", 
                    PartitionManager::Display::UsingDispString->depr_opt_str,
                    DeprecationTable[optctrl].DeprecatedOnVersion,
                    (char)DeprecationTable[optctrl].Option,
                    DeprecationTable[optctrl].Option_long,
                    DeprecationMsg); exit(1);
        }
        else if (DeprecationTable[optctrl].DeprecationType == 2)
        {
            if (Opt == DeprecationTable[optctrl].Option || strcmp(OptionLong.c_str(), DeprecationTable[optctrl].Option_long) == 0)
                LOGD("%s [%s]: -%c (%s): %s\n",
                    PartitionManager::Display::UsingDispString->switched_opt_str,
                    DeprecationTable[optctrl].DeprecatedOnVersion,
                    (char)DeprecationTable[optctrl].Option,
                    LongErrMsg.c_str(),
                    DeprecationMsg); exit(1);
        }

    }
}

#define DEPR_HANDLE __process_deprecated_opts

/* end of code */
