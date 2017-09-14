#!/bin/bash
# Run as sudo if needed

if [[ -z $1 ]]; then
    echo "USAGE: ./dpu_change_firmware.sh <HEX_FILE>";
    exit;
fi

dfu-programmer atmega16u2 erase
dfu-programmer atmega16u2 flash $1 $2
dfu-programmer atmega16u2 reset

# ~/Sources/hiduino/src/arduino_midi/arduino_midi.hex
# ./lib-src/IoT/firmwares/Arduino-dfu-usbserial-atmega16u2-Uno-Rev3.hex
