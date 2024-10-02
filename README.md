## Partition Manager (pmt)

[![Commit reviewed](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml/badge.svg)](https://github.com/ShawkTeam/pmt/actions/workflows/check_commits.yml)

This binary, written with C++, is for writing/reading, formatting and getting size on Android partitions.

```
Usage:  pmt [OPTIONS] backup PARTITION [OUTPUT] [OPTIONS]...
  or:   pmt [OPTIONS] flash PARTITION FILE [OPTIONS]...
  or:   pmt [OPTIONS] format PARTITION FILE_SYSTEM[ext/2/3/4] [OPTIONS]...
  or:   pmt [OPTIONS] partition-size PARTITION [OPTIONS]...

Options:
   -l, --logical     It is meant to determine whether the target partition is logical.
   -P, --search-path It is meant to specify a custom partition search path. Only classic partitions (default: /dev/block/by-name).
   -p, --list        List partitions.
   -s, --silent      Information and warning messages are silenced in normal work.
   -f, --force       Force mode. Some things are ignored.
   -V, --verbose     Verbose mode. Print detailed informations etc.
   -S, --set-lang    Set current language.
   -v, --version     See version.
       --help        See this help message.

Examples:
   pmt backup boot_a -P /dev/block/platform/bootdevice/by-name
   pmt flash boot_a /sdcard/twrp/boot.img -c /dev/block/platform/bootdevice/by-name
   pmt format system_a ext4 --logical
   pmt -P /dev/block/platform/bootdevice/by-name --list

Report bugs and suggestions to <t.me/ShawkTeam | Topics | pmt>
```

#### Some notes

- pmt supports multiple languages. [See languages.](https://github.com/ShawkTeam/pmt/blob/2.9.0/LANGUAGES.md)
- [Add language.](https://github.com/ShawkTeam/pmt/blob/2.9.0/ADD-LANGUAGES.md)
- Feel free to ask any questions you want.
- Packages are available in publications.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes.](https://github.com/ShawkTeam/pmt/blob/2.9.0/CHANGELOG.md)
- We are always open to your suggestions and support (developing)!

### How to build?
Partition Manager only buildable with Android NDK (make compilation system deprecated).

 - [Download Android NDK](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/ShawkTeam/pmt -b 2.9.0
cd pmt
```
 - Set the NDK working directory variable.
```
export NDK_PROJECT_PATH="${PWD}" # or where the source directory is everywhere
export NDK_ROOT_DIR=<PATH> # Note that if the NDK is in the directory

# Generate clang version header
bash build/bash/gen-header
```
 - Go to the NDK directory and start the build
```
./ndk-build

# Permission denied? Change mode and retry
(sudo) chmod +x ndk-build
# OR
(sudo) chmod 755 ndk-build
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

### Manage pmt with termux script
 - Download script.

```
curl -LSs https://github.com/ShawkTeam/pmt/raw/2.9.0/pmt-termux.sh > pmt-termux.sh
```
 - Some informations...
```
## View script help
bash pmt-termux.sh # --help (optional)

## The commands will be told to you anyway. Ask your questions from the telegram group.
```

### How to use
```
# Directly access root shell
/system/bin/su

# If you are using termux, use with
# tsu (sudo) will be a better choice
pkg install -y tsu # install tsu (sudo)

sudo <COMMAND(S)>
```

- If you have installed the deb package of pmt, installed it with a makefile, or installed it to `$PATH` using any path, just the name of the pmt is enough (or the file name if you did it manually)
```
(sudo) pmt <ARGUMENT(S)>
```

- If you have not done this type of institution, pmt is in the directory where you are present you can run with `(sudo) ./`.
```
(sudo) ./pmt <ARGUMENT(S)> # or whatever the file name is
```

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `build/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
