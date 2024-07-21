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
VERSION := 2.5.0
VERSION_CODE := 250
TARGET := pmt

# device arch info
ARCH := $(shell uname -m)

# current directory
CUR_DIR = $(shell pwd)
OUT_DIRNAME ?= out
SOURCE_DIRNAME ?= jni

# others needed important variables
ifeq ($(THIS_IS),src)
	BUILD := ../build
	SOURCE_DIR := $(CUR_DIR)
	OUT_DIR := ../$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
	INCLUDE_DIR := ../include
else ifeq ($(THIS_IS),debutils)
	BUILD := ..
	SOURCE_DIR := ../../$(SOURCE_DIRNAME)
	OUT_DIR := ../../$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
else ifeq ($(THIS_IS),out)
	BUILD := ../build
	SOURCE_DIR := ../$(SOURCE_DIRNAME)
	OUT_DIR := $(CUR_DIR)
	DEBUTILS_DIR := $(BÜILD)/deb
else ifeq ($(THIS_IS),main)
	BUILD := $(CUR_DIR)/build
	SOURCE_DIR := $(CUR_DIR)/$(SOURCE_DIRNAME)
	OUT_DIR := $(CUR_DIR)/$(OUT_DIRNAME)
	DEBUTILS_DIR := $(BUILD)/deb
endif

BINARY_DIR := $(OUT_DIR)/binary
PACKAGE_DIR := $(OUT_DIR)/package
STATICLIB_DIR := $(OUT_DIR)/static_libs
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
SRCS := $(wildcard $(SOURCE_DIR)/*.c)
OBJS = $(SRCS:.c=.o)

# the presence of all source files that are on this list will be checked
SRCS_REQ := \
	$(SOURCE_DIR)/debugging.c \
	$(SOURCE_DIR)/docs.c \
	$(SOURCE_DIR)/get_stat.c \
	$(SOURCE_DIR)/lang_tools.c \
	$(SOURCE_DIR)/languages.c \
	$(SOURCE_DIR)/partitiontool.c \
	$(SOURCE_DIR)/pmt.c \
	$(SOURCE_DIR)/root.c \
	$(SOURCE_DIR)/tools.c \
	$(SOURCE_DIR)/versioner.c

ifeq ($(THIS_IS),src)
	HEADERS_REQ := \
		$(INCLUDE_DIR)/pmt/deprecates.h \
		$(INCLUDE_DIR)/pmt/docs.h \
		$(INCLUDE_DIR)/pmt/pmt.h \
		$(INCLUDE_DIR)/pmt/stringkeys.h \
		$(INCLUDE_DIR)/pmt/versioning.h
endif

# objects to be used wgen static library files is created
STATICLIB_OBJS := \
	$(SOURCE_DIR)/root.o \
	$(SOURCE_DIR)/debugging.o \
	$(SOURCE_DIR)/listpart.o \
	$(SOURCE_DIR)/partitiontool.o

# objects to be used when executable file is created
OBJS_EXEC := \
	$(SOURCE_DIR)/$(TARGET).o \
	$(SOURCE_DIR)/docs.o \
	$(SOURCE_DIR)/versioner.o \
	$(SOURCE_DIR)/get_stat.o \
	$(SOURCE_DIR)/tools.o \
	$(SOURCE_DIR)/lang_tools.o \
	$(SOURCE_DIR)/languages.o

# other directories in the out directory
IN_OUT_DIR := \
	$(BINARY_DIR) \
	$(PACKAGE_DIR) \
	$(STATICLIB_DIR)

# list of file/directory to be checked when the deb pack is created
DEB_CHECKS := \
	$(DEBUTILS_DIR) \
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
hide := @
MAKE_HIDE := $(hide)$(MAKE)
SILENT := -s

# color definations
RESET := \033[0m
RED := \033[0;31m
GREEN := \033[0;32m
YELLOW := \033[0;33m

# end