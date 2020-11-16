# libcamera
A C library for the **Nintendo DSi** that allows the use of the built-in cameras.

## Installing

Simply clone this git repository and run `$ make` from the root of the source tree. You can also run `$ make install` to copy the library's files inside your libnds installation folder.

## Using

To use this library, make sure to append:
- `-lcamera7` for **ARM7**
- `-lcamera9` for **ARM9**

in the respective Makefiles under `LIBS	:=`

If you did not install, also append the folder containing this library under `LIBDIRS	:=`

### Note
An ARM7 binary is necessary to correctly initialize the cameras. 
Refer to to the **examples** for usage.

## Requirements

- [**devkitPro**](https://github.com/devkitPro)
- [**libnds**](https://github.com/devkitPro/libnds)

## Credits

- **NoCash** for [**GBATEK**](https://problemkaputt.de/gbatek.htm)
- My poor DSi that endured hours of use as debugging hardware.
