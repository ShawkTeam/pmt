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
# sub-make for making deb package
#####

THIS_IS := debutils

# include needed variables
include ../../Makefile.inc

TEMP_DIR := $(DEBUTILS_DIR)/template

ifeq ($(FOR_THIS),64)
	DEB_ARCH_NAME := arm64-v8a
else ifeq ($(FOR_THIS),32)
	DEB_ARCH_NAME := armeabi-v7a
endif

ifneq ($(wildcard /dev/block/by-name),)
	SUDO := su -c
else ifeq ($(wildcard /system/build.prop),)
	SUDO := sudo
else
	SUDO := 
endif

PROGRESS_LIST := \
	startup \
	$(DEB_CHECKS) \
	check_binary \
	prepare \
	make_debian_pack

# make deb package
all: $(PROGRESS_LIST)

startup:
	$(E) " --------- Making deb package --------- "
	@ rm -rf $(TEMP_DIR)
	$(E) " - Checking files and directories (only neededs)..."

prepare:
	$(E) " - Copying files..."
	@ cp -r $(DEBUTILS_DIR)/data $(TEMP_DIR) || exit 1
	@ rm -f $(DEBTERMUX_USR)/share/man/man8/dummy
	@ rm -f $(DEBTERMUX_USR)/bin/dummy
	@ mkdir $(TEMP_DIR)/DEBIAN

check_binary:
	@ if [ ! -f "$(BINARY_DIR)/pmt" ]; then \
		$(E_NS) " - pmt not builded! Please build and retry."; \
		exit 1; \
	fi
	$(E) " - Generating template directory..."
	@ mkdir $(TEMP_DIR)
	$(E) " - Generating debian package directory..."
	@ mkdir $(DEB_DIR)

make_debian_pack:
	@ abort() { \
		[ -d $(TEMP_DIR) ] \
		&& rm -rf $(TEMP_DIR); \
		[ -d $(DEB_DIR) ] \
		&& rm -rf $(DEB_DIR); \
		exit 1; \
	}; \
	if [ ! "$(FOR_THIS)" = "64" ] && [ ! "$(FOR_THIS)" = "32" ]; then \
		$(E_NS) " - Invalid arch number: $(FOR_THIS) [maybe null]" && abort; \
	fi; \
	$(E_NS) " - Selected arm-$(FOR_THIS) package control file."; \
	cp $(DEBUTILS_DIR)/DEBIAN/control_$(FOR_THIS) $(TEMP_DIR)/DEBIAN/control || abort; \
	cp $(DEBUTILS_DIR)/mandoc/$(TARGET).8.gz $(DEBTERMUX_USR)/share/man/man8 || abort; \
	cp $(BINARY_DIR)/$(TARGET) $(DEBTERMUX_USR)/bin || abort; \
	$(E_NS) " - Starting dpkg-deb..."; \
	sleep 2; \
	$(SUDO) chmod -R 755 *; \
	dpkg-deb -b $(TEMP_DIR) $(DEB_DIR)/$(TARGET)-$(DEB_ARCH_NAME).deb || abort; \
	rm -rf $(TEMP_DIR); \
	$(E_NS) " - Done!"

$(DEBUTILS_DIR)/%:
	@ [ ! -e "$@" ] && $(E_NS) " - Check failed! Not found: $@" && exit 1

# end
