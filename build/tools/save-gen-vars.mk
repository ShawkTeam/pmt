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

define save-gen-vars
	$(hide)rm -f $(BASH_DIR)/additional-vars
	$(call touch,$(BASH_DIR)/additional-vars)
	$(hide)echo "NDK_PROG=$(NDK_PROG)" >> $(BASH_DIR)/additional-vars
	$(hide)echo "FORCE_GEN=$(FORCE_GEN)" >> $(BASH_DIR)/additional-vars
	$(hide)echo "THIS_IS=$(THIS_IS)" >> $(BASH_DIR)/additional-vars
	$(hide)echo "UPDATE_MAKEFILES=$(UPDATE_MAKEFILES)" >> $(BASH_DIR)/additional-vars
	$(hide)echo "SOURCE_DIRNAME=$(SOURCE_DIRNAME)" >> $(BASH_DIR)/additional-vars
	$(hide)echo "OUT_DIRNAME=$(OUT_DIRNAME)" >> $(BASH_DIR)/additional-vars
endef
