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
# sub-make for building libiconv and libicrt (built-in libs)
#####

# Include required files
include ../../../build/config/env.mk
ifeq ($(INC_OLDENV),true)
include ../../../build/config/oldenv.mk
endif

E := @ echo
INCLUDE_DIRS := \
	$(CURDIR)/../../../include/libiconv \
	$(CURDIR)/lib \
	$(CURDIR)/srclib
CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Wno-unused-function \
	-Wno-unused-but-set-variable \
	-Wno-missing-field-initializers \
	-fPIC \
	$(foreach dir,$(INCLUDE_DIRS),$(shell echo "-I$(dir)"))
AR_FLAGS := rcs
OUT := $(realpath ../../../out/parted)
LIB := $(CURDIR)/lib
SRC := $(CURDIR)/src
SRCLIB := $(CURDIR)/srclib
LIBICRT := $(CURDIR)/icrt

LIBICRT_SRCS := \
	$(LIBICRT)/allocator.c \
	$(LIBICRT)/areadlink.c \
	$(LIBICRT)/binary-io.c \
	$(LIBICRT)/careadlinkat.c \
	$(LIBICRT)/fd-hook.c \
	$(LIBICRT)/getprogname.c \
	$(LIBICRT)/unistd.c \
	$(LIBICRT)/xreadlink.c

LIBICRT_OBJS := $(LIBICRT_SRCS:.c=.o)

LIBICONV_SRCS := \
	$(LIB)/iconv.c \
	$(LIB)/relocatable.c

LIBICONV_OBJS := $(LIBICONV_SRCS:.c=.o)

PROGRESS_LIST := \
	outctrl \
	$(LIBICRT_OBJS) \
	libicrt_ar \
	print_iconv \
	$(LIBICONV_OBJS) \
	libiconv_ar

.PHONY: all
all: $(PROGRESS_LIST)

.PHONY: clean
clean:
	@ rm -rf $(LIBICONV_OBJS) $(LIBICRT_OBJS) $(OUT)/libicrt.a $(OUT)/libiconv.a

outctrl:
	@ if [ ! -d $(OUT) ]; then mkdir -p $(OUT); fi

$(LIBICRT)/%.o: $(LIBICRT)/%.c
	$(E) "   CC    libiconv/icrt/`basename $@`"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

$(LIB)/%.o: $(LIB)/%.c
	$(E) "   CC    libiconv/lib/`basename $@`"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

$(SRC)/%.o: $(SRC)/%.c
	$(E) "   CC    libiconv/src/`basename $@`"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

libicrt_ar: $(LIBICRT_OBJS)
	$(E) "   AR    out/parted/libicrt.a"
	@ $(AR) $(AR_FLAGS) $(OUT)/libicrt.a $(LIBICRT_OBJS)

libiconv_ar: $(LIBICONV_OBJS)
	$(E) "   AR    out/parted/libiconv.a"
	@ $(AR) $(AR_FLAGS) $(OUT)/libiconv.a $(LIBICONV_OBJS)

print_iconv:
	$(E) "   ----------- libiconv ----------- "
