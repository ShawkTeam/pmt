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

LOCAL_MODULE := libcharset
LOCAL_SRC_FILES := \
	$(LOCAL_PATH)/lib/localcharset.c \
	$(LOCAL_PATH)/lib/relocatable-stub.c
LOCAL_C_INCLUDES := $(LOCAL_PATH)/../../../include/libcharset
LOCAL_CFLAGS := \
	-Wall \
	-Wextra \
	-Wno-sign-compare \
	-Wno-unused-const-variable \
	-Wno-unused-parameter \
	-fPIC \
	-g \
	-fvisibility=hidden

include $(BUILD_STATIC_LIBRARY)