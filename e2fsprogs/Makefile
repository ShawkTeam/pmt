# By YZBruh

# Copyright 2024 Partition Manager
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#     http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

#####
# sub-make for building e2fsprogs (built-in mke2fs)
#####

# Include required files
include ../../build/config/env.mk
ifeq ($(INC_OLDENV),true)
include ../../build/config/oldenv.mk
endif

# Some variables, flags etc.
E := @ echo
INCLUDE := $(realpath ../../include/e2fsprogs)
E2FSPROGS_DEFAULT_CFLAGS = \
	-std=c17 \
	-Wall \
	-Werror \
	-Wno-pointer-arith \
	-Wno-sign-compare \
	-Wno-type-limits \
	-Wno-typedef-redefinition \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument \
	-fPIC \
	-pthread
INCLUDE_DIRS := \
	$(INCLUDE)/misc \
	$(INCLUDE)/blkid \
	$(INCLUDE)/e2p \
	$(INCLUDE)/et \
	$(INCLUDE)/ext2fs \
	$(INCLUDE)/ss \
	$(INCLUDE)/support \
	$(INCLUDE)/uuid \
	$(INCLUDE)/e2fsck \
	$(INCLUDE)
INC_DIRS := $(foreach dir,$(INCLUDE_DIRS),$(shell echo -I$(dir)))
CFLAGS := $(E2FSPROGS_DEFAULT_CFLAGS) $(INC_DIRS)
ARFLAGS := rcs
OUT := $(realpath ../../out/e2fsprogs)
MKE2FS := $(CURDIR)/mke2fs
LIB := $(CURDIR)/lib
LIBEXT2FS := $(LIB)/ext2fs
LIBEXT2_UUID := $(LIB)/uuid
LIBEXT2_E2P := $(LIB)/e2p
LIBEXT2_QUOTA := $(LIB)/support
LIBEXT2_MISC := $(LIB)/misc
LIBEXT2_COM_ERR := $(LIB)/et
LIBEXT2_BLKID := $(LIB)/blkid

# Source list of mke2fs
MKE2FS_SRCS := \
	$(MKE2FS)/default_profile.c \
	$(MKE2FS)/mk_hugefiles.c \
	$(MKE2FS)/mke2fs.c \
	$(MKE2FS)/util.c

# Source list of libext2fs
LIBEXT2FS_SRCS := \
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
	$(LIBEXT2FS)/ext2_err.c \
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

# Source list of libext2_uuid
LIBEXT2_UUID_SRCS := \
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

# Source list of libext2_blkid
LIBEXT2_BLKID_SRCS := \
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

# Source list of libext2_e2p
LIBEXT2_E2P_SRCS := \
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

# Source list of libext2_quota
LIBEXT2_QUOTA_SRCS := \
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

# Source od libext2_misc
LIBEXT2_MISC_SRCS := $(LIBEXT2_MISC)/create_inode.c

# Source list of libext2_com_err
LIBEXT2_COM_ERR_SRCS := \
	$(LIBEXT2_COM_ERR)/com_err.c \
	$(LIBEXT2_COM_ERR)/com_right.c \
	$(LIBEXT2_COM_ERR)/error_message.c \
	$(LIBEXT2_COM_ERR)/et_name.c \
	$(LIBEXT2_COM_ERR)/init_et.c

# Object lists
MKE2FS_OBJS := $(MKE2FS_SRCS:.c=.o)
LIBEXT2FS_OBJS := $(LIBEXT2FS_SRCS:.c=.o)
LIBEXT2_UUID_OBJS := $(LIBEXT2_UUID_SRCS:.c=.o)
LIBEXT2_BLKID_OBJS := $(LIBEXT2_BLKID_SRCS:.c=.o)
LIBEXT2_E2P_OBJS := $(LIBEXT2_E2P_SRCS:.c=.o)
LIBEXT2_QUOTA_OBJS := $(LIBEXT2_QUOTA_SRCS:.c=.o)
LIBEXT2_MISC_OBJS := $(LIBEXT2_MISC_SRCS:.c=.o)
LIBEXT2_COM_ERR_OBJS := $(LIBEXT2_COM_ERR_SRCS:.c=.o)

# Compiler flags (CFLAGS)
LIBEXT2FS_CFLAGS := -Wno-unused-but-set-variable
LIBEXT2_E2P_CFLAGS := -Wno-error=attributes
LIBEXT2_MISC_CFLAGS := -Wno-error=format-extra-args
LIBEXT2_BLKID_CFLAGS := \
	-Wno-error=attributes \
	-Wno-error=pointer-sign \
	-Wno-unused-but-set-variable \
	-fno-strict-aliasing

