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

#include <sys/cdefs.h>

__BEGIN_DECLS

#ifndef __PMT_H_
#define __PMT_H_

#define PMT_PACKAGE_NAME "Partition Manager"

#ifdef INC_MAIN_LIBS
  #include <stdio.h>
  #include <stdbool.h>
  #include <unistd.h>
  #include <fcntl.h>
  #include <stdlib.h>
  #include <stdarg.h>
  #include <string.h>
#endif

#ifdef INC_GETOPT
  #include <getopt.h>
#endif

#ifdef INC_DIRENT
  #include <dirent.h>
#endif

#ifdef INC_STAT
  #include <sys/stat.h>
#endif

#ifdef INC_DEBUGERS
  #include <errno.h>
#endif

#ifdef INC_TOOLS_REQS
  #include <fcntl.h>
  #include <sys/statvfs.h>
#endif

/* variable definations */
extern char* _Nullable out;
extern char* _Nullable cust_cxt;
extern char* _Nullable target_partition;
extern char* _Nullable target_flash_file;
extern char* _Nullable format_fs;
extern char* _Nullable partition_type;
extern char* _Nullable bin_name;
extern bool pmt_use_logical;
extern bool pmt_use_cust_cxt;
extern bool pmt_ab;
extern bool pmt_logical;
extern bool pmt_silent;
extern bool pmt_flash;
extern bool pmt_backup;
extern bool pmt_format;
extern bool pmt_force_mode;
extern bool pmt_inst_on_termux;

/* language struces configurations */
extern struct pmt_langdb_general* _Nullable current;
extern struct pmt_langdb_docs* _Nullable curr_docs;
extern struct pmt_langdb_general en;
extern struct pmt_langdb_general tr;
extern struct pmt_langdb_docs en_docs;
extern struct pmt_langdb_docs tr_docs;

/* logging levels */
typedef enum {
    LOG_LEVEL_FATAL,
    LOG_LEVEL_ERR,
    LOG_LEVEL_WARN,
    LOG_LEVEL_DEBUG
} LogLevel;

/* function definations */
int listpart(void);
void check_dev_point(void);
void check_root(void);
int pmt(unsigned short progress_code);
void version(void);
void setlang(const char* _Nonnull lang, int null_conf_stat);
int search_sls(void);
int loadlang(void);
int get_stat(const char* _Nonnull filepath, const char* _Nonnull stype);
void debug(LogLevel status, const char* _Nullable fmt, ...);

/* logging macros */
#define LOGF(fmt, ...) debug(LOG_LEVEL_FATAL, fmt, ##__VA_ARGS__)
#define LOGE(fmt, ...) debug(LOG_LEVEL_ERR, fmt, ##__VA_ARGS__)
#define LOGW(fmt, ...) debug(LOG_LEVEL_WARN, fmt, ##__VA_ARGS__)
#define LOGD(fmt, ...) debug(LOG_LEVEL_DEBUG, fmt, ##__VA_ARGS__)

#endif

__END_DECLS

/* end of code */
