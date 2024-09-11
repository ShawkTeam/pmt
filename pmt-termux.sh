#!/data/data/com.termux/files/usr/bin/env bash

# By YZBruh | ShawkTeam

# Variables
LOCAL_VERSION="2.8.0"
LOCAL_OWNER="ShawkTeam"
LOCAL_REPO="pmt"
LOCAL_RELEASE_TAG="${LOCAL_VERSION}"
LOCAL_PREFIX="${PREFIX}"
[ -d "${LOCAL_PREFIX}" ] \
|| LOCAL_PREFIX="/data/data/com.termux/files/usr"
LOCAL_TMPDIR="${LOCAL_PREFIX}/tmp/pmt-termux-helper"

# Colors
RESET="\033[0m"
RED="\033[0;31m"
GREEN="\033[0;32m"
YELLOW="\033[0;33m"

# Printer functions
function printc() { echo -e "$*" >&2; }
function print()
{
    if echo "$*" | grep "Success" &>/dev/null; then
        echo -e " - ${GREEN}${1:0:7}${RESET}." >&2
    else
        echo -e " - $*" >&2
    fi
}

# Print error and exit
function abort()
{
    print "${RED}Error:${RESET} ${@}"
    cleanup
    exit 1
}

# Print warnings
function warning() { print "${YELLOW}Warning:${RESET} ${@}"; }

# Print head
function script_head() { printc " --- Partition Manager Termux Helper Script --- \n"; }

# For display help message
function view_help()
{
    echo -n "Usage: "
    if echo "${0}" | grep "./" >&/dev/null; then
        printc "${0} [OPTIONS]..."
    else
        printc "(bash) ${0} [OPTIONS]"
    fi

    printc "Install, uninstall, install status checker for Partition Manager binary.\n"
    printc "Options:"
    printc "    install,   -i [OPTS]        Download and install Partition Manager."
    printc "    uninstall, -u               Uninstall Partition Manager."
    printc "    status,    -s               Display install/uninstall status."
    printc "    --setup,   -S               Setup required packages."
    printc "    --package <FILE>            If you already have a debug package, make\n                                  setup by specifying this way."
    printc "    --binary  <FILE>            Setup binary instead of the deb pack."
    printc "    --compress-algorithm [ALGO] Speficy custom algorithm for extracting                                           package (if only custom package specified)."
    printc "Supported algorithms: xz, gzip, zip, 7z, tar, tar.xz, tar.gz\n"
    printc "Report bugs to <t.me/ShawkTeam | Topics | pmt>"

    exit 0
}

# Script really operated termux proclamation?
function really_termux()
{
    ls "${LOCAL_PREFIX}/bin" | grep "termux" &>/dev/null \
    || abort "Are you sure you're in termux?"
}

# Get architecture info
function get_architecture()
{
    local arch=$(uname -m)
    local archs_64=("aarch64" "armv8" "arm64-v8a" "armv8-a")
    local archs_32=("aarch32" "armv7" "armeabi-v7a" "armv7l")

    print "Device architecture: '${arch}'."

    for a in ${archs_64[@]}; do
        [ "${arch}" = "${a}" ] \
        && LOCAL_ARCH="arm64-v8a" \
        && return
    done

    for a in ${archs_32[@]}; do
        [ "${arch}" = "${a}" ] \
        && LOCAL_ARCH="armeabi-v7a" \
        && return
    done

    LOCAL_ARCH="arm64-v8a"
}

# Generate template dir
function gen_tempdir() { mkdir -p "${LOCAL_TMPDIR}"; }

# Clean template dir
function cleanup() { rm -rf "${LOCAL_TMPDIR}"; }

# Check install/uninstall status
function check_status()
{
    local installed="${RED}false${RESET}"
    [ -f "${LOCAL_PREFIX}/bin/pmt" ] \
    && installed="${GREEN}true${RESET}"

    print "Installed: ${installed}"
    exit 0
}

# Check internet connection
function net_control()
{
    curl "https://github.com" &>/dev/null \
    || abort "You need internet connection to this process."
}

# Download Partition Manager
function download()
{
    local URL

    if [ "${BINARY}" = 1 -a "${PACKAGE}" != 1 ]; then
        URL="https://github.com/${LOCAL_OWNER}/${LOCAL_REPO}/releases/tag/${LOCAL_RELEASE_TAG}/download/pmt-${LOCAL_ARCH}.xz"
    else
        URL="https://github.com/${LOCAL_OWNER}/${LOCAL_REPO}/releases/tag/${LOCAL_RELEASE_TAG}/download/pmt-${LOCAL_ARCH}.deb"
    fi

    print "Downloading: \`${URL}'"

    curl -L "${URL}" -o "${LOCAL_TMPDIR}/pmt-${LOCAL_ARCH}.deb" &>/dev/null \
    || abort "Download failed!"

    chmod -R 777 "${LOCAL_TMPDIR}" \
    || warning "Cannot set mode '777' on installed sources."
}

# For installing required packages
function setup_packages()
{
    net_control

    print "Updating mirrors..."
    if ! pkg update &>/dev/null || [ "$?" != 0 ]; then
        abort "Updating failed!"
    fi

    print "Installing: 'xz-utils, p7zip'"
    if ! pkg install -y xz-utils p7zip || [ "$?" != 0 ]; then
        abort "Installing failed!"
    fi

    print "Success."
    exit 0
}

