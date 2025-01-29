## Partition Manager Installatation Guide
In this guide, I will give a tutorial on how to install `pmt`.

### On Termux
The simplest installation in this guide is the one to be performed on termux. Because I wrote a [**script**](https://github.com/ShawkTeam/pmt/blob/3.0.2/pmt-termux.sh) for it...
   - First of all, if it is not installed, you should install termux from [**F-Droid**](https://f-droid.org/packages/com.termux/) (I recommend F-Droid).
   - In general (**if you have installed termux for the first time**), it is recommended to update the packages. You can use the command below;
   ```
   pkg update && pkg upgrade -y
   ```
   - Now all you have to do is download the script.
   ```
   curl -LSs https://github.com/ShawkTeam/pmt/raw/3.0.2/pmt-termux.sh > pmt-termux.sh
   ```
   - You need to prepare your environment. The script can do this for you;
   ```
   bash pmt-termux.sh setup
   ```
   - Now, install `pmt` on Termux...
   ```
   bash pmt-termux.sh install
   ```
   - To get information about the script (usage etc.);
   ```
   bash pmt-termux.sh --help
   ```
   - From now on, you can use `pmt` on termux. If you reinstall termux or clear its memory, you need to install it again with these steps.
   - For proper use of pmt, you need to use `tsu`. `tsu` works in a Termux environment, compared to the '`su`' command. We need this too. So, you should use '`tsu`' instead of '`su`' command for root access.
   ```
   tsu
   # You have now accessed root!

   # If you don't want to go to the root environment exactly, you can run one-time root-accessible commands with sudo
   sudo <commands>

   # Example:
   sudo pmt --help
   ```

##### **NOTES:**
   - You must be connected to the **Internet** when performing these operations.
   - Root access is **not required** during the installation process, do not use it!

### On Custom Recovery
You have 2 options for installing `pmt` on recovery (**one-time**)...
  - With PC, **needed a compatibility cable**.
  - Installing it in a recovery that can **decrypt internal storage**.

##### Installing with PC
   - You need to install [**platform tools**](https://developer.android.com/tools/releases/platform-tools) or [**minimal ADB**](https://androidmtk.com/download-minimal-adb-and-fastboot-tool) on your computer. And of course, both USB drives (you should find them).
   - You should download and extract `pmt` from [**publications**](https://github.com/ShawkTeam/pmt/releases) (there are many programs that can do this).
   - Enter the recovery mode on the device. Connect the USB cable. Make sure that the device is connected.
   - Now, we need to send the `pmt` to the device and set permissions.
   ```
   # Send to device
   adb push <PMT_FILE_PATH> /system/bin/pmt

   # Set permissions for pmt
   adb shell chmod 755 /system/bin/pmt
   ```
   - Now you can use `pmt` with the `adb shell` or via the recovery terminal.

**NOTES:**
  - You can easily learn how to use ADB from videos on youtube or guides on the Internet.

##### Non-PC installing method
   - You should download and extract `pmt` from [**publications**](https://github.com/ShawkTeam/pmt/releases) (there are many programs that can do this, example: [**ZArchiver**](https://play.google.com/store/apps/details?id=ru.zdevs.zarchiver)).
   - The file you are extracting must be in internal storage!
   - Enter the recovery mode and go to the terminal;
   ```
   cp /sdcard/pmt /system/bin
   chmod 755 /system/bin/pmt
   ```
   - Now you can use `pmt` with the `adb shell` or via the recovery terminal.

**NOTES:**
  - Make sure the internal storage is **mounted**! In short, you can understand this as follows: **do the files in the internal storage appear?**

### General Notes
   - Is there a place that you hang out, that you don't understand, that's a **problem**? Contact us from our [**telegram group** (pmt topic)](https://t.me/shawkbuilddiscussion/19875)!
