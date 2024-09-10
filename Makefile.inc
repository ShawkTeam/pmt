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

# speficy
VERSION := 2.8.0
VERSION_CODE := 280
TARGET := pmt

# device arch info
ARCH := $(shell uname -m)

# current directory
OUT_DIRNAME ?= out
SOURCE_DIRNAME ?= jni

# others needed important variables
ifeq ($(THIS_IS),src)
	BUILD := ../build
	SOURCE_DIR := $(CURDIR)
	OUT_DIR := ../$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
else ifeq ($(THIS_IS),debutils)
	BUILD := ..
	SOURCE_DIR := ../../$(SOURCE_DIRNAME)
	OUT_DIR := ../../$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
else ifeq ($(THIS_IS),out)
	BUILD := ../build
	SOURCE_DIR := ../$(SOURCE_DIRNAME)
	OUT_DIR := $(CURDIR)
	DEBUTILS_DIR := $(BÜILD)/deb
else ifeq ($(THIS_IS),main)
	BUILD := $(CURDIR)/build
	SOURCE_DIR := $(CURDIR)/$(SOURCE_DIRNAME)
	OUT_DIR := $(CURDIR)/$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
endif

BINARY_DIR := $(OUT_DIR)/binary
PACKAGE_DIR := $(OUT_DIR)/package
DEB_DIR := $(OUT_DIR)/debpackage
TOOLS := $(BUILD)/tools
UTILS := $(BUILD)/util
BASH_DIR := $(BUILD)/bash
OTHERS := $(BUILD)/others
TERMUX_USR := /data/data/com.termux/files/usr
TERMUX_BIN := $(TERMUX_USR)/bin
LINUX_BIN := /usr/bin
DEBTERMUX_USR := $(DEBUTILS_DIR)/template$(TERMUX_USR)

ifneq ($(wildcard $(LINUX_BIN)),)
	BIN := $(LINUX_BIN)
else
	BIN := $(TERMUX_BIN)
endif

include $(UTILS)/utils.mk

ifneq ($(shell basename $(SOURCE_DIR)),$(SOURCE_DIRNAME))
	$(error The index name specified with the current source directory name is not the same! Something's wrong)
endif

ifneq ($(shell basename $(OUT_DIR)),$(OUT_DIRNAME))
	$(error The index name specified with the current output directory name is not the same! Something's wrong)
endif

# sources
SRCS := $(wildcard $(SOURCE_DIR)/*.cpp)
OBJS = $(SRCS:.cpp=.o)

# other directories in the out directory
IN_OUT_DIR := \
	$(BINARY_DIR) \
	$(PACKAGE_DIR) \
	$(STATICLIB_DIR)

# list of file/directory to be checked when the deb pack is created
DEB_CHECKS := \
	$(DEBUTILS_DIR)/ \
	$(DEBUTILS_DIR)/DEBIAN \
	$(DEBUTILS_DIR)/DEBIAN/control_32 \
	$(DEBUTILS_DIR)/DEBIAN/control_64 \
	$(DEBUTILS_DIR)/mandoc \
	$(DEBUTILS_DIR)/mandoc/$(TARGET).8.gz \
	$(DEBUTILS_DIR)/data \
	$(DEBUTILS_DIR)/data/data \
	$(DEBUTILS_DIR)/data/data/com.termux \
	$(DEBUTILS_DIR)/data/data/com.termux/files \
	$(DEBUTILS_DIR)/data/data/com.termux/files/usr \
	$(DEBUTILS_DIR)/data/data/com.termux/files/usr/bin \
	$(DEBUTILS_DIR)/data/data/com.termux/files/usr/share \
	$(DEBUTILS_DIR)/data/data/com.termux/files/usr/share/man \
	$(DEBUTILS_DIR)/data/data/com.termux/files/usr/share/man/man8

# for running make with silent mode
MAKE_HIDE := @ $(MAKE)
SILENT := -s
E := @ echo
E_NS := echo
P := printf

# color definations
RESET := \033[0m
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m

# end