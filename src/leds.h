#ifndef LEDS_H
#define LEDS_H

#include <stdint.h>
#include "colour.h"

void LedController_initialise();
void LedController_setColour(uint8_t, uint8_t, uint8_t, uint8_t);
void LedController_setColour(uint8_t, uint8_colour);
void LedController_refresh();
void LedController_pushColour();

#endif