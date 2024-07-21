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

include env.mk

#########################################
#                                       #
#          Apply Configuration          #
#                                       #
#      Warning: please do not edit      #
#                                       #
#########################################

CC = clang
CFLAGS ?= "-O3 -I../include -std=c11 -pedantic -Wall -Wextra -Werror -Wno-nullability-extension -Wno-gnu-zero-variadic-macro-arguments $(PMT_EXTRA_CFLAGS)"

# set compiler setting (clang-gcc and ar)
ifneq ($(PMT_CC),)
	CC ?= $(PMT_CC)
else
	CC ?= clang
endif

ifneq ($(PMT_AR),)
	AR ?= $(PMT_AR)
else
	AR ?= ar
endif

# compiler flags settings
ifneq ($(PMT_ENABLE_DEBUG),)
	CFLAGS += -gdwarf-5 -fsanitize=address
endif

# write current env configuration to oldenv.mk
all:
	@echo "CC := $(CC)" > oldenv.mk; \
	echo "AR := $(AR)" >> oldenv.mk; \
	echo "CFLAGS := $(CFLAGS)" >> oldenv.mk
