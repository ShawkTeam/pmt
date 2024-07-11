/* By YZBruh | ShawkTeam */

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

#if defined(__cplusplus)
extern "C" {
#endif

#define INC_MAIN_LIBS

#include <pmt.h>

struct pmt_langdb_general en = {
    .lang_by_s = "YZBruh & r0manas",
    .language = "English",
    .lang_prefix = "en",
    .not_logical = "This device does not have logical partitions!",
    .not_file = "is not a file.",
    .not_dir = "is not a directory.",
    .not_in_dev = "Nothing found in /dev. Use force mode to avoid this error.",
    .not_open = "Couldn't open",
    .not_block = "The specified partition is not recognized as a block device.",
    .not_read = "Couldn't read",
    .not_write = "Couldn't write",
    .not_gen = "Couldn't generate",
    .no_root = "Root access could not be detected! Please run this with root permissions.",
    .no_target = "No target specified (backup, flash, or format).",
    .expected_backup_arg = "Expected backup argument 2 (1 of them are not mandatory), retrieved",
    .expected_flash_arg = "Expected flash argument 2, retrieved",
    .expected_format_arg = "Expected format argument 2, retrieved",
    .missing_operand = "Missing operand",
    .multiple_wiewers = "Multiple viewers can't be used on the same line.",
    .common_symbol_rule = "When specifying arguments for an option, ensure they do not begin with '-'. Each argument must correspond correctly to its respective option.",
    .req_part_name = "Partition name required.",
    .part_not_found = "Partition not found!",
    .unsupported_fs = "Formatter: unsupported filesystem",
    .cannot_stat = "Can't retrieve file status",
    .ffile_more_part = "Flash file size exceeds partition capacity.",
    .cannot_get_bsz = "Failed to retrieve partition block size.",
    .format_fail = "Formatting failed! There is a possibility of data damage.",
    .logical_warn = "This device uses logical partitions.",
    .ab_warn = "This device uses A/B partition style.",
    .out_not_spec = "Output file name not specified. Using default name:",
    .please_rerun = "Please rerun the command.",
    .part_disk_sz = "Partition disk size",
    .flash_file_sz = "Flash file size",
    .part_disk_sz_fail = "Failed to retrieve partition disk size.",
    .flash_file_sz_fail = "Failed to retrieve flash file size.",
    .list_of_dir = "Directory listing",
    .see_license = "View licenses using the -L argument.",
    .success_backup = "Backup successful. Output:",
    .success_flash = "Flash successful.",
    .warn = "WARNING",
    .fatal = "FATAL ERROR",
    .switching_lang = "Switching language...",
    .welcome = "language!",
    .welcome_ = "Welcome to ",
    .for_more = "for more information",
    .try_h = "Try",
    .usage_head = "Usage",
    .compiler_str = "Compiler",
    .version_str = "version",
    .bin_str = "binary",
    .unknw_str = "unknown",
    .by_str = "By"
};

struct pmt_langdb_general tr = {
    .lang_by_s = "YZBruh",
    .language = "Türkçe",
    .lang_prefix = "tr",
    .not_logical = "Bu cihaz mantıksal (logical) bölümlere sahip değil!",
    .not_file = "Bu bir dosya değil",
    .not_dir = "Bu bir dizin değil",
    .not_in_dev = "Bu bir şakamı? Bunun /dev dizini ile bi r ilgisi yok (içermiyor). Bu hatayla karşılaşmak istemiyorsanız zorlama (force) modu kullanın.",
    .not_open = "Açılamıyor",
    .not_block = "Belirtilen bölüm bir blok değil. Yani aslında bu bir bölüm bile değil (disk). Bu hatayı almak için şanslı olmak gerek..!",
    .not_read = "Veri okunamıyor",
    .not_write = "Veri yazılamıyor",
    .not_gen = "Oluşturulamıyor",
    .no_root = "Root erişimi tespit edilemedi! Lütfen root erişimi ile çalıştırın.",
    .no_target = "Hedef işlem yok (yedek, flaş veya format).",
    .expected_backup_arg = "Beklenen yedekleme argümanı 2 (bir tanesi zorunlu değil), alınan",
    .expected_flash_arg = "Beklenen flaş argümanı 2, alınan",
    .expected_format_arg = "Beklenen format argümanı 2, alınan",
    .missing_operand = "işlem belirtilmedi",
    .multiple_wiewers = "Birden fazla görüntüleme işlemi yapan fonksiyonlar bir arada kullanılamaz. Aynı anda sadece bir tanesi kullanılabilir.",
    .common_symbol_rule = "Bir seçeneğin argümanını verirken argüman önüne '-' sembolü getirilemez. Sembolü kaldırın ve tekrar deneyin.",
    .req_part_name = "Bölüm adı gereklidir.",
    .part_not_found = "Bölüm bulunamadı!",
    .unsupported_fs = "Formatlayıcı: desteklenmeyen dosya sistemi:",
    .cannot_stat = "Durumu tespit edilemedi",
    .ffile_more_part = "Flaşlanacak dosyanın boyutu mevcut bölüm boyutundan fazla.",
    .cannot_get_bsz = "Bölüm blok boyutu tespit edilemedi!",
    .format_fail = "Formatlama başarısız oldu. Bazı şeyler zarar görmüş olabilir!",
    .logical_warn = "Uyarı: bu cihaz mantıksal (logical) bölümlere sahip.",
    .ab_warn = "Uyarı: bu cihazın bazı bölümleri A/B kullanıyor.",
    .out_not_spec = "Uyarı: çıktı dosya belirtilmedi. Çıktı dosya adı bölüm adına göre belirlenecek.",
    .please_rerun = "Lütfen yeniden çalıştırın",
    .part_disk_sz = "Bölümün disk boyutu",
    .flash_file_sz = "Flaşlanacak dosyanın boyutu",
    .flash_file_sz_fail = "Uyarı: flaşlanacak dosyanın boyutu tespit edilemedi.",
    .part_disk_sz_fail = "Uyarı: bölüm boyutunun boyutu tespit edilemedi.",
    .list_of_dir = "Dizin içeriğinin listesi",
    .see_license = "Lisansı -L seçeneği ile görüntüleyebilirsiniz.",
    .success_backup = "Başarılı. Çıktı",
    .success_flash = "Başarılı.",
    .warn = "UYARI",
    .fatal = "KRİTİK HATA",
    .switching_lang = "Dil değiştiriliyor...",
    .welcome = "diline hoş geldiniz!",
    .welcome_ = NULL,
    .for_more = "komutunu kullanabilirsiniz",
    .try_h = "Daha fazla bilgi",
    .usage_head = "Kullanımı",
    .compiler_str = "Derleyici",
    .version_str = "versiyon",
    .bin_str = "yapı",
    .unknw_str = "bilinmeyen",
    .by_str = "Çeviriyi yapan(lar):"
};

struct pmt_langdb_docs en_docs = {
    .docs_strs_l1 = "[OPTIONS] backup PARTITION [OUTPUT] [OPTIONS]...",
    .docs_strs_l2 = "[OPTIONS] flash FILE PARTITION [OPTIONS]...",
    .docs_strs_l3 = "[OPTIONS] format FILE_SYSTEM[ext/2/3/4] PARTITION [OPTIONS]...",
    .docs_strs_l4 = "Options",
    .docs_strs_l5 = "It is meant to determine whether the target partition is logical.",
    .docs_strs_l6 = "It is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name).",
    .docs_strs_l7 = "List partitions.",
    .docs_strs_l8 = "Information and warning messages are silenced in normal work.",
    .docs_strs_l9 = "Force mode. Some things are ignored.",
    .docs_strs_l10 = "Set current language.",
    .docs_strs_l11 = "See version.",
    .docs_strs_l12 = "See this help message.",
    .docs_strs_l13 = "See license.",
    .docs_strs_l14 = "Examples",
    .docs_strs_l15 = "Report bugs to",
    .or_str = "or",
    .usage_docstr = "Usage"
};

struct pmt_langdb_docs tr_docs = {
    .docs_strs_l1 = "[SEÇENEKLER] backup BÖLÜM [ÇIKTI] [SEÇENEKLER]...",
    .docs_strs_l2 = "[SEÇENEKLER] flash DOSYA BÖLÜM [SEÇENEKLER]...",
    .docs_strs_l3 = "[SEÇENEKLER] format DOSYA_SİSTEMİ[ext/2/3/4] BÖLÜM [SEÇENEKLER]...",
    .docs_strs_l4 = "Seçenekler",
    .docs_strs_l5 = "Bu seçeneği kullanarak mantıksal (logical) bir bölümle işlem yapılacağını belirtebilirsiniz.",
    .docs_strs_l6 = "Bu seçeneği kullanarak özel /dev bağlamı belirtebilirsiniz. Sadece normal (mantıksal olmayan) bölümler içindir (Varsayılan: /dev/block/by-name).",
    .docs_strs_l7 = "Bölümler listelenir.",
    .docs_strs_l8 = "Bilgi ve uyarı mesajları susturulur.",
    .docs_strs_l9 = "Zorlama modu. Bazı şeyler göz ardı edilir.",
    .docs_strs_l10 = "Mevcut dili ayarlayın.",
    .docs_strs_l11 = "Sürümü görüntüleyin.",
    .docs_strs_l12 = "Bu yardım mesajını görüntüleyin.",
    .docs_strs_l13 = "Lisansı gorüntüleyin.",
    .docs_strs_l14 = "Örnekler",
    .docs_strs_l15 = "Sorunları şu adrese bildirin:",
    .or_str = "yada",
    .usage_docstr = "Kullanımı"
};

char* pmt_langdb_langs[] = {
    "en",
    "tr"
};

int pmt_langdb_total = 2;
int pmt_langdb_ctrl = 1;

#if defined(__cplusplus)
}
#endif

/* end of code */
