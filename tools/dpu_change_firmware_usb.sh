#!/bin/bash
# Run as sudo if needed

dfu-programmer atmega16u2 erase
dfu-programmer atmega16u2 flash ./lib-src/IoT/firmwares/Arduino-dfu-usbserial-atmega16u2-Uno-Rev3.hex --suppress-bootloader-mem
dfu-programmer atmega16u2 reset
