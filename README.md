# Cup Pong Firmware

This repository stores the Cup-Pong firmware. The firmware is written for the ATTiny85 microcontroller. It is written using the ATTinyCore Arduino core (see https://github.com/SpenceKonde/ATTinyCore).

To compile and upload the firmware, install ATTinyCore as per the instructions on the website. The following configuration settings are used:
 - Clock: 8 MHz (Internal)
 - B.O.D Disabled
 - Timer 1 Clock: CPU
 - LTO: Enabled
 - millis/micros: Enabled

When uploading the sketch it is important to disconnect Pin 6 from the Infra-Red LED, otherwise the upload check will fail.

# Important
Use the Arduino IDE to "Burn Bootloader" or the code won't work!

# Compilation Instructions

Compile using `arduino-cli`:
    arduino-cli compile --fqbn ATTinyCore:avr:attinyx5

# Programmer Type
usbasp

## To Do
 - Figure out why upload fails with IR LED connected (try moving neopixels to that pin instead because the diode is probably pulling the comms low)

## Animation Controller

The animation controller implements it's own scripting language so that animations can be loaded via the I2C bus. Each animation command is executed on each animation clock cycle. This section details the commands that may be sent.

Each command is 32 bits long. The first 4 bits identify the command, and the remaining bits are command arguments or empty.

Command (4 bits) = 16 options
LED index (4 bits) = 16 options
Colour (3 bytes)

i2c buffer size is either 16 or 32 bytes

 - `goto` - go to a specified line index of the animation command
 - `new` - create a new animation sequence
 - `start` - begin the animation sequence in memory

## Animations

The animation commands above allow the following animations to be played:
 - Solid on (turn LED's on or off any colour)
   - Arguments:
       LED index (1-8)
       
 - Fade to (fade from one colour to another colour over a given number of cycles)
 - Blink (flash a colour a specified number of times at a specified speed)
