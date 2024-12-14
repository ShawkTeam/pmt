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
# sub-make for building libcharset (built-in lib)
#####

include ../../../build/config/env.mk
ifeq ($(INC_OLDENV),true)
include ../../../build/config/oldenv.mk
endif

E := @ echo
INCLUDE_DIR := $(CURDIR)/../../../include/libcharset
CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-fPIC \
	-g \
	-fvisibility=hidden \
	-I$(INCLUDE_DIR)
AR_FLAGS := rcs
OUT := $(realpath ../../../out/parted)
LIB := $(CURDIR)/lib

LIBCHARSET_SRCS := \
	$(LIB)/localcharset.c \
	$(LIB)/relocatable-stub.c
LIBCHARSET_OBJS := $(LIBCHARSET_SRCS:.c=.o)

PROGRESS_LIST := \
	outctrl \
	$(LIBCHARSET_OBJS) \
	libcharset_ar

.PHONY: all
all: $(PROGRESS_LIST)

.PHONY: clean
clean:
	@ rm -f $(LIBCHARSET_OBJS) $(OUT)/libcharset.a

outctrl:
	@ if [ ! -d $(OUT) ]; then mkdir -p $(OUT); fi

$(LIB)/%.o: $(LIB)/%.c
	$(E) "   CC    libcharset/lib/`basename $@`"
	@ $(CC) -c $(CFLAGS) -o $@ $^ || exit 1

libcharset_ar: $(LIBCHARSET_OBJS)
	$(E) "   AR    out/parted/libcharset.a"
	@ $(AR) $(AR_FLAGS) $(OUT)/libcharset.a $(LIBCHARSET_OBJS)
