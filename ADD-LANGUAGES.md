### Add a new language to pmt (guide)

On this page, I will tell you how to add languages to pmt. This is not a difficult thing :)

##### Send ready stuff
 - Send ready translations via pull requests. After making the necessary checks, if there is no problem, I will accept it.
 - Proper commit messages are required.
 - If there is an error, I will mention it in the pull request comments.
 - Once you accept it, I (YZBruh) will implement the rest of the necessary things.
 - It may take 5 days for me to notice :P

##### Little important notes
 - You don't have to be a professional to do this thing.
 - There will be only one place you need to pay attention to, I will explain it.
 - There is no need to know C/C++.
 - You can edit existing translations.
 - You may need ready pmt to understand some things.
 - If you are on an x86 PC, you can compile and use it, but the functions will never work.

##### Understanding general logic
 All the texts (strings) in pmt are like variables in bash. I mean:

 ```
 Bash
     export missing_operand="missing operand."

     APPLYING:
          ~ $ echo -n "$missing_operand\n" # for more detail I used the -n argument
          missing operand
          ~ $ 

 C / C++
     const char* _Nonnull missing_operand = "missing operand.";
     const std::string missing_operand = "missing operand.";

     APPLYING (C / C++):
          printf("%s\n", missing_operand); // Move to new line with '\n' character
          std::cout << missing_operand << std::endl; // Move to new line with std::endl
 ```

 For example, let's take the output directly in pmt without any arguments and process the variables and structures behind the work.

 ```
 Shell
      ~ $ pmt
      pmt: missing operand
      Try `pmt --help' for more information.
      ~ $

 Code pieces (C++)
      struct pmt_langdb_general en = {
          // other translations
          .missing_operand = "missing operand",
          .try_h = "Try",
          .for_more = "for more information",
          // other translations
      }

      // pmt code functions [ logging ]
      LOGE("%s\n%s `%s --help' %s.\n, missing_operand, try_h, args[0], for_more); // LOGE is error logger (pmt). args[0] = execution name
 ```

In short, there are variables for texts. And I made these dynamic by using [struct](https://chatgpt.com/share/a798b57c-7e29-4b17-8887-f230414e57bd) method in C (but C++ is being used. And, it didn't change much about that). You just need to add translation :)

##### Translating main program texts (relevant part)

 - Let's open our jni/Languages.cpp source file.
 - Now, let's create the translation with the ready-made struct structure (see include/pmt/StringKeys.h for the structure).
 ```
 // Main
 struct langdb_general Lang<LANGUAGE_PREFIX> = { // LANGUAGE_PREFIX must be the corresponding abbreviation of the language in English. For example, it's like En in English.
      // translations
 }

 // Example
 struct langdb_general LangEn = {
      // translation
 }
 ```
 - We need to add some information about the language.
 ```
 VERY IMPORTANT NOTE: You should do your translations from within the function called WCHAR_T!
 
 struct langdb_general Lang<LANGUAGE_PREFIX> = {
      .lang_by_s = // Names of those who made the translation. It's up to you. Do you use & between more than one person?
      .language = // Language name. For example English
      .lang_prefix = // Language prefix. For example en
      // other translations
 }

 // Example
 struct langdb_general LangEn = {
      .lang_by_s = WCHAR_T("YZBruh & r0manas"),
      .language = WCHAR_T("English"),
      .lang_prefix = WCHAR_T("en"),
      // other translations
      .by_str = WCHAR_T("By") // Example for end translate
 }

 // CRITIC WARNING: Do not add ',' to the end of the last translation text. But others always...
 ```
 - Now do the others :)
 - Now let me explain the documentation...

##### Document texts translation (relevant part)

 - Let's open our jni/Languages.cpp source file.
 - Now, let's create the translation with the ready-made struct structure (see include/pmt/StringKeys.h for the structure).
 ```
 struct langdb_docs LangDoc<LANGUAGE_PREFIX> = {
      // translations
 }

 // Example
 struct pmt_langdb_docs LangDocEn = {
      // translations
 }

 // CRITIC WARNING: Do not add ',' to the end of the last translation text. But others always...
 ```
 - Make translations by taking examples from existing ones. And definitely do it regularly by getting help message from pmt :D

##### General things to do in translation

 - Open jni/LanguageTools.cpp
```
string supp_langs[] = {
    "en",
    "tr",
    // language prefix. "<LANGUAGE_PREFIX>",
    "" // PLEASE DO NOT ADD IT UNDER `""`!
};

// Example
string supp_langs[] = {
    "en",
    "tr",
    "az",
    ""
};

// Add the language you are translating into these existing language prefixes. I will fix the errors here (if there is an error)
```

##### Notes
 - Apologies for the crappy current language control structure :(
 - You can ask your questions: <t.me / ShawkTeam | Topics | pmt>
