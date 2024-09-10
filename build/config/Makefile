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

CXX = clang++
AR = ar
CXXFLAGS ?= \
	-O3 \
	-I../include \
	-std=c++20 \
	-Wall \
	-Wextra \
	-Werror \
	-Wno-vla-cxx-extension \
	-Wno-nullability-completeness \
	-Wno-writable-strings \
	-Wno-unused-parameter \
	-Wno-unused-command-line-argument \
	-Wno-nullability-extension \
	-Wno-reorder-init-list \
	-Wno-gnu-zero-variadic-macro-arguments \
	$(PMT_EXTRA_CXXFLAGS)

# set compiler setting (clang and ar)
ifneq ($(PMT_CXX),)
	CXX ?= $(PMT_CXX)
endif

ifneq ($(PMT_AR),)
	AR ?= $(PMT_AR)
endif

# compiler flags settings
ifeq ($(PMT_ENABLE_DEBUG),true)
	CXXFLAGS += \
		-gdwarf-5 \
		-fsanitize=address
endif

# write current env configuration to oldenv.mk
all:
	@ echo "CXX := $(CXX)" > oldenv.mk
	@ echo "AR := $(AR)" >> oldenv.mk
	@ echo "CXXFLAGS := $(CXXFLAGS)" >> oldenv.mk
