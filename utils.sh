#!/usr/bin/bash
# By YZBruh | ShawkTeam

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

# ANSI color codes
RED='\e[31m'
NC='\e[0m'

# needed variables
VERSION="2.4.0"
CUR_DIR=$(pwd)
LIB_DIR=${CUR_DIR}/libs
ARMV8A_DIR=${LIB_DIR}/arm64-v8a
ARMV7A_DIR=${LIB_DIR}/armeabi-v7a
DEB_DIR=${CUR_DIR}/deb
DEBUTILS_DIR=${CUR_DIR}/debutils
DEBTERMUX_USR=${DEBUTILS_DIR}/data/data/com.termux/files/usr

# set file modes (all) to 755
${SUDO} chmod -R 755 *

# error messages
abort()
{
    if [ ! "$1" = "" ]; then
        printf "${RED}${1}${NC}\n"
    fi
    if [ -d ${DEBUTILS_DIR}/temp ]; then
        rm -rf ${DEBUTILS_DIR}/temp
    fi
    exit 1
}

gen_deb()
{
    printf " --------- Making pmt deb package ---------\n"; 
    printf " - Checking all files and directories (only
eededs)...\n"; 

    # check important files
    if [ ! -d ${DEBUTILS_DIR} ]; then 
        abort " - Not found: ${DEBUTILS_DIR}\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/DEBIAN ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/DEBIAN\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/mandoc ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/mandoc\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr/bin ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr/bin\n"
    fi
    if [ ! -d ${DEBUTILS_DIR}/data/data/com.termux/files/usr/share/man/man8 ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/data/data/com.termux/files/usr/share/man/man8\n"
    fi
    if [ ! -f ${DEBUTILS_DIR}/mandoc/pmt.8.gz ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/mandoc/pmt.8.gz\n"
    fi
    if [ ! -f ${DEBUTILS_DIR}/DEBIAN/control_32 ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/DEBIAN/control_32\n"
    fi
    if [ ! -f ${DEBUTILS_DIR}/DEBIAN/control_64 ]; then 
        abort " - Not found: ${DEBUTILS_DIR}/DEBIAN/control_64\n"
    fi
    if [ ! -f ${ARMV8A_DIR}/pmt ]; then 
        abort " - Package not comptely builded! Please build package and try again\n"
    elif [ ! -f ${ARMV7A_DIR}/pmt ]; then 
        abort " - Package not comptely builded! Please build package and try again\n"
    fi

    # generate template dir
    printf " - Generating template dir...\n"
    ${SUDO} mkdir -p ${DEBUTILS_DIR}/temp || abort

    # generate out dir
    printf " - Generating out dir...\n"
    ${SUDO} mkdir -p ${DEB_DIR} || abort

    # copy files
    printf " - Copying files...\n"
    ${SUDO} cp -r ${DEBUTILS_DIR}/data ${DEBUTILS_DIR}/temp || abort
    ${SUDO} rm -f ${DEBTERMUX_USR}/share/man/man8/dummy
    ${SUDO} rm -f ${DEBTERMUX_USR}/bin/dummy
    ${SUDO} mkdir -p ${DEBUTILS_DIR}/temp/DEBIAN || abort

    # select control file
    printf " - Selected arm-${PREFIX} package control file.\n"
    ${SUDO} cp ${DEBUTILS_DIR}/DEBIAN/control_${PREFIX} ${DEBUTILS_DIR}/temp/DEBIAN/control || exit 1
    ${SUDO} cp ${DEBUTILS_DIR}/mandoc/pmt.8.gz ${DEBTERMUX_USR}/share/man/man8 || abort
    if [ "${PREFIX}" = "64" ]; then 
        ${SUDO} cp ${ARMV8A_DIR}/pmt ${DEBTERMUX_USR}/bin || abort
    elif [ "${PREFIX}" = "32" ]; then 
        ${SUDO} cp ${ARMV7A_DIR}/pmt ${DEBTERMUX_USR}/bin || abort
    fi

    # start dpkg-deb
    printf " - Starting dpkg-deb...\n"
    sleep 2
    ${SUDO} chmod -R 755 *

    # if ARM_PREFIX is '-v7a', unset ARM_PREFIX and PREFIX. Re set PREFIX
    if [ "${PREFIX}" = "32" ]; then 
        unset PREFIX
        PREFIX="eabi-v7a"
    fi

    ${SUDO} dpkg-deb -b ${DEBUTILS_DIR}/temp ${DEB_DIR}/pmt-${VERSION}-arm${PREFIX}${ARM_PREFIX}.deb || abort
    ${SUDO} rm -rf ${DEBUTILS_DIR}/temp

    printf " - Done! Package: ${DEB_DIR}/pmt-${VERSION}-arm${PREFIX}${ARM_PREFIX}.deb\n"
}

gen_modpack()
{
    printf " ----------- Making static lib package -----------\n"
    printf " - Checking files...\n"

    if [ ! -f $(STATICLIB_DIR)/libpmt_root.a ]; then
        printf " - Not found: $(STATICLIB_DIR)/libpmt_root.a\n"
        exit 1
    fi
    if [ ! -f $(STATICLIB_DIR)/libpmt_lister.a ]; then
        printf " - Not found: $(STATICLIB_DIR)/libpmt_lister.a\n"
        exit 1
    fi
    if [ ! -f $(STATICLIB_DIR)/libpmtpartition_tool.a ]; then
        printf " - Not found: $(STATICLIB_DIR)/libpmtpartition_tool.a\n"
        exit 1
    fi

    printf " - Compressing...\n"
    mkdir -p static-lib-pack
    cd static-lib-pack
    cp jni/include/pmt.h .
    mkdir -p include
    mv pmt.h include/
    zip -rq pmt-static-lib-pack.zip *.a include || exit 1
    rm -rf include
    sleep 1
    printf " - Success.\n\n"
    cd ..
}

case "${1}" in
    make-deb)
        case "${2}" in
            arm64-v8a)
                PREFIX="64"
                ARM_PREFIX="-v8a"
            ;;
            armeabi-v7a)
                PREFIX="32"
                ARM_PREFIX=""
            ;;
            *)
                abort " - Error: unknown architecture flag: $2. Avaiable: arm64-v8a & armeabi-v7a.\n"
        esac

        case "${3}" in
            sudo)
                SUDO="sudo"
            ;;
            no-sudo)
                SUDO=""
            ;;
            *)
                SUDO=""
        esac
        gen_deb
    ;;
    modpack)
        case "${2}" in
            arm64-v8a)
                STATICLIB_DIR="${CUR_DIR}/obj/local/${2}"
            ;;
            armeabi-v7a)
                STATICLIB_DIR="${CUR_DIR}/obj/local/${2}"
            ;;
            *)
                abort " - Error: unknown architecture flag: ${2}. Avaiable: arm64-v8a & armeabi-v7a.\n"
        esac

        gen_modpack
    ;;
    *)
        abort "${0}: invalid operand.\nUse the make-deb flag to create a deb package, and the modpack flag to create packages for static libraries."
esac

# end of script
