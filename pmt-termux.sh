#!/data/data/com.termux/files/usr/bin/env bash

# By YZBruh | ShawkTeam

# Variables
LOCAL_VERSION="2.9.1"
LOCAL_RELDATE="20241002"
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
    printc "    --package <FILE>            If you already have a pmt package, make\n                                  setup by specifying this way."
    printc "Report bugs to <t.me/ShawkTeam | Topics | pmt>"

    exit 0
}

# Script really operated termux proclamation?
function really_termux()
{
    basename -a ${LOCAL_PREFIX}/bin/* | grep "termux" &>/dev/null \
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

# check xz-utils install status
function check_xz()
{
    # The outflow of the APT is not controlled in use
    [ -f ${LOCAL_PREFIX}/bin/xz ] \
    || abort "xz-utils not installed! Run setup command."
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
    local URL="https://github.com/${LOCAL_OWNER}/${LOCAL_REPO}/releases/tag/${LOCAL_RELEASE_TAG}/download/pmt-${LOCAL_ARCH}-${LOCAL_RELDATE}.xz"
    local URL_MANDOC="https://github.com/${LOCAL_OWNER}/${LOCAL_REPO}/releases/tag/${LOCAL_RELEASE_TAG}/download/mandoc.gz"

    print "Downloading: 'pmt-${LOCAL_ARCH}-${LOCAL_RELDATE}.xz'..."
    curl -L "${URL}" -o "${LOCAL_TMPDIR}/pmt-${LOCAL_ARCH}.xz" &>/dev/null \
    || abort "Download failed!"

    HAVE_MANDOC=true
    print "Downloading mandoc..."
    curl -L "${URL_MANDOC}" -o "${LOCAL_TMPDIR}/pmt.8.gz" &>/dev/null \
    || warning "Download failed! (mandoc)"

    chmod -R 755 "${LOCAL_TMPDIR}" &>/dev/null \
    || warning "Cannot set mode '777' on downloaded files."
}

# For installing required packages
function setup_packages()
{
    net_control

    print "Updating mirrors..."
    pkg update &>/dev/null || abort "Updating failed!"

    print "Installing xz-utils..."
    pkg install -y xz-utils &>/dev/null \
    || abort "Installing failed!"

    print "Success."
    exit 0
}

# Install deb package
function install_fn()
{
    local mydir="${PWD}"
    [ "${LOCAL_PACKAGE}" = "" ] || local bname=$(basename ${LOCAL_PACKAGE})

    ${PACKAGE} && \
    if [ ! -f "${LOCAL_PACKAGE}" ]; then
        [ -d "${LOCAL_PACKAGE}" ] \
        && abort "\`${LOCAL_PACKAGE}': is directory."

        abort "\`${LOCAL_PACKAGE}': no such file."
    else
        cp "${LOCAL_PACKAGE}" "${LOCAL_TMPDIR}/pmt-${LOCAL_ARCH}.xz"
    fi

    cd "${LOCAL_TMPDIR}"

    print "Extracting package..."
    if xz -d "$(basename *.xz)" ; then
        rm -f "pmt*.xz"
    else
        abort "Failed! Cannot extract pmt package."
    fi

    [ -z $(basename "pmt-*") ] \
    && abort "Extracted binary file was not found!"
    mv "$(basename pmt-*)" pmt

    print "Installing..."
    cp pmt "${LOCAL_PREFIX}/bin/pmt" &>/dev/null \
    || abort "Installing failed!"
    
    if ${HAVE_MANDOC}; then
        print "Installing mandoc (force)..."
        cp -f  pmt.8.gz ${LOCAL_PREFIX}/share/man/man8 &>/dev/null
        chmod 755 ${LOCAL_PREFIX}/share/man/man8/pmt.8.gz &>/dev/null
    fi

    print "Setting up permissions for binary..."
    chmod 755 "${LOCAL_PREFIX}/bin/pmt" &>/dev/null \
    || abort "Failed to set permissions!"

    print "Success."
    cd "${mydir}"
}

# Uninstall deb package
function uninstall_fn()
{
    print "Uninstalling Partition Manager..." && \
    if rm "${LOCAL_PREFIX}/bin/pmt" &>/dev/null; then
        print "Success."
    else
        abort "Failed!"
    fi

    rm -f ${LOCAL_PREFIX}/share/man/man8/pmt.8.gz
}

trap "abort Interrupt." SIGINT
trap "cleanup" SIGQUIT
PACKAGE=false
ALREADY_SHIFT=false
HAVE_MANDOC=false
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
            PACKAGE=true
            [ -z ${2} ] \
            && printc "Option '--package' requires an argument (file)." \
            && exit 1
            LOCAL_PACKAGE="${2}"
            ALREADY_SHIFT=true && shift 1
            ;;
        --help)
            view_help
            ;;
        *)
            if echo ${1} | grep "-" &>/dev/null; then
                if ! echo ${1} | grep ".xz" &>/dev/null; then
                    printc "Unknown option: ${1}" \
                    exit 1
                else
                    break;
                fi
            else
                break
            fi
            ;;
    esac

    ${ALREADY_SHIFT} || shift 1
done

### Main ###
[ -z "${1}" -a "${SOME_SPEC}" != 1 ] && view_help

script_head
really_termux
gen_tempdir

if [ "${PROCESS}" = 1 ]; then
    [ -f "${LOCAL_PREFIX}/bin/pmt" ] \
    && abort "Partition Manager already installed."
    ${PACKAGE} || net_control
    check_xz
    get_architecture
    print "Starting install process..."
    ${PACKAGE} || download
    install_fn
elif [ "${PROCESS}" = 2 ]; then
    [ ! -f "${LOCAL_PREFIX}/bin/pmt" ] \
    && abort "Partition Manager already uninstalled."
    print "Starting uninstall process..."
    uninstall_fn
fi

cleanup

exit 0