# Install deb package
function install_fn()
{
    local mydir="$(pwd)"
    [ "${LOCAL_PACKAGE}" = "" ] || local bname=$(basename ${LOCAL_PACKAGE})

    [ "${PACKAGE}" = 1 ] && \
    if [ ! -f "${LOCAL_PACKAGE}" ]; then
        [ -d "${LOCAL_PACKAGE}" ] \
        && abort "\`${LOCAL_PACKAGE}': is directory."

        abort "\`${LOCAL_PACKAGE}': no such file."
    else
        cp "${LOCAL_PACKAGE}" "${LOCAL_TMPDIR}"
    fi

    cd "${LOCAL_TMPDIR}"

    [ "${BINARY}" = 1 -a "${NONE_ALGO}" != 1 ] \
    && print "Extracting '${bname}'..." && \
    if eval "${ALGO_DEC} ${ALGO_FLAGS} ${LOCAL_TMPDIR}/${bname}" &>/dev/null; then
        rm -f "${bname}"
    else
        abort "Failed! Try speficing algorithm."
    fi

    [ "$(basename *)" = "*" ] \
    && abort "Deb pack or binary file was not found!"

    bname=$(basename *)

    if [ "${BINARY}" = 1 ]; then
        mv "${bname}" pmt &>/dev/null

        print "Copying..."
        cp pmt "${LOCAL_PREFIX}/bin/pmt" &>/dev/null \
        || abort "Copying failed"

        print "Setting up permissions..."
        chmod 777 "${LOCAL_PREFIX}/bin/pmt" &>/dev/null \
        || abort "Cannot set permissions!"

        print "Success."
        return
    fi

    print "Installing Partition Manager with APT..."
    if ! apt -y install ./pmt-${LOCAL_ARCH}.deb; then
        warning "Installing failed with APT. Trying installing with dpkg..."

        dpkg install pmt-${LOCAL_ARCH}.deb &>/dev/null \
        || abort "Cannot install Partition Manager!"
    fi

    print "Success."
    cd "${mydir}"
}

# Uninstall deb package
function uninstall_fn()
{
    [ "${BINARY}" = 1 ] \
    && print "Removing binary..." && \
    if rm "${LOCAL_PREFIX}/bin/pmt" &>/dev/null; then
        print "Success."
        return
    else
        abort "Failed!"
    fi

    print "Uninstalling Partition Manager with APT..."
    if ! apt -y remove pmt &>/dev/null; then
        warning "Uninstalling failed with APT. Trying uninstalling with dpkg..."

        dpkg remove pmt &>/dev/null \
        || abort "Cannot uninstall Partition Manager!"
    fi

    print "Success."
}

trap "abort Interrput; cleanup" SIGINT
# set -x

# Process arguments
while (($# >= 1)); do
    SOME_SPEC=1

    case "${1}" in
        install|-i)
            PROCESS=1
            ;;
        uninstall|-u)
            PROCESS=2
            ;;
        status|-s)
            script_head
            check_status y
            ;;
        --setup|-S)
            script_head
            print "Starting package setupper..."
            setup_packages
            ;;
        --package)
            PACKAGE=1
            LOCAL_PACKAGE="${2}"
            ;;
        --binary)
            BINARY=1
            ;;
        --not-compressed)
            NOT_COMP=1
            ;;
        --compress-algorithm)
            ALGO_SPEC=1
            [ -z "${2}" ] \
            && abort "'--compress-algorithm' requires an argument."
            case "${2}" in
                xz|gzip|zip|7z|tar|tar.xz|tar.gz)
                    if echo "${2}" | grep "tar." &>/dev/null; then
                        ALGO_DEC="tar"
                        ALGO_FLAGS="-xf"
                    elif [ "${2}" = "zip" ]; then
                        ALGO_DEC="unzip"
                        ALGO_FLAGS=
                    elif [ "${2}" = "7z" ]; then
                        ALGO_DEC="7z"
                        ALGO_FLAGS="x"
                    else
                        ALGO_DEC="${2}"
                        ALGO_FLAGS="-d"
                    fi
                    ;;
                none)
                    NONE_ALGO=1
                    ;;
                *)
                    abort "Unknown compress algorithm: ${2}"
                    ;;
            esac
            ;;
        --help)
            view_help
            ;;
    esac

    shift 1
done

### Main ###
[ -z "${1}" -a "${SOME_SPEC}" != 1 ] && view_help

script_head

[ -z "${LOCAL_PACKAGE}" -a "${PACKAGE}" = 1 ] \
&& abort "'--package' requires an argument (file)."

really_termux
gen_tempdir

[ -z "${ALGO_DEC}" ] && ALGO_DEC="xz" && ALGO_FLAGS="-d"
[ "${ALGO_SPEC}" = 1 -a "${PACKAGE}" != 1 ] \
&& abort "Compression algorithm cannot be specified without package specification option."

if [ "${PROCESS}" = 1 ]; then
    [ -f "${LOCAL_PREFIX}/bin/pmt" ] \
    && abort "Partition Manager already installed."
    [ "${PACKAGE}" = 1 ] || net_control
    get_architecture
    print "Starting install process..."
    [ "${PACKAGE}" = 1 ] || download
    install_fn
elif [ "${PROCESS}" = 2 ]; then
    [ ! -f "${LOCAL_PREFIX}/bin/pmt" ] \
    && abort "Partition Manager already uninstalled."
    print "Starting uninstall process..."
    uninstall_fn
fi

cleanup

exit 0
