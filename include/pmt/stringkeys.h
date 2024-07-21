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

#ifndef __PMT_STRINGKEYS_
#define __PMT_STRINGKEYS_

__BEGIN_DECLS

/* The struct is a very good option for setting the languages of texts etc. */
struct pmt_langdb_general {
    const char* _Nonnull lang_by_s;
    const char* _Nonnull language;
    const char* _Nonnull lang_prefix;
    const char* _Nonnull not_logical;
    const char* _Nonnull not_file;
    const char* _Nonnull not_dir;
    const char* _Nonnull not_in_dev;
    const char* _Nonnull not_open;
    const char* _Nonnull not_block;
    const char* _Nonnull not_read;
    const char* _Nonnull not_readdir;
    const char* _Nonnull not_write;
    const char* _Nonnull not_gen;
    const char* _Nonnull no_root;
    const char* _Nonnull no_target;
    const char* _Nonnull expected_backup_arg;
    const char* _Nonnull expected_flash_arg;
    const char* _Nonnull expected_format_arg;
    const char* _Nonnull missing_operand;
    const char* _Nonnull multiple_wiewers;
    const char* _Nonnull common_symbol_rule;
    const char* _Nonnull req_part_name;
    const char* _Nonnull part_not_found;
    const char* _Nonnull unsupported_fs;
    const char* _Nonnull cannot_stat;
    const char* _Nonnull ffile_more_part;
    const char* _Nonnull cannot_get_bsz;
    const char* _Nonnull format_fail;
    const char* _Nonnull depr_backup_opt;
    const char* _Nonnull depr_flash_opt;
    const char* _Nonnull depr_format_opt;
    const char* _Nonnull depr_Vlicense_opt;
    const char* _Nonnull depr_ch_list_opt;
    const char* _Nonnull not_spec_opt;
    const char* _Nonnull logical_warn;
    const char* _Nonnull ab_warn;
    const char* _Nonnull out_not_spec;
    const char* _Nonnull please_rerun;
    const char* _Nonnull part_disk_sz;
    const char* _Nonnull flash_file_sz;
    const char* _Nonnull part_disk_sz_fail;
    const char* _Nonnull flash_file_sz_fail;
    const char* _Nonnull unknown_opr;
    const char* _Nonnull list_of_dir;
    const char* _Nonnull success_backup;
    const char* _Nonnull success_flash;
    const char* _Nonnull warn;
    const char* _Nonnull fatal;
    const char* _Nonnull switching_lang;
    const char* _Nonnull welcome;
    const char* _Nullable welcome_;
    const char* _Nonnull for_more;
    const char* _Nonnull try_h;
    const char* _Nonnull usage_head;
    const char* _Nonnull depr_opt_str;
    const char* _Nonnull switched_opt_str;
    const char* _Nonnull not_changed_opt;
    const char* _Nonnull compiler_str;
    const char* _Nonnull version_str;
    const char* _Nonnull bin_str;
    const char* _Nonnull unknw_str;
    const char* _Nonnull by_str;
};

/* docs etc. */
struct pmt_langdb_docs {
    const char* _Nonnull docs_strs_l1;
    const char* _Nonnull docs_strs_l2;
    const char* _Nonnull docs_strs_l3;
    const char* _Nonnull docs_strs_l4;
    const char* _Nonnull docs_strs_l5;
    const char* _Nonnull docs_strs_l6;
    const char* _Nonnull docs_strs_l7;
    const char* _Nonnull docs_strs_l8;
    const char* _Nonnull docs_strs_l9;
    const char* _Nonnull docs_strs_l10;
    const char* _Nonnull docs_strs_l11;
    const char* _Nonnull docs_strs_l12;
    const char* _Nonnull docs_strs_l13;
    const char* _Nonnull docs_strs_l14;
    const char* _Nonnull or_str;
    const char* _Nonnull usage_docstr;
};

/* for checks etc */
struct pmt_langdb_langs {
    const char* _Nullable lang_pr;
};

__END_DECLS

#endif /* __PMT_STRINGKEYS_ */

/* end of code */
