# By YZBruh

# Copyright 2024 Partition Manager
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#	 http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

########
# 3.0.2
########

LOCAL_PATH := $(call my-dir)

include $(LOCAL_PATH)/../build/config/env.mk

PMT_CXXFLAGS = \
	-O3 \
	-Wall \
	-Wextra \
	-Wno-vla-cxx-extension \
	-Wno-nullability-completeness \
	-Wno-writable-strings \
	-Wno-nullability-extension \
	-Wno-reorder-init-list \
	-Wno-gnu-zero-variadic-macro-arguments \
	-static \
	$(PMT_EXTRA_CXXFLAGS)
E2FSPROGS_DEFAULT_CFLAGS = \
	-Werror \
	-Wno-pointer-arith \
	-Wno-sign-compare \
	-Wno-type-limits \
	-Wno-typedef-redefinition \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument
PARTED_DEFAULTS_CFLAGS = \
	-Wno-pointer-sign \
	-Wno-sign-compare \
	-Wno-gnu-designator \
	-Wno-unused-variable \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument \
	-Wno-missing-field-initializers \
	-Wno-single-bit-bitfield-constant-conversion

ifneq ($(PMT_ENABLE_DEBUG),)
	PMT_CXXFLAGS += -gdwarf-5 -fsanitize=address
endif

PMT := PartitionManager
PARTED := parted
MKE2FS := e2fsprogs/mke2fs
LIB := e2fsprogs/lib
LIBEXT2FS := $(LIB)/ext2fs
LIBEXT2_UUID := $(LIB)/uuid
LIBEXT2_E2P := $(LIB)/e2p
LIBEXT2_QUOTA := $(LIB)/support
LIBEXT2_MISC := $(LIB)/misc
LIBEXT2_COM_ERR := $(LIB)/et
LIBEXT2_BLKID := $(LIB)/blkid
INC_DIR := $(LOCAL_PATH)/../include/e2fsprogs
E2FSPROGS_INCLUDES := \
	$(INC_DIR)/misc \
	$(INC_DIR)/blkid \
	$(INC_DIR)/e2p \
	$(INC_DIR)/et \
	$(INC_DIR)/ext2fs \
	$(INC_DIR)/ss \
	$(INC_DIR)/support \
	$(INC_DIR)/uuid \
	$(INC_DIR)/e2fsck \
	$(INC_DIR)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2fs
