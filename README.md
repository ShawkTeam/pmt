## Partition Manager (pmt)

[![Commit reviewed](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml/badge.svg)](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml)

## Work continues on the renovated pmt! You can check it out now :) [ShawkTeam/pmt-renovated](https://github.com/ShawkTeam/pmt-renovated)

This binary, written with C++, is for managing (partition) table, writing/reading, formatting and getting size on Android partitions.

```
Usage:  pmt [OPTIONS] start-parted [DEVICE]...
  or:   pmt [OPTIONS] backup PARTITION [OUTPUT] [OPTIONS]...
  or:   pmt [OPTIONS] flash PARTITION FILE [OPTIONS]...
  or:   pmt [OPTIONS] format PARTITION FILE_SYSTEM[ext/2/3/4] [OPTIONS]...
  or:   pmt [OPTIONS] partition-size PARTITION [OPTIONS]...

Options:
   -l, --logical     It is meant to determine whether the target partition is logical.
   -P, --search-path It is meant to specify a custom partition search path. Only normal partitions (default: /dev/block/by-name).
   -p, --list        List partitions.
   -s, --silent      Information and warning messages are silenced in normal work.
   -f, --force       Force mode. Some things are ignored.
   -V, --verbose     Verbose mode. Print detailed informations etc.
   -S, --set-lang    Set current language.
   -U, --view-langs  See supported languages.
   -v, --version     See version.
       --help        See this help message.

partition-size flags:
       --only-size   Only the size is displayed, the partition name etc is not displayed.
       --as-byte     Display size as byte.
       --as-kilobyte Display size as kilobyte.
       --as-megabyte Display size as megabyte.
       --as-gigabyte Display size as gigabyte.

Examples:
   pmt backup boot_a -P /dev/block/platform/bootdevice/by-name
   pmt flash boot_a /sdcard/twrp/boot.img -c /dev/block/platform/bootdevice/by-name
   pmt format system_a ext4 --logical
   pmt -P /dev/block/platform/bootdevice/by-name --list
   pmt partition-size boot --as-byte
   pmt partition-size system --only-size --as-gigabyte --logical

Report bugs and suggestions to <t.me/ShawkTeam | Topics | pmt>
```

#### Some notes

- See the [guide](https://github.com/ShawkTeam/pmt/blob/3.0.2/INSTALLING.md) for installation (`INSTALLING.md`).
- pmt supports multiple languages. [See languages.](https://github.com/ShawkTeam/pmt/blob/3.0.2/LANGUAGES.md)
- [Add a language!](https://github.com/ShawkTeam/pmt/blob/3.0.2/ADD-LANGUAGES.md)
- Feel free to ask any questions you want.
- Packages are available in publications.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes.](https://github.com/ShawkTeam/pmt/blob/3.0.2/CHANGELOG.md)
- We are always open to your suggestions and support (developing)!

### How is it built?
Make or Android NDK is required to build.

##### Build with NDK
 - [Download Android NDK](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/ShawkTeam/pmt -b 3.0.2
cd pmt
```
 - Set the NDK working directory variable.
```
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

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `build/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
