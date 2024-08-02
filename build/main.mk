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
CLS_ADTS := "rm -f $(BUILD)/bash/additional-vars"

all:
	$(MAKE_HIDE) $(SILENT) -C $(BUILD)/config || exit 1
	$(MAKE_HIDE) $(SILENT) -C $(SOURCE_DIRNAME) INC_OLDENV=true || exit 1

# cleaner functions
.PHONY: clean
clean:
	$(E) "Cleaning directories..."
	@ if [ -d $(BINARY_DIR) ]; then \
		$(E_NS) "==> $(OUT_DIRNAME)/`basename $(BINARY_DIR)`"; \
	fi
	@ if [ -d $(PACKAGE_DIR) ]; then \
		$(E_NS) "==> $(OUT_DIRNAME)/`basename $(PACKAGE_DIR)`"; \
	fi
	@ if [ -d $(STATICLIB_DIR) ]; then \
		$(E_NS) "==> $(OUT_DIRNAME)/`basename $(STATICLIB_DIR)`"; \
	fi
	@ if [ -d $(DEB_DIR) ]; then \
		$(E_NS) "==> $(OUT_DIRNAME)/`basename $(DEB_DIR)`"; \
	fi
	@ rm -rf $(IN_OUT_DIR)
	@ rm -rf $(DEB_DIR)
	@ sleep 2
	$(MAKE_HIDE) $(SILENT) -C $(SOURCE_DIRNAME) clean INC_OLDENV=false || exit 1
	@ sleep 1
	$(E) "Success."

# helper function
.PHONY: help
help:
	$(E) " ------- Partition Manager help ------- " \
	&& $(E_NS)
	$(E) " Commands:"
	$(E) "    $(MAKE)                       ==>  Build Partition Manager."
	$(E) "    $(MAKE) deb                   ==>  Generate debian package for termux."
	$(E) "    $(MAKE) clean                 ==>  Clear builded binary."
	$(E) "    $(MAKE) install               ==>  It installs $(TARGET) into termux."
	$(E) "    $(MAKE) uninstall             ==>  It uninstalls $(TARGET) into termux."
	$(E) "    $(MAKE) gen-makefiles         ==>  Generate makefiles for build."
	$(E) "    $(MAKE) gen-ndk-makefiles     ==>  Generate NDK makefiles for build."
	$(E) "    $(MAKE) clean-makefiles       ==>  Cleanup makefiles."
	$(E) "    $(MAKE) clean-ndk-makefiles   ==>  Cleanup NDK makefiles."
	$(E) "    $(MAKE) update-makefiles      ==>  Re-generate makefiles."
	$(E) "    $(MAKE) update-ndk-makefiles  ==>  Re-generate NDK makefiles."
	$(E) "    $(MAKE) help                  ==>  Display this help message." && $(E_NS)

# deb maker
.PHONY: deb
deb:
	$(MAKE_HIDE) $(SILENT) -C $(DEBUTILS_DIR) -f deb.mk FOR_THIS=$(FOR_THIS) || exit 1
	$(P) ""

# install pmt in to termux
.PHONY: install
install:
	$(eval PROG := $@)
	$(MAKE_HIDE) $(SILENT) -C $(OUT_DIRNAME) install PROG=$(PROG) || exit 1

# uninstall pmt in to termux
.PHONY: uninstall
uninstall:
	$(eval PROG := $@)
	$(MAKE_HIDE) $(SILENT) -C $(OUT_DIRNAME) uninstall PROG=$(PROG) || exit 1

# clean ndk makefiles
.PHONY: gen-ndk-makefiles
gen-ndk-makefiles:
	$(eval NDK_PROG = true)
	$(call save-gen-vars)
	$(call gen-ndk-mfiles)
	@ $(CLS_ADTS)

.PHONY: gen-makefiles
gen-makefiles:
	$(call save-gen-vars)
	$(call gen-mfiles)
	@ $(CLS_ADTS)

.PHONY: update-ndk-makefiles
update-ndk-makefiles:
	$(E) " ------ Updating NDK makefiles ------ "
	$(eval NDK_PROG = true)
	$(eval UPDATE_MAKEFILES = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	$(call gen-ndk-mfiles)
	@ $(CLS_ADTS)

.PHONY: update-makefiles
update-makefiles:
	$(E) " ------ Updating makefiles ------ "
	$(eval UPDATE_MAKEFILES = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	$(call gen-mfiles)
	@ $(CLS_ADTS)

.PHONY: clean-ndk-makefiles
clean-ndk-makefiles:
	$(eval NDK_PROG = true)
	$(call save-gen-vars)
	$(call clean-ndk-mfiles)
	@ $(CLS_ADTS)

.PHONY: clean-makefiles
clean-makefiles:
	$(call save-gen-vars)
	$(call clean-mfiles)
	@ $(CLS_ADTS)

# end
