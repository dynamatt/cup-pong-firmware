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

# Programming

## Using USBASP
 - Programmer Type: usbasp

## Using Raspberry Pi
When programming with AVR dude, use the following configuration:

    # Linux GPIO configuration for avrdude.
    # Change the lines below to the GPIO pins connected to the AVR.
    programmer
    id    = "pi_1";
    desc  = "Use the Linux sysfs interface to bitbang GPIO lines";
    type  = "linuxgpio";
    reset = 17;
    sck   = 3;
    mosi  = 2;
    miso  = 4;
    ;

This configuration allows uploading firmwate using a Raspberry Pi without disconnecting I2C lines.

To make sure everything is plugged in and configured correctly:

    sudo avrdude -p t85 -C ~/avrdude_gpio.conf -c pi_1 -v


# Raspberry Pi Pinout

![](https://cdn.sparkfun.com/assets/learn_tutorials/1/5/9/5/GPIO.png)
