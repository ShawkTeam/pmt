#!/data/data/com.termux/files/usr/bin/env bash
#
# By YZBruh
#

VERSION="2.1.0"
CUR_DIR="$(pwd)"
TMP_DIR="${CUR_DIR}/tempinstall"
TERMUX_BIN_PREFIX="/data/data/com.termux/files/usr/bin"
UNAME="$(uname -m)"

abort()
{
    rm -rf "${TMP_DIR}"
    exit 1
}

echo " ------------ pmt installer ------------"

if [[ "${UNAME}" == "aarch64" ]] || [[ "${UNAME}" == "armv8a" ]]; then
    ARCH="aarch64"
elif [[ "${UNAME}" == "aarch32" ]] || [[ "${UNAME}" == "armv7a" ]]; then
    ARCH="armv7a"
    SUB_PREF="eabi"
else
    echo "  - Unsupported arch: ${UNAME}!"
    abort
fi

REL_LINK="https://github.com/YZBruh/pbt/releases/download/${VERSION}/pmt-${ARCH}-linux-android${SUB_PREF}.xz"

if [ -f "${TERMUX_BIN_PREFIX}/pmt" ]; then
    echo "  - pmt already installed."
    exit
fi

if [ ! -f "${TERMUX_BIN_PREFIX}/wget" ]; then
    echo "  - Installing wget..."
    pkg update || abort
    pkg install wget || abort
fi

echo "  - Downloading latest version of package..."

mkdir -p "${TMP_DIR}" || abort
wget -q -P "${TMP_DIR}" "${REL_LINK}" || abort

echo "  - Extracting downloaded package..."

cd "${TMP_DIR}" || abort
xz -d *.xz || abort
cd "${CUR_DIR}" || abort

echo "  - Installing..."

cp "${TMP_DIR}/pmt-${ARCH}-linux-android${SUB_PREF}" "${TERMUX_BIN_PREFIX}/pmt" || abort
chmod 777 "${TERMUX_BIN_PREFIX}/pmt" || abort
rm -rf "${TMP_DIR}" || abort

echo -e "  - Success.\n"

# end of script
