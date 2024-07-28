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
	place-holder/debugging.c \
	place-holder/help.c \
	place-holder/get_stat.c \
	place-holder/lang_tools.c \
	place-holder/languages.c \
	place-holder/partitiontool.c \
	place-holder/pmt.c \
	place-holder/root.c \
	place-holder/tools.c \
	place-holder/versioning.c

# objects to be used when executable file is created
OBJS_EXEC := \
	$(SOURCE_DIR)/$(TARGET).o \
	$(SOURCE_DIR)/help.o \
	$(SOURCE_DIR)/versioning.o \
	$(SOURCE_DIR)/get_stat.o \
	$(SOURCE_DIR)/tools.o \
	$(SOURCE_DIR)/lang_tools.o \
	$(SOURCE_DIR)/languages.o

HEADERS_REQ := \
	$(PMT_INCDIR)/pmt/deprecates.h \
	$(PMT_INCDIR)/pmt/help_msgs.h \
	$(PMT_INCDIR)/pmt/pmt.h \
	$(PMT_INCDIR)/pmt/stringkeys.h \
	$(PMT_INCDIR)/pmt/versioning.h

PROGRESS_LIST := \
	welcome \
	$(SRCS_REQ) \
	$(HEADERS_REQ) \
	pr_obj \
	$(OBJS) \
	make_outdirs \
	$(STATIC_LIBS) \
	make_executable \
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
	@ if [ -f $(SOURCE_DIR)/debugging.o ]; then \
		$(E_NS) " - Please clean up before you build it." && echo; \
		$(E_NS) " ----------------------------------- "; \
		exit 1; \
	fi
	$(E) " - Checking required source files..."
	@ sleep 1

pr_obj:
	$(E) " - Building objects..."

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
	$(eval GEN_OBJS_MSG = )

lib$(TARGET)_root.a:
	$(E) " - Making static libraries..."
	$(E) "   AR  $@"
	@ $(AR) rcs "$@" "$(SOURCE_DIR)/root.o" || exit 1

lib$(TARGET)_debugging.a:
	$(E) "   AR  $@"
	@ $(AR) rcs "$@" "$(SOURCE_DIR)/debugging.o"

lib$(TARGET)_listpart.a:
	$(E) "   AR  $@"
	@ $(AR) rcs "$@" "$(SOURCE_DIR)/listpart.o"

lib$(TARGET)_partitiontool.a:
	$(E) "   AR  $@"
	@ $(AR) rcs "$@" "$(SOURCE_DIR)/partitiontool.o"
	@ sleep 1

make_executable:
	$(E) " - Making executable file..."
	$(E) "   LD  $(TARGET)"
	@ $(CC) $(CFLAGS) -L$(SOURCE_DIR) -l$(TARGET)_root -l$(TARGET)_debugging -l$(TARGET)_listpart -l$(TARGET)_partitiontool -o $(TARGET) $(OBJS_EXEC) || exit 1
	@ sleep 1

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