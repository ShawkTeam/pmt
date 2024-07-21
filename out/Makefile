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
# sub-make for installing-uninstalling
#####

THIS_IS := out

# include needed variables
include ../Makefile.inc
-include $(BUILD)/config/INS_STAT.mk
-include $(BUILD)/config/UNINS_STAT.mk

# create an empty target
all:
	$(hide)printf ""

# installer
.PHONY: install
install:
	# really termux?
	$(hide)if [ -f $(TERMUX_BIN)/termux-open ]; then \
		printf " ------------ $(TARGET) installer ------------ \n"; \
		if [ -f $(TERMUX_BIN)/$(TARGET) ]; then \
			printf " - $(TARGET) already installed\n"; \
			exit; \
		fi; \
		if [ ! "$(INSTALL_SUCCESS)" = "true" ] && [ ! "$(INSTALL_SUCCESS)" = "" ]; then \
			printf " - $(YELLOW)$(BOLD)Warning:$(BOLD_RESET)$(RESET) a previously-stayed failed installation process found\n"; \
		fi; \
		if [ -f $(DEB_DIR)/*.deb ]; then \
			printf " - The created deb pack was found. It's setup...\n"; \
			cd $(DEB_DIR) || exit 1; \
			apt install ./*.deb || exit 1; \
			if [ ! "$?" = "0" ]; then \
				cd $(CUR_DIR); \
				printf " - Success.\n\n"; \
				echo "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
				echo "UNINSTALLED_SUCCESS := " > $(BUILD)/config/UNINS_STAT.mk; \
				cd ..; \
				exit 0; \
			else \
				cd $(CUR_DIR); \
				printf " - $(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) installing failed!\n"; \
				echo "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
				cd ..; \
				exit 1; \
			fi; \
		fi; \
		if [ ! -f $(BINARY_DIR)/$(TARGET) ]; then \
			printf " - $(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) Package not builded! Please build package and try again \n"; \
			echo "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		printf " - Installing binary...\n"; \
		if [ "`cp $(BINARY_DIR)/$(TARGET) /data/data/com.termux/files/usr/bin/$(TARGET)`" = "" ]; then \
			printf " - Setting up permissions...\n"; \
		else \
			echo "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		if [ "`chmod 777 $(TERMUX_BIN)/$(TARGET)`" = "" ]; then \
			printf " - Saving current status...\n"; \
			echo "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
		else \
			echo "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
			exit 1; \
		fi; \
		printf " - Success.\n\n"; \
		echo "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
		echo "UNINSTALLED_SUCCESS := " > $(BUILD)/config/UNINS_STAT.mk; \
	else \
		printf " - $(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) This function is only available on Termux.\n"; \
		exit 1; \
	fi

# uninstaller
.PHONY: uninstall
uninstall:
	# really termux?
	$(hide)if [ -f $(TERMUX_BIN)/termux-open ]; then \
		printf " ----------- $(TARGET) uninstaller ----------- \n"; \
		if [ ! -f $(TERMUX_BIN)/$(TARGET) ]; then \
			printf " - $(TARGET) already uninstalled\n"; \
			exit; \
		fi; \
		if [ ! "$(UNINSTALL_SUCCESS)" = "true" ] && [ ! "$(UNINSTALL_SUCCESS)" = "" ]; then \
			printf " - $(YELLOW)$(BOLD)Warning:$(BOLD_RESET)$(RESET) a previously-stayed failed uninstallation process found\n"; \
		fi; \
		if [ -f $(TERMUX_USR)/share/man/man8/$(TARGET).8.gz ]; then \
			printf " - It was found to be established by $(TARGET)'s deb pack. It's removed with apt...\n"; \
			apt remove -y $(TARGET) || exit 1; \
			printf " - Success.\n\n"; \
			echo "UNINSTALLED_SUCCESS := true" > $(BUILD)/config/UNINS_STAT.mk; \
			echo "INSTALL_SUCCESS := " > $(BUILD)/config/INS_STAT.mk; \
		else \
			printf " - It was found that pmt was manually established (with this makefile or copying). Manually removed...\n"; \
			if [ "`rm $(TERMUX_BIN)/$(TARGET)`" = "" ]; then \
				printf " - Success.\n\n"; \
				echo "UNINSTALLED_SUCCESS := true" > $(BUILD)/config/UNINS_STAT.mk; \
				echo "INSTALL_SUCCESS := " > $(BUILD)/config/INS_STAT.mk; \
			else \
				echo "UNINSTALLED_SUCCESS := false" > $(BUILD)/config/UNINS_STAT.mk; \
				exit 1; \
			fi; \
		fi; \
	else \
		printf "$(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) This function is only available on Termux.\n"; \
		exit 1; \
	fi

# end