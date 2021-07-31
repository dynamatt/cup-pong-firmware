# Cup Pong Firmware

This repository stores the Cup-Pong firmware. The firmware is written for the ATTiny85 microcontroller. It is written using the ATTinyCore Arduino core (see https://github.com/SpenceKonde/ATTinyCore).

The following configuration settings are used:
 - Clock: 8 MHz (Internal)
 - B.O.D Disabled
 - Timer 1 Clock: CPU
 - LTO: Enabled
 - millis/micros: Enabled

# Compilation Instructions
*Before loading the firmware, the Arduino Bootloader must be loaded using the "Burn Bootloader" command on the Arduino IDE.*

To compile and run using `platformio`:

    pio run -e attiny85

# Programmer Type
 - Programmer Type: usbasp