# Full object list
OBJS_ALL := \
	$(MKE2FS_OBJS) \
	$(LIBEXT2FS_OBJS) \
	$(LIBEXT2_BLKID_OBJS) \
	$(LIBEXT2_UUID_OBJS) \
	$(LIBEXT2_E2P_OBJS) \
	$(LIBEXT2_QUOTA_OBJS) \
	$(LIBEXT2_MISC_OBJS) \
	$(LIBEXT2_COM_ERR_OBJS)

# Progress list
PROGRESS_LIST := \
	$(LIBEXT2_BLKID_OBJS) \
	libext2_blkid_ar \
	$(LIBEXT2_UUID_OBJS) \
	libext2_uuid_ar \
	$(LIBEXT2_E2P_OBJS) \
	libext2_e2p_ar \
	$(LIBEXT2FS_OBJS) \
	libext2fs_ar \
	$(LIBEXT2_QUOTA_OBJS) \
	libext2_quota_ar \
	$(LIBEXT2_MISC_OBJS) \
	libext2_misc_ar \
	$(LIBEXT2_COM_ERR_OBJS) \
	libext2_com_err_ar \
	$(MKE2FS_OBJS) \
	mke2fs_dummy_ld

.PHONY: all
all: $(PROGRESS_LIST)

# Cleaner 
.PHONY: clean
clean:
	@ rm -rf $(OBJS_ALL)

#######################################
# 'MAKE' TARGETS FOR BUILDING OBJECTS #
#######################################

$(MKE2FS)/%.o: $(MKE2FS)/%.c
	$(E) "   CC    e2fsprogs/`basename $(MKE2FS)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) $(MKE2FS_CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2FS)/%.o: $(LIBEXT2FS)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2FS)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) $(LIBEXT2FS_CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_BLKID)/%.o: $(LIBEXT2_BLKID)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_BLKID)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) $(LIBEXT2_BLKID_CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_E2P)/%.o: $(LIBEXT2_E2P)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_E2P)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_UUID)/%.o: $(LIBEXT2_UUID)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_UUID)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_QUOTA)/%.o: $(LIBEXT2_QUOTA)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_QUOTA)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_MISC)/%.o: $(LIBEXT2_MISC)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_MISC)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) $(LIBEXT2_MISC_CFLAGS) "$<" -o "$@" || exit 1

$(LIBEXT2_COM_ERR)/%.o: $(LIBEXT2_COM_ERR)/%.c
	$(E) "   CC    e2fsprogs/lib/`basename $(LIBEXT2_COM_ERR)`/`basename $@`"
	@ $(CC) -c $(CFLAGS) "$<" -o "$@" || exit 1

#############################################
# 'MAKE' TARGETS FOR GENERATING STATIC LIBS #
#############################################

libext2fs_ar: $(LIBEXT2FS_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2fs.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2fs.a $^ || exit 1
	$(E) "   ----------- libext2_quota -----------"

libext2_blkid_ar: $(LIBEXT2_BLKID_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_blkid.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_blkid.a $^ || exit 1
	$(E) "   ----------- libext2_uuid ---------"

libext2_e2p_ar: $(LIBEXT2_E2P_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_e2p.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_e2p.a $^ || exit 1
	$(E) "   ----------- libext2fs -----------"

libext2_uuid_ar: $(LIBEXT2_UUID_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_uuid.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_uuid.a $^ || exit 1
	$(E) "   ----------- libext2_e2p -----------"

libext2_quota_ar: $(LIBEXT2_QUOTA_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_quota.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_quota.a $^ || exit 1
	$(E) "   ----------- libext2_misc -----------"

libext2_misc_ar: $(LIBEXT2_MISC_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_misc.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_misc.a $^ || exit 1
	$(E) "   ----------- libext2_com_err -----------"

libext2_com_err_ar: $(LIBEXT2_COM_ERR_OBJS)
	$(E) "   AR    out/e2fsprogs/libext2_com_err.a"
	@ $(AR) $(ARFLAGS) $(OUT)/libext2_com_err.a $^ || exit 1
	$(E) "   ----------- mke2fs -----------"

#############################################
# DUMMY 'MAKE' TARGET FOR DISPLAYING MKE2FS #
#############################################

mke2fs_dummy_ld:
	$(E) "   DMY   mke2fs"
