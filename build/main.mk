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

UPDATE_MAKEFILES = false

all:
	$(hide)# To save configuration, the makefile in the config directory
	$(MAKE_HIDE) $(SILENT) -C $(BUILD)/config || exit 1
	$(hide)# start the main build process
	$(MAKE_HIDE) $(SILENT) -C $(SOURCE_DIRNAME) INC_OLDENV=true || exit 1

# cleaner functions
.PHONY: clean
clean:
	$(hide)printf "Cleaning directories...\n"; \
	# cleanup out/binary
	$(hide)if [ -d $(BINARY_DIR) ]; then \
		printf "==> $(OUT_DIRNAME)/`basename $(BINARY_DIR)`\n"; \
		rm -rf "$(BINARY_DIR)"; \
	fi; \
	# cleanup out/package
	$(hide)if [ -d $(PACKAGE_DIR) ]; then \
		printf "==> $(OUT_DIRNAME)/`basename $(PACKAGE_DIR)`\n"; \
		rm -rf "$(PACKAGE_DIR)"; \
	fi; \
	# cleanup out/static_libs
	$(hide)if [ -d $(STATICLIB_DIR) ]; then \
		printf "==> $(OUT_DIRNAME)/`basename $(STATICLIB_DIR)`\n"; \
		rm -rf "$(STATICLIB_DIR)"; \
	fi; \
	# cleanup out/debpackage
	$(hide)if [ -d $(DEB_DIR) ]; then \
		printf "==> $(OUT_DIRNAME)/`basename $(DEB_DIR)`\n"; \
		rm -rf "$(DEB_DIR)"; \
	fi; \
	sleep 2; \
	# clean the objects by calling the receipt in the source directory
	$(MAKE_HIDE) $(SILENT) -C $(SOURCE_DIRNAME) clean INC_OLDENV=false || exit 1
	$(hide)sleep 1
	$(hide)printf "Success.\n"

# helper function
.PHONY: help
help:
	$(hide)printf " ------- Partition Manager help -------\n\n"
	$(hide)printf " Commands:\n"
	$(hide)printf "    $(MAKE)                       ==>  Build Partition Manager.\n"
	$(hide)printf "    $(MAKE) deb                   ==>  Generate debian package for termux.\n"
	$(hide)printf "    $(MAKE) clean                 ==>  Clear builded binary.\n"
	$(hide)printf "    $(MAKE) install               ==>  It installs $(TARGET) into termux.\n"
	$(hide)printf "    $(MAKE) uninstall             ==>  It uninstalls $(TARGET) into termux.\n"
	$(hide)printf "    $(MAKE) gen-makefiles         ==>  Generate makefiles for build.\n"
	$(hide)printf "    $(MAKE) gen-ndk-makefiles     ==>  Generate NDK makefiles for build.\n"
	$(hide)printf "    $(MAKE) clean-makefiles       ==>  Cleanup makefiles.\n"
	$(hide)printf "    $(MAKE) clean-ndk-makefiles   ==>  Cleanup NDK makefiles.\n"
	$(hide)printf "    $(MAKE) update-makefiles      ==>  Re-generate makefiles.\n"
	$(hide)printf "    $(MAKE) update-ndk-makefiles  ==>  Re-generate NDK makefiles.\n"
	$(hide)printf "    $(MAKE) help                  ==>  Display this help message.\n\n"

# deb maker
.PHONY: deb
deb:
	$(MAKE_HIDE) $(SILENT) -C $(DEBUTILS_DIR) -f deb.mk FOR_THIS=$(FOR_THIS) || exit 1
	$(hide)printf ""

# install pmt in to termux
.PHONY: install
install:
	$(MAKE_HIDE) $(SILENT) -C $(OUT_DIRNAME) install || exit 1

# uninstall pmt in to termux
.PHONY: uninstall
uninstall:
	$(MAKE_HIDE) $(SILENT) -C $(OUT_DIRNAME) uninstall || exit 1

# clean ndk makefiles
.PHONY: gen-ndk-makefiles
gen-ndk-makefiles:
	$(eval NDK_PROG = true)
	$(call save-gen-vars)
	$(call gen-ndk-mfiles)
	$(hide)printf ""

.PHONY: gen-makefiles
gen-makefiles:
	$(call save-gen-vars)
	$(call gen-mfiles)
	$(hide)printf ""

.PHONY: update-ndk-makefiles
update-ndk-makefiles:
	$(hide)printf " ------ Updating NDK makefiles ------ \n"
	$(eval NDK_PROG = true)
	$(eval UPDATE_MAKEFILES = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	$(call gen-ndk-mfiles)
	$(hide)printf ""

.PHONY: update-makefiles
update-makefiles:
	$(hide)printf " ------ Updating makefiles ------ \n"
	$(eval UPDATE_MAKEFILES = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	$(call gen-mfiles)
	$(hide)printf ""

.PHONY: clean-ndk-makefiles
clean-ndk-makefiles:
	$(eval NDK_PROG = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	$(hide)printf ""

.PHONY: clean-makefiles
clean-makefiles:
	$(call save-gen-vars)
	$(call clean-mfiles)
	$(hide)printf ""

# end