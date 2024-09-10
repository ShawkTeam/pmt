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

INSTALL_PROGRESS_LIST := \
	really_termux \
	welcome \
	check_ins_stat \
	deb_installer \
	really_builded \
	install_binary

UNINSTALL_PROGRESS_LIST := \
	really_termux \
	welcome \
	check_unins_stat \
	uninstall_$(TARGET)

# create an empty target
all:
	$(P) ""

# installer
.PHONY: install
install: $(INSTALL_PROGRESS_LIST)

# uninstaller
.PHONY: uninstall
uninstall: $(UNINSTALL_PROGRESS_LIST)

install_binary:
	$(E) " - Installing binary..."
	if cp $(BINARY_DIR)/$(TARGET) /data/data/com.termux/files/usr/bin/$(TARGET); then \
		$(E_NS) " - Setting up permissions..."; \
	else \
		$(E_NS) "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
		exit 1; \
	fi; \
	if chmod 777 $(TERMUX_BIN)/$(TARGET); then \
		$(E_NS) " - Saving current status..."; \
		$(E_NS) "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
	else \
		$(E_NS) "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
		exit 1; \
	fi; \
	$(P) " - Success.\n\n"; \
	$(E_NS) "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
	$(E_NS) "UNINSTALLED_SUCCESS := " > $(BUILD)/config/UNINS_STAT.mk
	@ exit 0

uninstall_$(TARGET):
	if [ -f $(TERMUX_USR)/share/man/man8/$(TARGET).8.gz ]; then \
		$(E_NS) " - It was found to be established by $(TARGET)'s deb pack. It's removed with apt..."; \
		apt remove -y $(TARGET) || exit 1; \
		$(P) " - Success.\n\n"; \
		$(E_NS) "UNINSTALLED_SUCCESS := true" > $(BUILD)/config/UNINS_STAT.mk; \
		$(E_NS) "INSTALL_SUCCESS := " > $(BUILD)/config/INS_STAT.mk; \
	else \
		$(E_NS) " - It was found that pmt was manually established (with this makefile or copying). Manually removed..."; \
		if rm $(TERMUX_BIN)/$(TARGET); then \
			$(P) " - Success.\n\n"; \
			$(E_NS) "UNINSTALLED_SUCCESS := true" > $(BUILD)/config/UNINS_STAT.mk; \
			$(E_NS) "INSTALL_SUCCESS := " > $(BUILD)/config/INS_STAT.mk; \
		else \
			$(E_NS) "UNINSTALLED_SUCCESS := false" > $(BUILD)/config/UNINS_STAT.mk; \
			exit 1; \
		fi; \
	fi

deb_installer:
	if [ -f $(DEB_DIR)/*.deb ]; then \
		$(E_NS) " - The created deb pack was found. It's setup..."; \
		cd $(DEB_DIR) || exit 1; \
		apt install ./*.deb || exit 1; \
		if [ ! "$?" = "0" ]; then \
			cd $(CUR_DIR); \
			$(P) " - Success.\n\n"; \
			$(E_NS) "INSTALL_SUCCESS := true" > $(BUILD)/config/INS_STAT.mk; \
			$(E_NS) "UNINSTALLED_SUCCESS := " > $(BUILD)/config/UNINS_STAT.mk; \
			cd ..; \
			exit 0; \
		else \
			cd $(CUR_DIR); \
			$(P) " - $(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) installing failed!\n"; \
			$(E_NS) "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
			cd ..; \
			exit 1; \
		fi; \
	fi

check_ins_stat:
	@ if [ ! "$(INSTALL_SUCCESS)" = "true" ] && [ ! "$(INSTALL_SUCCESS)" = "" ]; then \
		$(P) " - $(YELLOW)$(BOLD)Warning:$(BOLD_RESET)$(RESET) a previously-stayed failed installation process found\n"; \
	fi

check_unins_stat:
	@ if [ ! "$(UNINSTALL_SUCCESS)" = "true" ] && [ ! "$(UNINSTALL_SUCCESS)" = "" ]; then \
		$(P) " - $(YELLOW)$(BOLD)Warning:$(BOLD_RESET)$(RESET) a previously-stayed failed uninstallation process found\n"; \
	fi

welcome:
	$(E) " ----------- $(TARGET) $(PROG)er ----------- "
	@ if [ "$(PROG)" = "uninstall" ]; then \
		if [ ! -f $(TERMUX_BIN)/$(TARGET) ]; then \
			$(E_NS) " - $(TARGET) already $(PROG)ed"; \
			exit 1; \
		fi; \
	fi
	@ if [ "$(PROG)" = "install" ]; then \
		if [ -f $(TERMUX_BIN)/$(TARGET) ]; then \
			$(E_NS) " - $(TARGET) already $(PROG)ed"; \
			exit 1; \
		fi; \
	fi

really_termux:
	@ if [ ! -f $(TERMUX_BIN)/termux-open ]; then \
		$(P) "$(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) This function is only available on Termux.\n"; \
		exit 1; \
	fi

really_builded:
	if [ ! -f $(BINARY_DIR)/$(TARGET) ]; then \
		$(P) " - $(RED)$(BOLD)Error:$(BOLD_RESET)$(RESET) Package not builded! Please build package and try again \n"; \
		$(E_NS) "INSTALL_SUCCESS := false" > $(BUILD)/config/INS_STAT.mk; \
		exit 1; \
	fi

# end
