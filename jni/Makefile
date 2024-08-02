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
	place-holder/debug.c \
	place-holder/help.c \
	place-holder/get_stat.c \
	place-holder/lang_tools.c \
	place-holder/languages.c \
	place-holder/partitiontool.c \
	place-holder/pmt.c \
	place-holder/root.c \
	place-holder/tools.c \
	place-holder/version.c

# objects to be used when executable file is created
OBJS_EXEC := \
	$(SOURCE_DIR)/$(TARGET).o \
	$(SOURCE_DIR)/help.o \
	$(SOURCE_DIR)/version.o \
	$(SOURCE_DIR)/get_stat.o \
	$(SOURCE_DIR)/tools.o \
	$(SOURCE_DIR)/lang_tools.o \
	$(SOURCE_DIR)/languages.o

HEADERS_REQ := \
	$(PMT_INCDIR)/pmt/ExternC.h \
	$(PMT_INCDIR)/pmt/Deprecates.h \
	$(PMT_INCDIR)/pmt/HelpMessages.h \
	$(PMT_INCDIR)/pmt/PartitionManager.h \
	$(PMT_INCDIR)/pmt/StringKeys.h \
	$(PMT_INCDIR)/pmt/VersionVars.h

PROGRESS_LIST := \
	welcome \
	wait \
	$(SRCS_REQ) \
	$(HEADERS_REQ) \
	pr_obj \
	$(OBJS) \
	make_outdirs \
	pr_sts \
	$(STATIC_LIBS) \
	make_executable \
	wait \
	end_progress

define check_hf
	@ [ ! -f "$1" ] \
	&& $(E_NS) "   ==> Couldn't found required header file: include/pmt/`basename $1`" \
	&& exit 1
endef

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
	@ if [ -f $(SOURCE_DIR)/debug.o ]; then \
		$(E_NS) " - Please clean up before you build it." && echo; \
		$(E_NS) " ----------------------------------- "; \
		exit 1; \
	fi
	$(E) " - Checking required source files..."

pr_obj:
	$(E) " - Building objects..."

pr_sts:
	$(E) " - Making static libraries..."

wait:
	@ sleep 2

make_outdirs:
	@ rm -rf $(IN_OUT_DIR)
	@ mkdir $(BINARY_DIR)
	@ mkdir $(PACKAGE_DIR)
	@ mkdir $(STATICLIB_DIR)

place-holder/%.c:
	$(E) "   CHK $(SOURCE_DIRNAME)/`basename $@`"
	@ if [ ! -f "$(SOURCE_DIR)/`basename $@`" ]; then \
		$(E_NS) "   ==> Couldn't found required source file: $(SOURCE_DIRNAME)/`basename $@`"; \
		exit 1; \
	fi

$(PMT_INCDIR)/%.h:
	$(E) "   CHK include/pmt/`basename $@`"
	@ if [ ! -f "$(INCLUDE_DIR)/pmt/`basename $@`" ]; then \
		$(E_NS) "   ==> Couldn't found required header file: include/pmt/`basename $@`"; \
		exit 1; \
	fi

$(SOURCE_DIR)/%.o: $(SOURCE_DIR)/%.c
	$(E) "   CC  $(SOURCE_DIRNAME)/`basename $@`"
	@ $(CC) $(CFLAGS) -c "$<" || exit 1

$(TARGET)_%:
	$(E) "   AR  lib$@.a"
	@ $(AR) rcs "lib$@.a" "$(SOURCE_DIR)/$$(echo "$@" | cut -d'_' -f2).o"

make_executable:
	$(E) " - Making executable file..."
	$(E) "   LD  $(TARGET)"
	@ $(CC) $(CFLAGS) -L$(SOURCE_DIR) $(foreach st,$(STATIC_LIBS),$(shell echo -n -l$(st) )) -o $(TARGET) $(OBJS_EXEC) || exit 1

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
	mv *.a $(STATICLIB_DIR) || abort_build; \
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
	$(eval STATICLIBS = $(wildcard $(SOURCE_DIR)/*.a))
	$(eval OBJS = $(wildcard $(SOURCE_DIR)/*.o))
	$(info Cleaning files...)
	$(foreach obj, \
	$(OBJS), \
	$(call m_stat_nn,$(SOURCE_DIRNAME)/$(shell basename $(obj))) \
	$(call erase,$(obj)) \
	)
	$(foreach lib, \
	$(STATICLIBS), \
	$(call m_stat_nn,$(SOURCE_DIRNAME)/$(shell basename $(lib))) \
	$(call erase,$(lib)) \
	)

# end