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
# sub-make for building parted (built-in parted)
#####

# Include required files
include ../../build/config/env.mk
ifeq ($(INC_OLDENV),true)
include ../../build/config/oldenv.mk
endif

# Some flags etc
E := @ echo
INCLUDE_DIRS := \
	$(CURDIR)/../../include \
	$(CURDIR)/../../include/libgnulib \
	$(CURDIR)/parted \
	$(CURDIR)/libparted \
	$(CURDIR)/libparted/labels \
	$(CURDIR)/lib
CFLAGS := \
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
	-Wno-single-bit-bitfield-constant-conversion \
	$(foreach dir,$(INCLUDE_DIRS),$(shell echo -I$(dir)))
AR_FLAGS := rcs
OUT := $(realpath ../../out/parted)
LIBPARTED := libparted
PARTED := parted
PATH := $(shell echo $$PREFIX)/bin

LIBPARTED_SRCS := \
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

PARTED_SRCS := \
	$(PARTED)/command.c \
	$(PARTED)/jsonwrt.c \
	$(PARTED)/parted.c \
	$(PARTED)/strlist.c \
	$(PARTED)/table.c \
	$(PARTED)/ui.c \
	$(PARTED)/version.c

LIBPARTED_OBJS := $(LIBPARTED_SRCS:.c=.o)
PARTED_OBJS := $(PARTED_SRCS:.c=.o)

OBJS_ALL := \
	$(LIBPARTED_OBJS) \
	$(PARTED_OBJS)

PROGRESS_LIST := \
	make_outdir \
	build_libgnulib \
	build_libcharset \
	build_libiconv_and_libicrt \
	print_libparted \
	$(LIBPARTED_OBJS) \
	libparted_ar \
	print_parted \
	$(PARTED_OBJS) \
	dummy_parted

.PHONY: all
all: $(PROGRESS_LIST)

.PHONY: clean
clean:
	@ rm -rf $(OBJS_ALL) $(OUT) *.a
	@ $(MAKE) -C $(CURDIR)/libgnulib -s clean
	@ $(MAKE) -C $(CURDIR)/libiconv -s clean
	@ $(MAKE) -C $(CURDIR)/libcharset -s clean

.PHONY: install
install:
	@ abort() { \
		echo "$1"; \
		exit 1; \
	}; \
	[ -f $(PATH)/parted-test ] && \
	abort "Already installed."; \
	cp $(OUT)/parted $(PATH)/parted-test || \
	abort "Copying failed!"; \
	chmod 777 $(PATH)/parted-test || \
	abort "Cannot set permissions!"

.PHONY: uninstall
uninstall:
	@ if [ ! -f $(PATH)/parted-test ]; then echo "Already uninstalled"; exit 1; fi
	@ rm -f $(PATH)/parted-test &>/dev/null

.PHONY:
reinstall:
	@ $(MAKE) -s uninstall
	@ $(MAKE) -s install

$(LIBPARTED)/%.o: $(LIBPARTED)/%.c
	$(E) "   CC    $@"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

$(PARTED)/%.o: $(PARTED)/%.c
	$(E) "   CC    $@"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

libparted_ar: $(LIBPARTED_OBJS)
	$(E) "   AR    out/parted/libparted.a"
	@ $(AR) $(AR_FLAGS) $(OUT)/libparted.a $(LIBPARTED_OBJS)

build_libgnulib:
	@ $(MAKE) -C $(CURDIR)/libgnulib -s

build_libcharset:
	$(E) "   ----------- libcharset ----------- "
	@ $(MAKE) -C $(CURDIR)/libcharset -s

build_libiconv_and_libicrt:
	$(E) "   ----------- libicrt ----------- "
	@ $(MAKE) -C $(CURDIR)/libiconv -s

make_outdir:
	@ if [ ! -d $(OUT) ]; then mkdir -p $(OUT); fi

print_libparted:
	$(E) "   ----------- libparted ----------- "

print_parted:
	$(E) "   ----------- parted ----------- "

dummy_parted:
	$(E) "   DMY   parted"
