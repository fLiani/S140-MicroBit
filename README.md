# FAB'S BUILD:

Firstly, change the .o files in the codal-microbit-v2/lib to the ones I have provided inside "S140 O FILES" in the root directory

My nrf52833-softdevice.ld file starts like this:

MEMORY
{
  MBR (rx) : ORIGIN = 0x0000, LENGTH = 0x1000
  SD (rx) : ORIGIN = 0x1000, LENGTH = 0x26000
  FLASH (rx) : ORIGIN = 0x27000, LENGTH = 0x72000 - 0x27000
  BOOTLOADER (rx) : ORIGIN = 0x72000, LENGTH = 0x7E000 - 0x72000
  SETTINGS (rx) : ORIGIN = 0x7E000, LENGTH = 0x2000
  UICR (rx) : ORIGIN = 0x10001014, LENGTH = 0x8
  NOINIT (rwx) : ORIGIN = 0x20002030, LENGTH = 0x20002040 - 0x20002030
  RAM (rwx) : ORIGIN = 0x20002440, LENGTH = 0x20000 - 0x2440
}
OUTPUT_FORMAT ("elf32-littlearm", "elf32-bigarm", "elf32-littlearm")
ENTRY(Reset_Handler)
SECTIONS
{
    . = ALIGN(4);
    .mbr :
    {
        KEEP(*(.mbr))
    } > MBR

    . = ALIGN(4);
    .softdevice :
    {
        KEEP(*(.softdevice))
    } > SD
    
    . = ALIGN(4);
    .bootloader :
    {
        KEEP(*(.bootloader))
    } > BOOTLOADER

    . = ALIGN(4);
    .uicr :
    {
        KEEP(*(.uicr))
    } > UICR

    . = ALIGN(4);
    .settings :
    {
        KEEP(*(.settings))
    } > SETTINGS
    
    .text :
    {
        KEEP(*(.isr_vector))
        KEEP(*(.Vectors))
        *(.text*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *crtbegin.o(.ctors)
        *crtbegin?.o(.ctors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .ctors)
        *(SORT(.ctors.*))
        *(.ctors)
        *crtbegin.o(.dtors)
        *crtbegin?.o(.dtors)
        *(EXCLUDE_FILE(*crtend?.o *crtend.o) .dtors)
        *(SORT(.dtors.*))
        *(.dtors)
        *(.rodata*)
        KEEP(*(.eh_frame*))
    } > FLASH

I have also changed both libraries/codal-microbit-v2/target-locked.json and /target.json to:

Line 48 (definitions):     "definitions": "-DAPP_TIMER_V2 -DAPP_TIMER_V2_RTC1_ENABLED -DNRF_DFU_TRANSPORT_BLE=1 -DSOFTDEVICE_PRESENT -DNRF52833_XXAA -DNRF52833 -DTARGET_MCU_NRF52833 -DNRF5 -DNRF52833 -D__CORTEX_M4 -DS140 -DTOOLCHAIN_GCC -D__START=target_start",

Lastly, inside libraries/codal-microbit-nrf5sdk/CMakeLists.txt I have changed both lines 81 and 100 to include S140 headers instead of S113. Change "S113" to "S140"



# microbit-v2-samples

[![Native Build Status](https://github.com/lancaster-university/microbit-v2-samples/actions/workflows/build.yml/badge.svg)](https://github.com/lancaster-university/microbit-v2-samples/actions/workflows/build.yml) [![Docker Build Status](https://github.com/lancaster-university/microbit-v2-samples/actions/workflows/docker-image.yml/badge.svg)](https://github.com/lancaster-university/microbit-v2-samples/actions/workflows/docker-image.yml)

This repository provides the necessary tooling to compile a C/C++ CODAL program for the micro:bit V2 and generate a HEX file that can be downloaded to the device.

## Raising Issues
Any issues regarding the micro:bit are gathered on the [lancaster-university/codal-microbit-v2](https://github.com/lancaster-university/codal-microbit-v2) repository. Please raise yours there too.

# Installation
You need some open source pre-requisites to build this repo. You can either install these tools yourself, or use the docker image provided below.

- [GNU Arm Embedded Toolchain](https://developer.arm.com/tools-and-software/open-source-software/developer-tools/gnu-toolchain/gnu-rm/downloads)
- [Git](https://git-scm.com)
- [CMake](https://cmake.org/download/)
- [Python 3](https://www.python.org/downloads/)

We use Ubuntu Linux for most of our tests. You can also install these tools easily through the package manager:

```
    sudo apt install gcc
    sudo apt install git
    sudo apt install cmake
    sudo apt install gcc-arm-none-eabi binutils-arm-none-eabi
```

## Yotta
For backwards compatibility with [microbit-samples](https://github.com/lancaster-university/microbit-samples) users, we also provide a yotta target for this repository.

## Docker
You can use the [Dockerfile](https://github.com/lancaster-university/microbit-v2-samples/blob/master/Dockerfile) provided to build the samples, or your own project sources, without installing additional dependencies.

Run the following command to build the image locally; the .bin and .hex files from a successful compile will be placed in a new `out/` directory:

```
    docker build -t microbit-tools --output out .
```

To omit the final output stage (for CI, for example) run without the `--output` arguments:

```
    docker build -t microbit-tools .
```

# Building
- Clone this repository
- In the root of this repository type `python build.py`
- The hex file will be built `MICROBIT.hex` and placed in the root folder.

# Developing
You will find a simple main.cpp in the `source` folder which you can edit. CODAL will also compile any other C/C++ header files our source files with the extension `.h .c .cpp` it finds in the source folder.

The `samples` folder contains a number of simple sample programs that utilise you may find useful.

## Developer codal.json

There is an example `coda.dev.json` file which enables "developer builds" (clones dependencies from the latest commits, instead of the commits locked in the `codal-microbit-v2` tag), and adds extra CODAL flags that enable debug data to be printed to serial.
To use it, simply copy the additional json entries into your `codal.json` file, or you can replace the file completely (`mv coda.dev.json codal.json`).

# Debugging
If you are using Visual Studio Code, there is a working debugging environment already set up for you, allowing you to set breakpoints and observe the micro:bit's memory. To get it working, follow these steps:

1. Install either [OpenOCD](http://openocd.org) or [PyOCD](https://github.com/pyocd/pyOCD).
2. Install the [`marus25.cortex-debug` VS Code extension](https://marketplace.visualstudio.com/items?itemName=marus25.cortex-debug).
3. Build your program.
4. Click the Run and Debug option in the toolbar.
5. Two debugging options are provided: one for OpenOCD, and one for PyOCD. Select the correct one depending on the debugger you installed.

This should launch the debugging environment for you. To set breakpoints, you can click to the left of the line number of where you want to stop.

# Compatibility
This repository is designed to follow the principles and APIs developed for the first version of the micro:bit. We have also included a compatibility layer so that the vast majority of C/C++ programs built using [microbit-dal](https://www.github.com/lancaster-university/microbit-dal) will operate with few changes.

# Documentation
API documentation is embedded in the code using doxygen. We will produce integrated web-based documentation soon.
