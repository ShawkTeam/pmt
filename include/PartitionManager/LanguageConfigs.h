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

#pragma once

namespace PartitionManager {
	// Config base
	struct LanguageConfigs {
		string Name; // name of language. e.g.: "en"
		string ExName;
		struct langdb_general* LanguageStructure; // structure of language
		struct langdb_docs* LanguageDocStructure; // structure of language (for docs)
	};

	// Used config by pmt
	struct LanguageConfigs LanguageConfig[] {
		{"en", "English", &Display::LangEn, &Display::LangDocEn},
		{"tr", "Türkçe", &Display::LangTr, &Display::LangDocTr}
	};

	// Default
	struct langdb_general* Display::UsingDispString = nullptr;
}

/* end of code */