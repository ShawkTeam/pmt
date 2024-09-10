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
# sub-make for building package
#####

THIS_IS = src

include ../Makefile.inc

ifeq ($(INC_OLDENV),true)
	include $(BUILD)/config/oldenv.mk
endif

INCLUDE_DIR := $(realpath ../include)
PMT_INCDIR := $(INCLUDE_DIR)/pmt

# the presence of all source files that are on this list will be checked
SRCS_REQ := \
	place-holder/Debug.cpp \
	place-holder/Help.cpp \
	place-holder/GetState.cpp \
	place-holder/LanguageTools.cpp \
	place-holder/Languages.cpp \
	place-holder/PartitionTool.cpp \
	place-holder/PartitionManager.cpp \
	place-holder/Root.cpp \
	place-holder/Tools.cpp \
	place-holder/Version.cpp

# objects to be used when executable file is created
OBJS_EXEC := \
	$(SOURCE_DIR)/Debug.o \
	$(SOURCE_DIR)/Root.o \
	$(SOURCE_DIR)/PartitionManager.o \
	$(SOURCE_DIR)/PartitionTool.o \
	$(SOURCE_DIR)/ListPartitions.o \
	$(SOURCE_DIR)/Help.o \
	$(SOURCE_DIR)/Version.o \
	$(SOURCE_DIR)/GetState.o \
	$(SOURCE_DIR)/Tools.o \
	$(SOURCE_DIR)/Languages.o \
	$(SOURCE_DIR)/LanguageTools.o

HEADERS_REQ := \
	$(PMT_INCDIR)/PartitionManager/Deprecates.h \
	$(PMT_INCDIR)/PartitionManager/HelpFn.h \
	$(PMT_INCDIR)/PartitionManager/PartitionManager.h \
	$(PMT_INCDIR)/PartitionManager/StringKeys.h \
	$(PMT_INCDIR)/PartitionManager/VersionFnVars.h

PROGRESS_LIST := \
	welcome \
	wait \
	$(SRCS_REQ) \
	$(HEADERS_REQ) \
	pr_obj \
	$(OBJS) \
	make_outdirs \
	make_executable \
	wait \
	end_progress

# all target for building
all: $(PROGRESS_LIST)

welcome:
	@ rm -f $(BUILD)/config/oldenv.mk
	@ echo " ---- Partition Manager Builder ---- " \
	&& $(E_NS)
	$(E) " - Version: $(VERSION)"
	$(E) " - Version code: $(VERSION_CODE)" \
	&& $(E_NS)
	$(E) "   -------------------------------- " \
	&& $(E_NS)
	$(E) " - Checking required source files..."

pr_obj:
	$(E) " - Building objects..."

wait:
	@ sleep 2

make_outdirs:
	@ rm -rf $(IN_OUT_DIR)
	@ mkdir -p $(BINARY_DIR)
	@ mkdir -p $(PACKAGE_DIR)

place-holder/%.cpp:
	$(E) "   CHK $(SOURCE_DIRNAME)/`basename $@`"
	@ if [ ! -f "$(SOURCE_DIR)/`basename $@`" ]; then \
		$(E_NS) "   ==> Couldn't found required source file: $(SOURCE_DIRNAME)/`basename $@`"; \
		exit 1; \
	fi

$(PMT_INCDIR)/%.h:
	$(E) "   CHK include/PartitionManager/`basename $@`"
	@ if [ ! -f "$(INCLUDE_DIR)/PartitionManager/`basename $@`" ]; then \
		$(E_NS) "   ==> Couldn't found required header file: include/PartitionManager/`basename $@`"; \
		exit 1; \
	fi

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.cpp
	$(E) "   CXX $(SOURCE_DIRNAME)/`basename $@`"
	@ $(CXX) -x c++ $(CXXFLAGS) -c "$<" || exit 1

make_executable:
	$(E) " - Making executable file..."
	$(E) "   LD  $(TARGET)"
	@ $(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS_EXEC) || exit 1

end_progress:
	@ abort_build() { \
		[ -d "$(PACKAGE_DIR)" ] \
		&& rm -rf "$(PACKAGE_DIR)"; \
		[ -d "$(BINARY_DIR)" ] \
		&& rm -rf "$(BINARY_DIR)"; \
		[ -d "$(STATICLIB_DIR)" ] \
		&& rm -rf "$(STATICLIB_DIR)"; \
		exit 1; \
	}; \
	mv $(TARGET) $(BINARY_DIR) || abort_build; \
	$(E_NS) " - Generating package..."; \
	cp $(BINARY_DIR)/$(TARGET) $(PACKAGE_DIR) || abort_build; \
	$(E_NS) "   XZ  $(OUT_DIRNAME)/package/$(TARGET)-`date +%Y%m%d`.xz"
	xz $(PACKAGE_DIR)/$(TARGET) || abort_build; \
	sleep 1; \
	mv $(PACKAGE_DIR)/$(TARGET).xz $(PACKAGE_DIR)/$(TARGET)-`date +%Y%m%d`.xz || abort_build
	$(E) " - Success" && $(E_NS)
	@ sleep 1
	$(E) " ----------------------------------- "

.PHONY: clean
clean:
	$(eval OBJS = $(wildcard $(SOURCE_DIR)/*.o))
	$(info Cleaning files...)
	$(foreach obj, \
	$(OBJS), \
	$(call m_stat_nn,$(SOURCE_DIRNAME)/$(shell basename $(obj))) \
	$(call erase,$(obj)) \
	)

# end