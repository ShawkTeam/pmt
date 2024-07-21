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

##################
# See "erase" funtion for build/util/utils.mk
##################

include $(TOOLS)/save-gen-vars.mk

define clean-ndk-mfiles
	$(hide)[ "$(UPDATE_MAKEFILES)" = "true" ] || printf " ------ Cleaning NDK Makefiles ------ \n"
	$(hide)cat $(BASH_DIR)/clean-makefiles | $(BIN)/bash
endef

define clean-mfiles
	$(hide)[ "$(UPDATE_MAKEFILES)" = "true" ] || printf " ------ Cleaning Makefiles ------ \n"
	$(hide)cat $(BASH_DIR)/clean-makefiles | $(BIN)/bash
endef