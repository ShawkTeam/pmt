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
	-Wno-unused-parameter \
	-static \
	$(PMT_EXTRA_CXXFLAGS)
E2FSPROGS_DEFAULT_CFLAGS = \
	-Werror \
	-std=c17 \
	-Wno-pointer-arith \
	-Wno-sign-compare \
	-Wno-type-limits \
	-Wno-typedef-redefinition \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument \
	-include ../include/PartitionManager/Alternatives.h
PARTED_DEFAULTS_CFLAGS = \
	-std=c17 \
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

PMT := $(LOCAL_PATH)/PartitionManager
PARTED := $(LOCAL_PATH)/parted
PARTED_SRCDIR := $(PARTED)/parted
MKE2FS := $(LOCAL_PATH)/e2fsprogs/mke2fs
LIBGNULIB := $(PARTED)/libgnulib
LIBCHARSET := $(PARTED)/libcharset
LIBICRT := $(PARTED)/libiconv/icrt
LIBICONV := $(PARTED)/libiconv
LIBPARTED := $(PARTED)/libparted
LIB := $(LOCAL_PATH)/e2fsprogs/lib
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
	$(LIBGNULIB)/lib/argmatch.c \
	$(LIBGNULIB)/lib/basename-lgpl.c \
	$(LIBGNULIB)/lib/basename.c \
	$(LIBGNULIB)/lib/btowc.c \
	$(LIBGNULIB)/lib/c-ctype.c \
	$(LIBGNULIB)/lib/c-strcasecmp.c \
	$(LIBGNULIB)/lib/c-strncasecmp.c \
	$(LIBGNULIB)/lib/c32isprint.c \
	$(LIBGNULIB)/lib/canonicalize-lgpl.c \
	$(LIBGNULIB)/lib/cloexec.c \
	$(LIBGNULIB)/lib/close-stream.c \
	$(LIBGNULIB)/lib/closeout.c \
	$(LIBGNULIB)/lib/dirname-lgpl.c \
	$(LIBGNULIB)/lib/dirname.c \
	$(LIBGNULIB)/lib/error.c \
	$(LIBGNULIB)/lib/exitfail.c \
	$(LIBGNULIB)/lib/fcntl.c \
	$(LIBGNULIB)/lib/free.c \
	$(LIBGNULIB)/lib/getdtablesize.c \
	$(LIBGNULIB)/lib/hard-locale.c \
	$(LIBGNULIB)/lib/ialloc.c \
	$(LIBGNULIB)/lib/iswctype.c \
	$(LIBGNULIB)/lib/iswdigit.c \
	$(LIBGNULIB)/lib/iswpunct.c \
	$(LIBGNULIB)/lib/iswxdigit.c \
	$(LIBGNULIB)/lib/localcharset.c \
	$(LIBGNULIB)/lib/long-options.c \
	$(LIBGNULIB)/lib/malloca.c \
	$(LIBGNULIB)/lib/mbrtoc32.c \
	$(LIBGNULIB)/lib/mbrtowc.c \
	$(LIBGNULIB)/lib/mbszero.c \
	$(LIBGNULIB)/lib/nl_langinfo.c \
	$(LIBGNULIB)/lib/progname.c \
	$(LIBGNULIB)/lib/quotearg.c \
	$(LIBGNULIB)/lib/rawmemchr.c \
	$(LIBGNULIB)/lib/regex.c \
	$(LIBGNULIB)/lib/rpmatch.c \
	$(LIBGNULIB)/lib/safe-read.c \
	$(LIBGNULIB)/lib/setlocale-lock.c \
	$(LIBGNULIB)/lib/setlocale_null-unlocked.c \
	$(LIBGNULIB)/lib/setlocale_null.c \
	$(LIBGNULIB)/lib/stat-time.c \
	$(LIBGNULIB)/lib/stripslash.c \
	$(LIBGNULIB)/lib/tempname.c \
	$(LIBGNULIB)/lib/version-etc-fsf.c \
	$(LIBGNULIB)/lib/version-etc.c \
	$(LIBGNULIB)/lib/wctype.c \
	$(LIBGNULIB)/lib/unictype/ctype_print.c \
	$(LIBGNULIB)/lib/xalloc-die.c \
	$(LIBGNULIB)/lib/xmalloc.c \
	$(LIBGNULIB)/lib/xstrtol.c \
	$(LIBGNULIB)/lib/xstrtoll.c \
	$(LIBGNULIB)/lib/xstrtoul.c \
	$(LIBGNULIB)/lib/xstrtoull.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include/libgnulib \
	$(LOCAL_PATH)/../include \
	$(PARTED)/lib \
	$(LIBGNULIB)/lib
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
	$(LIBCHARSET)/lib/localcharset.c \
	$(LIBCHARSET)/lib/relocatable-stub.c
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
	$(LIBICRT)/allocator.c \
	$(LIBICRT)/areadlink.c \
	$(LIBICRT)/binary-io.c \
	$(LIBICRT)/careadlinkat.c \
	$(LIBICRT)/fd-hook.c \
	$(LIBICRT)/getprogname.c \
	$(LIBICRT)/unistd.c \
	$(LIBICRT)/xreadlink.c
