# By YZBruh

# Copyright 2024 Partition Manager
# 
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
# 
#	 http://www.apache.org/licenses/LICENSE-2.0
# 
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

########
# 3.0.2
########

LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE := libgnulib
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/lib/argmatch.c \
	$(LOCAL_PATH)/lib/basename-lgpl.c \
	$(LOCAL_PATH)/lib/basename.c \
	$(LOCAL_PATH)/lib/btowc.c \
	$(LOCAL_PATH)/lib/c-ctype.c \
	$(LOCAL_PATH)/lib/c-strcasecmp.c \
	$(LOCAL_PATH)/lib/c-strncasecmp.c \
	$(LOCAL_PATH)/lib/c32isprint.c \
	$(LOCAL_PATH)/lib/canonicalize-lgpl.c \
	$(LOCAL_PATH)/lib/cloexec.c \
	$(LOCAL_PATH)/lib/close-stream.c \
	$(LOCAL_PATH)/lib/closeout.c \
	$(LOCAL_PATH)/lib/dirname-lgpl.c \
	$(LOCAL_PATH)/lib/dirname.c \
	$(LOCAL_PATH)/lib/error.c \
	$(LOCAL_PATH)/lib/exitfail.c \
	$(LOCAL_PATH)/lib/fcntl.c \
	$(LOCAL_PATH)/lib/free.c \
	$(LOCAL_PATH)/lib/getdtablesize.c \
	$(LOCAL_PATH)/lib/hard-locale.c \
	$(LOCAL_PATH)/lib/ialloc.c \
	$(LOCAL_PATH)/lib/iswctype.c \
	$(LOCAL_PATH)/lib/iswdigit.c \
	$(LOCAL_PATH)/lib/iswpunct.c \
	$(LOCAL_PATH)/lib/iswxdigit.c \
	$(LOCAL_PATH)/lib/localcharset.c \
	$(LOCAL_PATH)/lib/long-options.c \
	$(LOCAL_PATH)/lib/malloca.c \
	$(LOCAL_PATH)/lib/mbrtoc32.c \
	$(LOCAL_PATH)/lib/mbrtowc.c \
	$(LOCAL_PATH)/lib/mbszero.c \
	$(LOCAL_PATH)/lib/nl_langinfo.c \
	$(LOCAL_PATH)/lib/progname.c \
	$(LOCAL_PATH)/lib/quotearg.c \
	$(LOCAL_PATH)/lib/rawmemchr.c \
	$(LOCAL_PATH)/lib/regex.c \
	$(LOCAL_PATH)/lib/rpmatch.c \
	$(LOCAL_PATH)/lib/safe-read.c \
	$(LOCAL_PATH)/lib/setlocale-lock.c \
	$(LOCAL_PATH)/lib/setlocale_null-unlocked.c \
	$(LOCAL_PATH)/lib/setlocale_null.c \
	$(LOCAL_PATH)/lib/stat-time.c \
	$(LOCAL_PATH)/lib/stripslash.c \
	$(LOCAL_PATH)/lib/tempname.c \
	$(LOCAL_PATH)/lib/version-etc-fsf.c \
	$(LOCAL_PATH)/lib/version-etc.c \
	$(LOCAL_PATH)/lib/wctype.c \
	$(LOCAL_PATH)/lib/unictype/ctype_print.c \
	$(LOCAL_PATH)/lib/xalloc-die.c \
	$(LOCAL_PATH)/lib/xmalloc.c \
	$(LOCAL_PATH)/lib/xstrtol.c \
	$(LOCAL_PATH)/lib/xstrtoll.c \
	$(LOCAL_PATH)/lib/xstrtoul.c \
	$(LOCAL_PATH)/lib/xstrtoull.c
LOCAL_C_INCLUDES := \
	$(LOCAL_PATH)/../../../include/libgnulib \
	$(LOCAL_PATH)/../../../include \
	$(LOCAL_PATH)/../lib \
	$(LOCAL_PATH)/lib
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-Wno-nullability-completeness \
	-Wno-macro-redefined \
	-fPIC \
	-include $(LOCAL_PATH)/../../include/PartitionManager/Alternatives.h

include $(BUILD_STATIC_LIBRARY)