LOCAL_SRC_FILES := \
	$(LIBEXT2FS)/ext2_err.c \
	$(LIBEXT2FS)/alloc.c \
	$(LIBEXT2FS)/alloc_sb.c \
	$(LIBEXT2FS)/alloc_stats.c \
	$(LIBEXT2FS)/alloc_tables.c \
	$(LIBEXT2FS)/atexit.c \
	$(LIBEXT2FS)/badblocks.c \
	$(LIBEXT2FS)/bb_inode.c \
	$(LIBEXT2FS)/bitmaps.c \
	$(LIBEXT2FS)/bitops.c \
	$(LIBEXT2FS)/blkmap64_ba.c \
	$(LIBEXT2FS)/blkmap64_rb.c \
	$(LIBEXT2FS)/blknum.c \
	$(LIBEXT2FS)/block.c \
	$(LIBEXT2FS)/bmap.c \
	$(LIBEXT2FS)/check_desc.c \
	$(LIBEXT2FS)/crc16.c \
	$(LIBEXT2FS)/crc32c.c \
	$(LIBEXT2FS)/csum.c \
	$(LIBEXT2FS)/closefs.c \
	$(LIBEXT2FS)/dblist.c \
	$(LIBEXT2FS)/dblist_dir.c \
	$(LIBEXT2FS)/digest_encode.c \
	$(LIBEXT2FS)/dirblock.c \
	$(LIBEXT2FS)/dirhash.c \
	$(LIBEXT2FS)/dir_iterate.c \
	$(LIBEXT2FS)/dupfs.c \
	$(LIBEXT2FS)/expanddir.c \
	$(LIBEXT2FS)/ext_attr.c \
	$(LIBEXT2FS)/extent.c \
	$(LIBEXT2FS)/fallocate.c \
	$(LIBEXT2FS)/fileio.c \
	$(LIBEXT2FS)/finddev.c \
	$(LIBEXT2FS)/flushb.c \
	$(LIBEXT2FS)/freefs.c \
	$(LIBEXT2FS)/gen_bitmap.c \
	$(LIBEXT2FS)/gen_bitmap64.c \
	$(LIBEXT2FS)/get_num_dirs.c \
	$(LIBEXT2FS)/get_pathname.c \
	$(LIBEXT2FS)/getsize.c \
	$(LIBEXT2FS)/getsectsize.c \
	$(LIBEXT2FS)/hashmap.c \
	$(LIBEXT2FS)/i_block.c \
	$(LIBEXT2FS)/icount.c \
	$(LIBEXT2FS)/imager.c \
	$(LIBEXT2FS)/ind_block.c \
	$(LIBEXT2FS)/initialize.c \
	$(LIBEXT2FS)/inline.c \
	$(LIBEXT2FS)/inline_data.c \
	$(LIBEXT2FS)/inode.c \
	$(LIBEXT2FS)/io_manager.c \
	$(LIBEXT2FS)/ismounted.c \
	$(LIBEXT2FS)/link.c \
	$(LIBEXT2FS)/llseek.c \
	$(LIBEXT2FS)/lookup.c \
	$(LIBEXT2FS)/mmp.c \
	$(LIBEXT2FS)/mkdir.c \
	$(LIBEXT2FS)/mkjournal.c \
	$(LIBEXT2FS)/namei.c \
	$(LIBEXT2FS)/native.c \
	$(LIBEXT2FS)/newdir.c \
	$(LIBEXT2FS)/nls_utf8.c \
	$(LIBEXT2FS)/openfs.c \
	$(LIBEXT2FS)/progress.c \
	$(LIBEXT2FS)/punch.c \
	$(LIBEXT2FS)/qcow2.c \
	$(LIBEXT2FS)/rbtree.c \
	$(LIBEXT2FS)/read_bb.c \
	$(LIBEXT2FS)/read_bb_file.c \
	$(LIBEXT2FS)/res_gdt.c \
	$(LIBEXT2FS)/rw_bitmaps.c \
	$(LIBEXT2FS)/sha256.c \
	$(LIBEXT2FS)/sha512.c \
	$(LIBEXT2FS)/swapfs.c \
	$(LIBEXT2FS)/symlink.c \
	$(LIBEXT2FS)/undo_io.c \
	$(LIBEXT2FS)/unix_io.c \
	$(LIBEXT2FS)/sparse_io.c \
	$(LIBEXT2FS)/unlink.c \
	$(LIBEXT2FS)/valid_blk.c \
	$(LIBEXT2FS)/version.c \
	$(LIBEXT2FS)/test_io.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-Wno-unused-but-set-variable \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_blkid
LOCAL_SRC_FILES := \
	$(LIBEXT2_BLKID)/cache.c \
	$(LIBEXT2_BLKID)/dev.c \
	$(LIBEXT2_BLKID)/devname.c \
	$(LIBEXT2_BLKID)/devno.c \
	$(LIBEXT2_BLKID)/getsize.c \
	$(LIBEXT2_BLKID)/llseek.c \
	$(LIBEXT2_BLKID)/probe.c \
	$(LIBEXT2_BLKID)/read.c \
	$(LIBEXT2_BLKID)/resolve.c \
	$(LIBEXT2_BLKID)/save.c \
	$(LIBEXT2_BLKID)/tag.c \
	$(LIBEXT2_BLKID)/version.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-Wno-error=attributes \
	-Wno-error=pointer-sign \
	-Wno-unused-but-set-variable \
	-fno-strict-aliasing \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_uuid
LOCAL_SRC_FILES := \
	$(LIBEXT2_UUID)/clear.c \
	$(LIBEXT2_UUID)/compare.c \
	$(LIBEXT2_UUID)/copy.c \
	$(LIBEXT2_UUID)/gen_uuid.c \
	$(LIBEXT2_UUID)/isnull.c \
	$(LIBEXT2_UUID)/pack.c \
	$(LIBEXT2_UUID)/parse.c \
	$(LIBEXT2_UUID)/unpack.c \
	$(LIBEXT2_UUID)/unparse.c \
	$(LIBEXT2_UUID)/uuid_time.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_e2p
