## Partition Manager (pmt)

This binary C is for manage partitions of android devices.
It offers a lot of options. I will place these below. But first let me talk about the operation...

#### Presented arguments (options)

```
Usage:  pmt backup PARTITION [OUTPUT] [OPTIONS]...
  or:   pmt flash PARTITION FILE [OPTIONS]...
  or:   pmt format PARTITION FILE_SYSTEM[ext/2/3/4] [OPTIONS]...

Options:
   -l, --logical     It is meant to determine whether the target partition is logical.
   -c, --context     It is meant to specify a custom /dev context. Only classic partitions (default: /dev/block/by-name).
   -p, --list        List partitions.
   -s, --silent      Information and warning messages are silenced in normal work.
   -f, --force       Force mode. Some things are ignored.
   -S, --set-lang    Set current language.
   -v, --version     See version.
       --help        See this help message.

Examples:
   pmt backup boot_a -c /dev/block/platform/bootdevice/by-name
   pmt flash /sdcard/twrp/boot.img boot_a -c /dev/block/platform/bootdevice/by-name
   pmt format ext4 system_a --logical
   pmt -c /dev/block/platform/bootdevice/by-name --list

Report bugs to <t.me/ShawkTeam | Topics | pmt>
```

#### Some notes

- pmt supports multiple languages. [See languages.](https://github.com/ShawkTeam/pmt/blob/2.5.0/LANGUAGES.md)
- [Add language.](https://github.com/ShawkTeam/pmt/blob/2.5.0/ADD-LANGUAGES.md)
- Feel free to ask any questions you want.
- Packages are available in publications.
- If the logical partition flag is not used, a classic partition is tried to be processing by default.
- [Click to see special version changes.](https://github.com/ShawkTeam/pmt/blob/2.5.0/CHANGELOG.md)
- We are always open to your suggestions and support (developing)!

### How is it built?
Make or Android NDK is required to build.

##### Build with NDK
 - [Download Android NDK](https://developer.android.com/ndk/downloads) and extract the NDK package.
 - Clone this repository. And get access to it.
```
git clone https://github.com/ShawkTeam/pmt -b 2.5.0
cd pmt
```
 - Set the NDK working directory variable.
```
make gen-ndk-makefiles
export NDK_PROJECT_PATH="${PWD}"
```
 - Go to the NDK directory and start the build
```
# Required for creating clang version information and directory access
export NDK_ROOT_DIR="${PWD}"
cd "${NDK_PROJECT_PATH}" && bash build/bash/gen-header \
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
   src/      build/        obj/    libs/
                                     |
                           __________|__________
                           |                   |
                       arm64-v8a/         armeabi-v7a/
                           |                   |
                          pmt                 pmt
```

##### Build with Makefiles

```
make

# Use termux :D
```
 - For the make installable debian package:

```
make deb <ARCH_NUM>

# Examples
make deb FOR_THIS=64
make deb FOR_THIS=32
```

### Notes
If you want to change something, take a look at the configuration. You can change him.
it is located in the `build/config` folder. His name is `env.mk`. I gave the information in the file. You can ask more.
