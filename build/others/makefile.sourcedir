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

# make objects. Usage $(call make_obj,<SRCFILE>)
define make_obj
	$(eval OBJ := $(1:.c=.o))
	$(call m_stat,CC,`basename $(SOURCE_DIR)`/`basename $(OBJ)`,n)
	$(CC) $(CFLAGS) -c "$1" || exit 1;
	$(hide)printf "\n"
endef

# make executable file with using static libraries and objects. Usage: $(call make_executable)
define make_executable
	printf " - Making executable file...\n"; \
	printf "   LD  $(TARGET)"; \
	$(CC) $(CFLAGS) -L$(SOURCE_DIR) \
	$(foreach s_obj_b, \
	$(shell basename -a $(STATICLIB_OBJS)), \
	$(eval s_obj_t_b = $(s_obj_b:.o=)) \
	$(shell echo -lpmt_$(s_obj_t_b)) \
	) \
	-o $(TARGET) $(OBJS_EXEC) || exit 1;
endef

# make static library. Usage $(call make_staticlib,<LIBRARY_NAME>,<OBJECT(S)>)
define make_staticlib
	echo -n "   AR  $1"; \
	$(AR) rcs "$1" "$2" || exit 1; \
	echo;
endef

# controls the presence of source file. usage: $(call check_cfile,<SOURCE_FILE>)
define check_cfile
	# the first argument is taken and controlled by the file with -f option
	printf "   CHK src/`basename $1`\n"; \
	if [ ! -f $1 ]; then \
		printf "   ==> Couldn't found required source file: src/`basename $1`\n"; \
		if [ -d "$(TEMP_DIR)" ]; then \
			rm -rf $(TEMP_DIR); \
		fi; \
		exit 1; \
	fi;
endef

# controls the presence of header file. usage: $(call check_hfile,<SOURCE_FILE>)
define check_hfile
	# the first argument is taken and controlled by the file with -f option
	printf "   CHK include/pmt/`basename $1`\n"; \
	if [ ! -f $1 ]; then \
		printf "   ==> Couldn't found required header file: include/pmt/`basename $1`\n"; \
		if [ -d "$(TEMP_DIR)" ]; then \
			rm -rf $(TEMP_DIR); \
		fi; \
		exit 1; \
	fi;
endef

# all target for building
all:
	$(hide)rm -f $(BUILD)/config/oldenv.mk
	$(hide)printf " ---- Partition Manager Builder ---- \n\n"
	$(hide)printf " - Version: $(VERSION)\n"
	$(hide)printf " - Version code: $(VERSION_CODE)\n\n"
	$(hide)printf "   --------------------------------   \n\n"
	$(hide)if [ -f $(SOURCE_DIR)/debugging.o ]; then \
		printf " - Please clean up before you build it.\n\n"; \
		printf " ----------------------------------- \n"; \
		exit 1; \
	fi
	$(hide)printf " - Checking required source files...\n"
	$(hide)sleep 1
	$(foreach src_cf, \
	$(SRCS_REQ), \
	$(call check_cfile,$(src_cf)) \
	)
	$(foreach src_hf, \
	$(HEADERS_REQ), \
	$(call check_hfile,$(src_hf)) \
	)
	$(hide)printf " - Building objects...\n"
	$(hide)sleep 2
	$(foreach csrc, \
	$(SRCS), \
	$(call make_obj,$(csrc)) \
	)
	$(foreach reqdir,$(IN_OUT_DIR),$(call mdir,$(reqdir)))
	$(hide)printf " - Making static libraries...\n"
	$(foreach s_obj, \
	$(shell basename -a $(STATICLIB_OBJS)), \
	$(eval s_obj_t = $(s_obj:.o=.a)) \
	$(call make_staticlib,libpmt_$(s_obj_t),$(s_obj)) \
	)
	$(hide)sleep 1
	$(call make_executable)
	$(hide)sleep 1
	$(hide)abort_build() { \
		if [ -d "$(PACKAGE_DIR)" ]; then \
			rm -rf "$(PACKAGE_DIR)"; \
		fi; \
		if [ -d "$(BINARY_DIR)" ]; then \
			rm -rf "$(BINARY_DIR)"; \
		fi; \
		if [ -d "$(STATICLIB_DIR)" ]; then \
			rm -rf "$(STATICLIB_DIR)"; \
		fi; \
		exit 1; \
	}; \
	mv $(TARGET) $(BINARY_DIR) || abort_build; \
	mv *.a $(STATICLIB_DIR) || abort_build; \
	printf "\n - Generating package...\n"; \
	cp $(BINARY_DIR)/$(TARGET) $(PACKAGE_DIR) || abort_build; \
	printf "   XZ  $(OUT_DIRNAME)/package/$(TARGET)-$(ARCH).xz"
	xz $(PACKAGE_DIR)/$(TARGET) || abort_build; \
	sleep 1; \
	mv $(PACKAGE_DIR)/$(TARGET).xz $(PACKAGE_DIR)/$(TARGET)-$(ARCH).xz || abort_build; \
	printf "\n - Success"; \
	sleep 1; \
	printf "\n\n ----------------------------------- \n"

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