LOCAL_SRC_FILES := \
	$(LIBEXT2_E2P)/crypto_mode.c \
	$(LIBEXT2_E2P)/encoding.c \
	$(LIBEXT2_E2P)/errcode.c \
	$(LIBEXT2_E2P)/feature.c \
	$(LIBEXT2_E2P)/fgetflags.c \
	$(LIBEXT2_E2P)/fgetproject.c \
	$(LIBEXT2_E2P)/fgetversion.c \
	$(LIBEXT2_E2P)/fsetflags.c \
	$(LIBEXT2_E2P)/fsetproject.c \
	$(LIBEXT2_E2P)/fsetversion.c \
	$(LIBEXT2_E2P)/getflags.c \
	$(LIBEXT2_E2P)/getversion.c \
	$(LIBEXT2_E2P)/hashstr.c \
	$(LIBEXT2_E2P)/iod.c \
	$(LIBEXT2_E2P)/ljs.c \
	$(LIBEXT2_E2P)/ls.c \
	$(LIBEXT2_E2P)/mntopts.c \
	$(LIBEXT2_E2P)/ostype.c \
	$(LIBEXT2_E2P)/parse_num.c \
	$(LIBEXT2_E2P)/pe.c \
	$(LIBEXT2_E2P)/percent.c \
	$(LIBEXT2_E2P)/pf.c \
	$(LIBEXT2_E2P)/ps.c \
	$(LIBEXT2_E2P)/setflags.c \
	$(LIBEXT2_E2P)/setversion.c \
	$(LIBEXT2_E2P)/uuid.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-Wno-error=attributes \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_quota
LOCAL_SRC_FILES := \
	$(LIBEXT2_QUOTA)/devname.c \
	$(LIBEXT2_QUOTA)/dict.c \
	$(LIBEXT2_QUOTA)/mkquota.c \
	$(LIBEXT2_QUOTA)/parse_qtype.c \
	$(LIBEXT2_QUOTA)/plausible.c \
	$(LIBEXT2_QUOTA)/prof_err.c \
	$(LIBEXT2_QUOTA)/profile.c \
	$(LIBEXT2_QUOTA)/profile_helpers.c \
	$(LIBEXT2_QUOTA)/quotaio.c \
	$(LIBEXT2_QUOTA)/quotaio_tree.c \
	$(LIBEXT2_QUOTA)/quotaio_v2.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_misc
