#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include "colour.h"

#define LED_COUNT 8

void LedController_initialise();
void LedController_setColour(uint16_t, uint8_t, uint8_t, uint8_t);
void LedController_setColour(uint16_t, uint8_colour);
uint8_colour LedController_getColour(uint16_t);
void LedController_refresh();
void LedController_pushColour();

#endif