LOCAL_C_INCLUDES := \
	$(LIBICONV)/lib \
	$(LIBICONV)/srclib
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
	$(LIBICONV)/lib/iconv.c \
	$(LIBICONV)/lib/relocatable.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include/libiconv \
	$(LIBICONV)/lib \
	$(LIBICONV)/srclib
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
	$(LIBPARTED)/architecture.c \
	$(LIBPARTED)/debug.c \
	$(LIBPARTED)/device.c \
	$(LIBPARTED)/disk.c \
	$(LIBPARTED)/exception.c \
	$(LIBPARTED)/filesys.c \
	$(LIBPARTED)/libparted.c \
	$(LIBPARTED)/timer.c \
	$(LIBPARTED)/unit.c \
	$(LIBPARTED)/arch/linux.c \
	$(LIBPARTED)/cs/constraint.c \
	$(LIBPARTED)/cs/geom.c \
	$(LIBPARTED)/cs/natmath.c \
	$(LIBPARTED)/fs/amiga/a-interface.c \
	$(LIBPARTED)/fs/amiga/affs.c \
	$(LIBPARTED)/fs/amiga/amiga.c \
	$(LIBPARTED)/fs/amiga/apfs.c \
	$(LIBPARTED)/fs/amiga/asfs.c \
	$(LIBPARTED)/fs/btrfs/btrfs.c \
	$(LIBPARTED)/fs/ext2/interface.c \
	$(LIBPARTED)/fs/f2fs/f2fs.c \
	$(LIBPARTED)/fs/fat/bootsector.c \
	$(LIBPARTED)/fs/fat/fat.c \
	$(LIBPARTED)/fs/hfs/hfs.c \
	$(LIBPARTED)/fs/hfs/probe.c \
	$(LIBPARTED)/fs/jfs/jfs.c \
	$(LIBPARTED)/fs/linux_swap/linux_swap.c \
	$(LIBPARTED)/fs/nilfs2/nilfs2.c \
	$(LIBPARTED)/fs/ntfs/ntfs.c \
	$(LIBPARTED)/fs/r/filesys.c \
	$(LIBPARTED)/fs/r/fat/bootsector.c \
	$(LIBPARTED)/fs/r/fat/calc.c \
	$(LIBPARTED)/fs/r/fat/clstdup.c \
	$(LIBPARTED)/fs/r/fat/context.c \
	$(LIBPARTED)/fs/r/fat/count.c \
	$(LIBPARTED)/fs/r/fat/fat.c \
	$(LIBPARTED)/fs/r/fat/fatio.c \
	$(LIBPARTED)/fs/r/fat/resize.c \
	$(LIBPARTED)/fs/r/fat/table.c \
	$(LIBPARTED)/fs/r/fat/traverse.c \
	$(LIBPARTED)/fs/r/hfs/advfs.c \
	$(LIBPARTED)/fs/r/hfs/advfs_plus.c \
	$(LIBPARTED)/fs/r/hfs/cache.c \
	$(LIBPARTED)/fs/r/hfs/file.c \
	$(LIBPARTED)/fs/r/hfs/file_plus.c \
	$(LIBPARTED)/fs/r/hfs/hfs.c \
	$(LIBPARTED)/fs/r/hfs/journal.c \
	$(LIBPARTED)/fs/r/hfs/probe.c \
	$(LIBPARTED)/fs/r/hfs/reloc.c \
	$(LIBPARTED)/fs/r/hfs/reloc_plus.c \
	$(LIBPARTED)/fs/reiserfs/reiserfs.c \
	$(LIBPARTED)/fs/udf/udf.c \
	$(LIBPARTED)/fs/ufs/ufs.c \
	$(LIBPARTED)/fs/xfs/xfs.c \
	$(LIBPARTED)/labels/aix.c \
	$(LIBPARTED)/labels/atari.c \
	$(LIBPARTED)/labels/bsd.c \
	$(LIBPARTED)/labels/dos.c \
	$(LIBPARTED)/labels/dvh.c \
	$(LIBPARTED)/labels/efi_crc32.c \
	$(LIBPARTED)/labels/fdasd.c \
	$(LIBPARTED)/labels/gpt.c \
	$(LIBPARTED)/labels/loop.c \
	$(LIBPARTED)/labels/mac.c \
	$(LIBPARTED)/labels/pt-tools.c \
	$(LIBPARTED)/labels/rdb.c \
	$(LIBPARTED)/labels/sun.c \
	$(LIBPARTED)/labels/vtoc.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../include/libgnulib \
	$(PARTED) \
	$(LIBPARTED) \
	$(LIBPARTED)/labels \
	$(PARTED)/lib
LOCAL_CFLAGS := $(PARTED_DEFAULTS_CFLAGS)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := lib__parted_objs
LOCAL_SRC_FILES := \
	$(PARTED)/command.c \
	$(PARTED)/jsonwrt.c \
	$(PARTED)/parted.c \
	$(PARTED)/strlist.c \
	$(PARTED)/table.c \
	$(PARTED)/ui.c \
	$(PARTED)/version.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../include/libgnulib \
	$(PARTED) \
	$(LIBPARTED) \
	$(LIBPARTED)/labels \
	$(PARTED)/lib
LOCAL_CFLAGS := $(PARTED_DEFAULTS_CFLAGS)

include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)

LOCAL_MODULE := lib__mke2fs_objs
LOCAL_SRC_FILES := \
	$(MKE2FS)/default_profile.c \
	$(MKE2FS)/mk_hugefiles.c \
	$(MKE2FS)/mke2fs.c \
	$(MKE2FS)/util.c
LOCAL_C_INCLUDES := $(E2FSPROGS_INCLUDES)
LOCAL_CFLAGS := $(E2FSPROGS_DEFAULT_CFLAGS)

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
	$(PMT)/Help.cpp
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../include \
	$(LOCAL_PATH)/../include/PartitionManager
LOCAL_CFLAGS := $(PMT_CXXFLAGS)
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
	libicrt \
	lib__parted_objs \
	lib__mke2fs_objs

include $(BUILD_EXECUTABLE)
