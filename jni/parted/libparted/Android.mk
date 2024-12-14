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

include $(CLEAR_VARS)

LOCAL_MODULE := libparted
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/architecture.c \
	$(LOCAL_PATH)/debug.c \
	$(LOCAL_PATH)/device.c \
	$(LOCAL_PATH)/disk.c \
	$(LOCAL_PATH)/exception.c \
	$(LOCAL_PATH)/filesys.c \
	$(LOCAL_PATH)/libparted.c \
	$(LOCAL_PATH)/timer.c \
	$(LOCAL_PATH)/unit.c \
	$(LOCAL_PATH)/arch/linux.c \
	$(LOCAL_PATH)/cs/constraint.c \
	$(LOCAL_PATH)/cs/geom.c \
	$(LOCAL_PATH)/cs/natmath.c \
	$(LOCAL_PATH)/fs/amiga/a-interface.c \
	$(LOCAL_PATH)/fs/amiga/affs.c \
	$(LOCAL_PATH)/fs/amiga/amiga.c \
	$(LOCAL_PATH)/fs/amiga/apfs.c \
	$(LOCAL_PATH)/fs/amiga/asfs.c \
	$(LOCAL_PATH)/fs/btrfs/btrfs.c \
	$(LOCAL_PATH)/fs/ext2/interface.c \
	$(LOCAL_PATH)/fs/f2fs/f2fs.c \
	$(LOCAL_PATH)/fs/fat/bootsector.c \
	$(LOCAL_PATH)/fs/fat/fat.c \
	$(LOCAL_PATH)/fs/hfs/hfs.c \
	$(LOCAL_PATH)/fs/hfs/probe.c \
	$(LOCAL_PATH)/fs/jfs/jfs.c \
	$(LOCAL_PATH)/fs/linux_swap/linux_swap.c \
	$(LOCAL_PATH)/fs/nilfs2/nilfs2.c \
	$(LOCAL_PATH)/fs/ntfs/ntfs.c \
	$(LOCAL_PATH)/fs/r/filesys.c \
	$(LOCAL_PATH)/fs/r/fat/bootsector.c \
	$(LOCAL_PATH)/fs/r/fat/calc.c \
	$(LOCAL_PATH)/fs/r/fat/clstdup.c \
	$(LOCAL_PATH)/fs/r/fat/context.c \
	$(LOCAL_PATH)/fs/r/fat/count.c \
	$(LOCAL_PATH)/fs/r/fat/fat.c \
	$(LOCAL_PATH)/fs/r/fat/fatio.c \
	$(LOCAL_PATH)/fs/r/fat/resize.c \
	$(LOCAL_PATH)/fs/r/fat/table.c \
	$(LOCAL_PATH)/fs/r/fat/traverse.c \
	$(LOCAL_PATH)/fs/r/hfs/advfs.c \
	$(LOCAL_PATH)/fs/r/hfs/advfs_plus.c \
	$(LOCAL_PATH)/fs/r/hfs/cache.c \
	$(LOCAL_PATH)/fs/r/hfs/file.c \
	$(LOCAL_PATH)/fs/r/hfs/file_plus.c \
	$(LOCAL_PATH)/fs/r/hfs/hfs.c \
	$(LOCAL_PATH)/fs/r/hfs/journal.c \
	$(LOCAL_PATH)/fs/r/hfs/probe.c \
	$(LOCAL_PATH)/fs/r/hfs/reloc.c \
	$(LOCAL_PATH)/fs/r/hfs/reloc_plus.c \
	$(LOCAL_PATH)/fs/reiserfs/reiserfs.c \
	$(LOCAL_PATH)/fs/udf/udf.c \
	$(LOCAL_PATH)/fs/ufs/ufs.c \
	$(LOCAL_PATH)/fs/xfs/xfs.c \
	$(LOCAL_PATH)/labels/aix.c \
	$(LOCAL_PATH)/labels/atari.c \
	$(LOCAL_PATH)/labels/bsd.c \
	$(LOCAL_PATH)/labels/dos.c \
	$(LOCAL_PATH)/labels/dvh.c \
	$(LOCAL_PATH)/labels/efi_crc32.c \
	$(LOCAL_PATH)/labels/fdasd.c \
	$(LOCAL_PATH)/labels/gpt.c \
	$(LOCAL_PATH)/labels/loop.c \
	$(LOCAL_PATH)/labels/mac.c \
	$(LOCAL_PATH)/labels/pt-tools.c \
	$(LOCAL_PATH)/labels/rdb.c \
	$(LOCAL_PATH)/labels/sun.c \
	$(LOCAL_PATH)/labels/vtoc.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../include \
	$(LOCAL_PATH)/../../include/libgnulib \
	$(LOCAL_PATH)/parted \
	$(LOCAL_PATH)/libparted \
	$(LOCAL_PATH)/libparted/labels \
	$(LOCAL_PATH)/lib
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