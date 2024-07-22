### Installing pmt deb packages in Termux

It's pretty simple.

###### Package selection
 - If the device is 64 bit, you should choose `arm64-v8a` package. If not, choose `armeabi-v7a` package.
 - And of course download it.

###### Setup
 - Access downloads or wherever the package is located.
 ```
 # Access downloads
 cd /sdcard/Download
 ```
 - Now it's time to set up.
 ```
 Syntax:
     apt install ./pmt-<VARIANT>.deb

 Examples:
     apt install ./pmt-armeabi-v7a.deb
     apt install ./pmt-arm64-v8a.deb
 ```
 - And enjoy!
