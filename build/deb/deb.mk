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
	SUDO := su
else ifeq ($(wildcard /system/build.prop),)
	SUDO := sudo
else
	SUDO := 
endif

# controls the presence of file/directory. usage: $(call check_local,<FILE_OR_DIRECTORY_PATH>,<PACKAGE_STAT: 1, NULL>)
define check_local
	# the first argument is taken and controlled by the file/directory with -e option
	if [ ! -e $1 ]; then \
		if [ $2 = 1 ]; then \
			printf " - Package not builded! Please build package and try again.\n"; \
		else \
			printf "   ==> Not found: $1\n"; \
		fi; \
		if [ -d "$(TEMP_DIR)" ]; then \
			rm -rf $(TEMP_DIR); \
		fi; \
		exit 1; \
	fi;
endef

# make deb package
all:
	$(hide)printf " --------- Making deb package ---------\n"
	# remove template directory
	$(call erase,$(TEMP_DIR))
	$(hide)printf " - Checking files and directories (only neededs)...\n"
	# check some files and directories with parsing DEB_CHECKS variable
	$(foreach deb_chfile, \
	$(DEB_CHECKS), \
	$(call check_local,$(deb_chfile)) \
	)
	# check build status
	$(call check_local, \
	$(BINARY_DIR)/pmt, \
	1 \
	)
	# make template and output directories
	$(call mdir,$(TEMP_DIR),"y")
	$(call mdir,$(DEB_DIR),"y")
	$(hide)printf " - Copying files...\n"
	# prepare
	$(hide)cp -r $(DEBUTILS_DIR)/data $(TEMP_DIR) || exit 1
	$(hide)rm -f $(DEBTERMUX_USR)/share/man/man8/dummy
	$(hide)rm -f $(DEBTERMUX_USR)/bin/dummy
	$(call mdir,$(TEMP_DIR)/DEBIAN)
	$(hide)abort() { \
		if [ -d $(TEMP_DIR) ]; then \
			rm -rf $(TEMP_DIR); \
		fi; \
		if [ -d $(DEB_DIR) ]; then \
			rm -rf $(DEB_DIR); \
		fi; \
		exit 1; \
	}; \
	if [ ! "$(FOR_THIS)" = "64" ] && [ ! "$(FOR_THIS)" = "32" ]; then \
		printf " - İnvalid arch number: $(FOR_THIS)\n" && abort; \
	fi; \
	printf " - Selected arm-$(FOR_THIS) package control file.\n"; \
	cp $(DEBUTILS_DIR)/DEBIAN/control_$(FOR_THIS) $(TEMP_DIR)/DEBIAN/control || abort; \
	cp $(DEBUTILS_DIR)/mandoc/$(TARGET).8.gz $(DEBTERMUX_USR)/share/man/man8 || abort; \
	cp $(BINARY_DIR)/$(TARGET) $(DEBTERMUX_USR)/bin || abort; \
	printf " - Starting dpkg-deb...\n"; \
	sleep 2; \
	$(SUDO) chmod -R 755 *; \
	dpkg-deb -b $(TEMP_DIR) $(DEB_DIR)/$(TARGET)-$(DEB_ARCH_NAME).deb || abort; \
	# cleanup template directory
	rm -rf $(TEMP_DIR); \
	printf " - Done!\n"

# end
