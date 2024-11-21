[![Website](https://img.shields.io/badge/Website-Link-blue.svg)](https://gavinlyonsrepo.github.io/)  [![Rss](https://img.shields.io/badge/Subscribe-RSS-yellow.svg)](https://gavinlyonsrepo.github.io//feed.xml)  [![Donate](https://img.shields.io/badge/Donate-PayPal-green.svg)](https://www.paypal.com/paypalme/whitelight976)

# ST7789 TFT LCD Raspberry PI Display Library

[![Image TFT](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/st7789.jpg)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/st7789.jpg)

## Table of contents

  * [Overview](#overview)
  * [Installation](#installation)
  * [Test](#test)
  * [Documentation](#documentation)
    * [API documentation](#api-documentation)
    * [Fonts](#fonts)
  * [Software](#software)
    * [User options](#user-options)
    * [File-system](#file-system)
    * [Tool chain](#tool-chain)
  * [Hardware](#hardware)
  * [Output](#output)
  * [Notes](#notes)
    * [Multiple SPI devices](#multiple-spi-devices)
    * [Raspberry Pi five](#raspberry-pi-five)
    * [Display offsets](#display-offsets)

## Overview

* Project Name: ST7789_TFT_RPI
* Author: Gavin Lyons.
* Description:

0. A C++ Library to connect 16-bit color ST7789 TFT LCD displays to Raspberry Pi single board computers.
1. Dynamic install-able Raspberry Pi C++ library.
2. 15 fonts included, new Fonts can be added by user
3. Graphics + print class included
4. Dependency: [bcm2835 Library](http://www.airspayce.com/mikem/bcm2835/), Provides SPI , system timer and GPIO control.
5. Hardware & Software SPI
6. Inverse colour, rotate, sleep modes supported.
7. 24 bit colour , 16 bit color & bi-color Bitmaps supported.
8. Note : This is a truncated port of combined display library : [Display_Lib_RPI.](https://github.com/gavinlyonsrepo/Display_Lib_RPI) created for a user request.

## Installation

1. Install the dependency bcm2835 Library if not installed
	* Install the C libraries of bcm2835, [Installation instructions here](http://www.airspayce.com/mikem/bcm2835/)

2. Download the ST7789_TFT_RPI library
	* Open a Terminal in a folder where you want to download,build & test library
	* Run following command to download latest release from github.

```sh
curl -sL https://github.com/gavinlyonsrepo/ST7789_TFT_RPI/archive/1.0.1.tar.gz | tar xz
```

3. Run 'make' and 'sudo make install' to run the makefile to build and then install library. 
	* It will be installed to usr/local/lib and usr/local/include by default. 
	* You can run 'make help' here to see other make options(uninstall etc).

```sh
cd ST7789_TFT_RPI-1.0.1
make
sudo make install
```

## Test

1. Next step is to test your display and installed library with the included test example files, connect display.
2. Enter the example folder.
3. Edit the makefile in that folder to select the example file path.
		Simply edit "SRC" variable at top of the makefile. In the "User SRC directory Option Section" at top of file.
		Pick an example "SRC" directory path and One ONLY.
5. Run 'make' commmand. This builds the examples file using the just installed library,
		and creates a test executable file in "Bin".
6. Run 'make run' to run that built executable file. 
	This wraps "sudo" as the bcm2835 requires root permissions by default.
7. User should now see the test routine in that file running on the display. Run 'make help' to see other options.

```sh
cd examples
make
make run
```

## Documentation


### API Documentation

The code is commented for Doxygen API generation software. Run doxygen on the file 'doxygen_docs_generate_file' to generate API in the 'doxygen_API_docs_output' folder

### Fonts

The font system is same as used in Display_Lib_RPI 'mother' library , [is documented here at link.](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/doc/fonts/README.md)

## Software

### User options

In the example files. There are 3 sections in "Setup()" function 
where user can make adjustments to select for SPI type used, and screen size.

1. USER OPTION 1 GPIO/SPI TYPE
2. USER OPTION 2 SCREEN SECTION 
3. USER OPTION 3 SPI SPEED , SPI_CE_PIN

*USER OPTION 1 SPI TYPE / GPIO*

This library supports both Hardware SPI and software SPI.
The SetupGPIO function is overloaded(2 off one for HW SPI the other for SW SPI).
The parameters set for SetupGPIO define which is used.
HW SPI is far faster and more reliable than SW SPI

*USER OPTION 2 Screen size  + Offsets*

User can adjust screen pixel height, screen pixel width and x & y screen offsets.
These offsets can be used in the event of screen damage or manufacturing errors around edge 
such as cropped data or defective pixels.
The function InitScreenSize sets them.

*USER OPTION 3  SPI SPEED , SPI_CE_PIN*

InitSPI function is overloaded(2 off, one for HW SPI the other for SW SPI).

Param SPI_Speed (HW SPI Only)

Here the user can pass the SPI Bus freq in Hertz,
Maximum 125 Mhz , Minimum 30Khz, The default in file is 8Mhz 
Although it is possible to select high speeds for the SPI interface, up to 125MHz,
Don't expect any speed faster than 32MHz to work reliably.
If you set to 0 .Speed is set to bcm2835 constant BCM2835_SPI_CLOCK_DIVIDER_32.

Param SPI_CE_PIN (HW SPI Only)

Which Chip enable pin to use two choices.
	* SPICE0 = 0
	* SPICE1 = 1

Param SPI_CommDelay (SW SPI Only)

The user can adjust If user is having reliability issues with SW SPI in some setups.
This is a microsecond delay in SW SPI GPIO loop. It is set to 0 by default, Increasing it will slow 
down SW SPI further.

### File system

In example folder:
The Main.cpp file contains tests showing library functions.
A bitmap data file contains data for bi-color bitmaps and icons tests.
The color bitmaps used in testing are in bitmap folder.
Examples are set up for 90 degree rotation for a 240X320 display.

| # | example file name  | Desc|
| ------ | ------ |  ------ |
| 1 | Hello_world| Basic use case |
| 2 | Text_Graphic_Functions | Tests text,graphics & function testing  |
| 3 | Bitmap_Tests | bitmap |
| 4 | Frame_rate_test_bmp | Frame rate per second (FPS) bitmaps |

There are 2 makefiles.

1. Root directory, builds and installs library at a system level.
2. Example directory  builds a chosen example file using installed library to an executable.
which can then be run.

Library naming :

1. Library name = librpist7789gl
2. Linker flags for complier = -lrpist7789gl (also needs -lbcm2835 for bcm2835 library)
3. Library File suffix  = RVL
4. Project name = ST7789_TFT_RPI

### Tool chain

* Development Tool chain.
	1. Raspberry PI 3 model b ( will not work on RPi 5 see notes)
	2. C++, g++ (Debian 12.2.0)
	3. Raspbian , Debian 12 bookworm OS, 64 bit.
	4. kernel : aarch64 Linux 6.1.0-rpi7-rpi-v8
	5. bcm2835 Library v1.75 dependency.

## Hardware

Tested and developed on:

* Size 1.69" IPS color TFT LCD
* Resolution: 240 (H) RGB x280 (V)
* Control chip: st7789v2
* Display area 27.972 (H) x 32.634 (V)
* Panel size 30.07 (H) x37.43 (V) x1.56 (d)
* Logic voltage 3.3V

Connections as setup in main.cpp test file.

| TFT PinNum | Pindesc | RPI HW SPI | RPI SW SPI |
| --- | --- | --- | --- |
| 1 | LED | VCC |  VCC |
| 2 | SS/CS | SPI_CE0 | GPIO8 |
| 3 | DC | GPIO24 | GPIO24  |
| 4 | RESET | GPI025  | GPIO25 |
| 5 | SDA | SPI_MOSI | GPIO6 |
| 6 | SCLK | SPI_CLK | GPIO5 |
| 7 | VCC | VCC | VCC  |
| 8 | GND | GND | GND |

1. Connect LED backlight pin 1 thru a resistor to VCC.
2. This is a 3.3V logic device do NOT connect the I/O logic lines to 5V logic device.
3. Pick any GPIO you want for SW SPI,  for HW SPI: reset and DC lines are flexible.
4. User can select  SPI_CE0  or SPI_CE1 for HW SPI
5. Backlight control is left to user.

## Output

[![output pic](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/st7789output.jpg)](https://github.com/gavinlyonsrepo/Display_Lib_RPI/blob/main/extra/images/st7789output.jpg)

## Notes

### Multiple SPI devices

When using hardware SPI for multiple devices on the bus.
If the devices require different SPI settings (speed of bus, bit order , chip enable pins , SPI data mode).
The user must call function **TFTSPIHWSettings()** before each block of SPI transactions for display in order to refresh the SPI hardware settings for that device. See github [issue #1](https://github.com/gavinlyonsrepo/Display_Lib_RPI/issues/1).

### Raspberry Pi five

Will not work on Raspberry 5 at present as the bcm2835 Library dependency is not updated
to work yet on Rpi5.

### Display offsets

The display initialisation requires an offset calculation which differs for different size and resolution displays.
This is in the code(Function AdjustWidthHeight()) but the many different size displays are not available for testing or dealt with.
If using a display other than 240x320(the default and size of ST7789 VRAM) and if user finds they cannot address all screen
or their data is offset. Try Setting the pixel width and height of your screen to 240X320 and do not write as 
much as possible to the part of the Video RAM you cannot see.
For example  if you have a 240X280 display in 0 degree rotation
1. Set pixel Width = 240 and pixel height = 320
2. Do not write to the missing 40 pixels in the Y-axis, you still can but it is inefficient.

