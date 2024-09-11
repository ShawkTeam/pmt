## Partition Manager (pmt)

[![Commit reviewed](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml/badge.svg)](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml)

This binary, written with C++, is for writing/reading and formatting on Android partitions.

#### Presented arguments (options)

```
Usage:  pmt [OPTIONS] backup PARTITION [OUTPUT] [OPTIONS]...
  or:   pmt [OPTIONS] flash PARTITION FILE [OPTIONS]...
  or:   pmt [OPTIONS] format PARTITION FILE_SYSTEM[ext/2/3/4] [OPTIONS]...

Options:
   -l, --logical     It is meant to determine whether the target partition is logical.
   -c, --context     It is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name).
   -p, --list        List partitions.
   -s, --silent      Information and warning messages are silenced in normal work.
   -f, --force       Force mode. Some things are ignored.
   -V, --verbose     Verbose mode. Print detailed informations etc.
   -S, --set-lang    Set current language.
   -v, --version     See version.
       --help        See this help message.

Examples:
   pmt backup boot_a -c /dev/block/platform/bootdevice/by-name
   pmt flash boot_a /sdcard/twrp/boot.img -c /dev/block/platform/bootdevice/by-name
   pmt format system_a ext4 --logical
   pmt -c /dev/block/platform/bootdevice/by-name --list

Report bugs and suggestions to <t.me/ShawkTeam | Topics | pmt>
```

#### Some notes

- pmt supports multiple languages. [See languages.](https://github.com/ShawkTeam/pmt/blob/2.8.0/LANGUAGES.md)
- [Add language.](https://github.com/ShawkTeam/pmt/blob/2.8.0/ADD-LANGUAGES.md)
- Feel free to ask any questions you want.
- Packages are available in publications.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes.](https://github.com/ShawkTeam/pmt/blob/2.8.0/CHANGELOG.md)
- We are always open to your suggestions and support (developing)!

### How is it built?
Make or Android NDK is required to build.

##### Build with NDK
 - [Download Android NDK](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/ShawkTeam/pmt -b 2.8.0
cd pmt
```
 - Set the NDK working directory variable.
```
make gen-ndk-makefiles
# If you fail the audit etc, use FORCE_GEN.
# Example:
    make gen-ndk-makefiles FORCE_GEN=true

# Required by Android NDK
export NDK_PROJECT_PATH="${PWD}"
```
 - Go to the NDK directory and start the build
```
# Required for creating clang version information and directory access
export NDK_ROOT_DIR="${PWD}"
cd "${NDK_PROJECT_PATH}" \
&& bash build/bash/gen-header \
&& cd "${NDK_ROOT_DIR}"

# Start build
./ndk-build
```
 - The output files will be inside the `pmt` folder. Binaries are available in two architectures within the `libs` folder. `arm64-v8a` (64-bit) and `armeabi-v7a` (32-bit).
```
                    pmt/
                     |
     ________________|________________
     |         |            |        |
   jni/      build/        obj/    libs/
                                     |
                           __________|__________
                           |                   |
                       arm64-v8a/         armeabi-v7a/
                           |                   |
                          pmt                 pmt
```

##### Build with Makefiles

```
# Setup environment
pkg update \
&& pkg upgrade -y \
&& pkg install make clang binutils xz-utils -y

# Start build
make

# To specify clang, just use PMT_CXX=<clang++> next to the command (and same logic in AR)
# Example:
    make PMT_CXX=${PWD}/../toolchain/bin/clang-18
    make PMT_AR=${PWD}/../toolchain/bin/ar
    make PMT_CXX=${PWD}/../toolchain/bin/clang-18 PMT_AR=${PWD}/../toolchain/bin/ar

# Speficying extra compiler flags on cmd. Example:
    make PMT_EXTRA_CXXFLAGS="-O2"

# Use termux :D

# Cleaning working directory
make clean

# Rebuild
make rebuild

# Install
make install

# Uninstall
make uninstall

# Re-install (install & uninstall)
make reinstall

# Manage pmt with termux script
## Download script
curl -LSs https://github.com/ShawkTeam/pmt/raw/2.8.0/pmt-termux.sh > pmt-termux.sh

## View script help
bash pmt-termux.sh # --help (optional)

## The commands will be told to you anyway. Ask your questions from the telegram group.

```
 - For the make installable debian package:

```
make deb <ARCH_NUM>

# Examples
    make deb FOR_THIS=64
    make deb FOR_THIS=32
```

### How to use
```
# Run
/system/bin/su
```

- If you have installed the deb package of pmt, installed it with a makefile, or installed it to `$PATH` using any path, just the name of the pmt is enough (or the file name if you did it manually)
```
pmt <...>
```

- If you have not done this type of institution, pmt is in the directory where you are present you can run with `./`.
```
./pmt <...> # or whatever the file name is
```

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `build/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
