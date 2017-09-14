#!/bin/bash
# Run as sudo if needed

dfu-programmer atmega16u2 erase
dfu-programmer atmega16u2 flash ./lib-src/IoT/firmwares/arduino_midi.hex --suppress-bootloader-mem
dfu-programmer atmega16u2 reset