LOCAL_SRC_FILES := $(LIBEXT2_MISC)/create_inode.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-Wno-error=format-extra-args \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libext2_com_err
LOCAL_SRC_FILES := \
	$(LIBEXT2_COM_ERR)/com_err.c \
	$(LIBEXT2_COM_ERR)/com_right.c \
	$(LIBEXT2_COM_ERR)/error_message.c \
	$(LIBEXT2_COM_ERR)/et_name.c \
	$(LIBEXT2_COM_ERR)/init_et.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	-fPIC \
	-pthread

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libgnulib
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/lib/argmatch.c \
	$(LOCAL_PATH)/lib/basename-lgpl.c \
	$(LOCAL_PATH)/lib/basename.c \
	$(LOCAL_PATH)/lib/btowc.c \
	$(LOCAL_PATH)/lib/c-ctype.c \
	$(LOCAL_PATH)/lib/c-strcasecmp.c \
	$(LOCAL_PATH)/lib/c-strncasecmp.c \
	$(LOCAL_PATH)/lib/c32isprint.c \
	$(LOCAL_PATH)/lib/canonicalize-lgpl.c \
	$(LOCAL_PATH)/lib/cloexec.c \
	$(LOCAL_PATH)/lib/close-stream.c \
	$(LOCAL_PATH)/lib/closeout.c \
	$(LOCAL_PATH)/lib/dirname-lgpl.c \
	$(LOCAL_PATH)/lib/dirname.c \
	$(LOCAL_PATH)/lib/error.c \
	$(LOCAL_PATH)/lib/exitfail.c \
	$(LOCAL_PATH)/lib/fcntl.c \
	$(LOCAL_PATH)/lib/free.c \
	$(LOCAL_PATH)/lib/getdtablesize.c \
	$(LOCAL_PATH)/lib/hard-locale.c \
	$(LOCAL_PATH)/lib/ialloc.c \
	$(LOCAL_PATH)/lib/iswctype.c \
	$(LOCAL_PATH)/lib/iswdigit.c \
	$(LOCAL_PATH)/lib/iswpunct.c \
	$(LOCAL_PATH)/lib/iswxdigit.c \
	$(LOCAL_PATH)/lib/localcharset.c \
	$(LOCAL_PATH)/lib/long-options.c \
	$(LOCAL_PATH)/lib/malloca.c \
	$(LOCAL_PATH)/lib/mbrtoc32.c \
	$(LOCAL_PATH)/lib/mbrtowc.c \
	$(LOCAL_PATH)/lib/mbszero.c \
	$(LOCAL_PATH)/lib/nl_langinfo.c \
	$(LOCAL_PATH)/lib/progname.c \
	$(LOCAL_PATH)/lib/quotearg.c \
	$(LOCAL_PATH)/lib/rawmemchr.c \
	$(LOCAL_PATH)/lib/regex.c \
	$(LOCAL_PATH)/lib/rpmatch.c \
	$(LOCAL_PATH)/lib/safe-read.c \
	$(LOCAL_PATH)/lib/setlocale-lock.c \
	$(LOCAL_PATH)/lib/setlocale_null-unlocked.c \
	$(LOCAL_PATH)/lib/setlocale_null.c \
	$(LOCAL_PATH)/lib/stat-time.c \
	$(LOCAL_PATH)/lib/stripslash.c \
	$(LOCAL_PATH)/lib/tempname.c \
	$(LOCAL_PATH)/lib/version-etc-fsf.c \
	$(LOCAL_PATH)/lib/version-etc.c \
	$(LOCAL_PATH)/lib/wctype.c \
	$(LOCAL_PATH)/lib/unictype/ctype_print.c \
	$(LOCAL_PATH)/lib/xalloc-die.c \
	$(LOCAL_PATH)/lib/xmalloc.c \
	$(LOCAL_PATH)/lib/xstrtol.c \
	$(LOCAL_PATH)/lib/xstrtoll.c \
	$(LOCAL_PATH)/lib/xstrtoul.c \
	$(LOCAL_PATH)/lib/xstrtoull.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include/libgnulib \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../parted/lib/libgnulib \
	$(LOCAL_PATH)/parted/libgnuliblib
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Wno-nullability-completeness \
	-Wno-macro-redefined \
	-fPIC \
	-include $(LOCAL_PATH)/../include/PartitionManager/Alternatives.h

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libcharset
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/parted/libcharset/lib/localcharset.c \
	$(LOCAL_PATH)/parted/libcharset/lib/relocatable-stub.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../include/libcharset
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-fPIC \
	-g \
	-fvisibility=hidden

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libicrt
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/parted/libiconv/icrt/allocator.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/areadlink.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/binary-io.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/careadlinkat.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/fd-hook.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/getprogname.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/unistd.c \
	$(LOCAL_PATH)/parted/libiconv/icrt/xreadlink.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/parted/libiconv/lib \
	$(LOCAL_PATH)/parted/libiconv/srclib
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Wno-unused-function \
	-Wno-unused-but-set-variable \
	-Wno-missing-field-initializers \
	-fPIC

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libiconv
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/parted/libiconv/lib/iconv.c \
	$(LOCAL_PATH)/parted/libiconv/lib/relocatable.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include/libiconv \
	$(LOCAL_PATH)/parted/libiconv/lib \
	$(LOCAL_PATH)/parted/libiconv/srclib
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Wno-unused-function \
	-Wno-unused-but-set-variable \
	-Wno-missing-field-initializers \
	-fPIC

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := libparted
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/parted/libparted/architecture.c \
	$(LOCAL_PATH)/parted/libparted/debug.c \
	$(LOCAL_PATH)/parted/libparted/device.c \
	$(LOCAL_PATH)/parted/libparted/disk.c \
	$(LOCAL_PATH)/parted/libparted/exception.c \
	$(LOCAL_PATH)/parted/libparted/filesys.c \
	$(LOCAL_PATH)/parted/libparted/libparted.c \
	$(LOCAL_PATH)/parted/libparted/timer.c \
	$(LOCAL_PATH)/parted/libparted/unit.c \
	$(LOCAL_PATH)/parted/libparted/arch/linux.c \
	$(LOCAL_PATH)/parted/libparted/cs/constraint.c \
	$(LOCAL_PATH)/parted/libparted/cs/geom.c \
	$(LOCAL_PATH)/parted/libparted/cs/natmath.c \
	$(LOCAL_PATH)/parted/libparted/fs/amiga/a-interface.c \
	$(LOCAL_PATH)/parted/libparted/fs/amiga/affs.c \
	$(LOCAL_PATH)/parted/libparted/fs/amiga/amiga.c \
	$(LOCAL_PATH)/parted/libparted/fs/amiga/apfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/amiga/asfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/btrfs/btrfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/ext2/interface.c \
	$(LOCAL_PATH)/parted/libparted/fs/f2fs/f2fs.c \
	$(LOCAL_PATH)/parted/libparted/fs/fat/bootsector.c \
	$(LOCAL_PATH)/parted/libparted/fs/fat/fat.c \
	$(LOCAL_PATH)/parted/libparted/fs/hfs/hfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/hfs/probe.c \
	$(LOCAL_PATH)/parted/libparted/fs/jfs/jfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/linux_swap/linux_swap.c \
	$(LOCAL_PATH)/parted/libparted/fs/nilfs2/nilfs2.c \
	$(LOCAL_PATH)/parted/libparted/fs/ntfs/ntfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/filesys.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/bootsector.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/calc.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/clstdup.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/context.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/count.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/fat.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/fatio.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/resize.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/table.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/fat/traverse.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/advfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/advfs_plus.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/cache.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/file.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/file_plus.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/hfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/journal.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/probe.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/reloc.c \
	$(LOCAL_PATH)/parted/libparted/fs/r/hfs/reloc_plus.c \
	$(LOCAL_PATH)/parted/libparted/fs/reiserfs/reiserfs.c \
	$(LOCAL_PATH)/parted/libparted/fs/udf/udf.c \
	$(LOCAL_PATH)/parted/libparted/fs/ufs/ufs.c \
	$(LOCAL_PATH)/parted/libparted/fs/xfs/xfs.c \
	$(LOCAL_PATH)/parted/libparted/labels/aix.c \
	$(LOCAL_PATH)/parted/libparted/labels/atari.c \
	$(LOCAL_PATH)/parted/libparted/labels/bsd.c \
	$(LOCAL_PATH)/parted/libparted/labels/dos.c \
	$(LOCAL_PATH)/parted/libparted/labels/dvh.c \
	$(LOCAL_PATH)/parted/libparted/labels/efi_crc32.c \
	$(LOCAL_PATH)/parted/libparted/labels/fdasd.c \
	$(LOCAL_PATH)/parted/libparted/labels/gpt.c \
	$(LOCAL_PATH)/parted/libparted/labels/loop.c \
	$(LOCAL_PATH)/parted/libparted/labels/mac.c \
	$(LOCAL_PATH)/parted/libparted/labels/pt-tools.c \
	$(LOCAL_PATH)/parted/libparted/labels/rdb.c \
	$(LOCAL_PATH)/parted/libparted/labels/sun.c \
	$(LOCAL_PATH)/parted/libparted/labels/vtoc.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../include/libgnulib \
	$(LOCAL_PATH)/parted \
	$(LOCAL_PATH)/parted/libparted \
	$(LOCAL_PATH)/parted/libparted/labels \
	$(LOCAL_PATH)/parted/lib
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-fPIC \
	-Wno-pointer-sign \
	-Wno-sign-compare \
	-Wno-gnu-designator \
	-Wno-unused-variable \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument \
	-Wno-missing-field-initializers \
	-Wno-single-bit-bitfield-constant-conversion

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := pmt
LOCAL_SRC_FILES := \
	$(PMT)/Alternatives.c \
	$(PMT)/Debug.cpp \
	$(PMT)/Root.cpp \
	$(PMT)/PartedUtils.cpp \
	$(PMT)/PartitionManager.cpp \
	$(PMT)/PartitionTool.cpp \
	$(PMT)/ListPartitions.cpp \
	$(PMT)/Version.cpp \
	$(PMT)/GetState.cpp \
	$(PMT)/Tools.cpp \
	$(PMT)/LanguageTools.cpp \
	$(PMT)/Languages.cpp \
	$(PMT)/Help.cpp \
	$(MKE2FS)/default_profile.c \
	$(MKE2FS)/mk_hugefiles.c \
	$(MKE2FS)/mke2fs.c \
	$(MKE2FS)/util.c \
	$(PARTED)/parted/command.c \
	$(PARTED)/parted/jsonwrt.c \
	$(PARTED)/parted/parted.c \
	$(PARTED)/parted/strlist.c \
	$(PARTED)/parted/table.c \
	$(PARTED)/parted/ui.c \
	$(PARTED)/parted/version.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../include/PartitionManager \
	$(LOCAL_PATH)/../include/libgnulib \
	$(LOCAL_PATH)/../include/libparted \
	$(LOCAL_PATH)/parted/lib
	$(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := \
	$(PMT_CXXFLAGS) \
	$(E2FSPROGS_DEFAULT_CFLAGS) \
	$(PARTED_DEFAULTS_CFLAGS)
LOCAL_STATIC_LIBRARIES := \
	libext2fs \
	libext2_blkid \
	libext2_uuid \
	libext2_e2p \
	libext2_quota \
	libext2_misc \
	libext2_com_err \
	libgnulib \
	libparted \
	libiconv \
	libcharset \
	libicrt

include $(BUILD_EXECUTABLE)
