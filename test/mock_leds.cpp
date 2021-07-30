#include "leds.h"
#include "colour.h"

uint8_colour pixels[LED_COUNT];         // in memory
uint8_colour pixels_live[LED_COUNT];    // on LEDs

void LedController_initialise()
{
    LedController_refresh();
}

void LedController_setColour(uint16_t index, uint8_colour colour)
{
    pixels[index] = colour;
}

void LedController_setColour(uint16_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    pixels[index].red = red;
    pixels[index].green = green;
    pixels[index].blue = blue;
}

void LedController_pushColour()
{
    uint8_colour first_color = pixels[LED_COUNT-1];
    for (int i=LED_COUNT-1; i>0; i--) {
        uint8_colour color = pixels[i-1];
        pixels[i] = color;
    }
    pixels[0] = first_color;
}

uint8_colour LedController_getColour(uint16_t index)
{
    return pixels[index];
}

void LedController_refresh()
{
    for (int i=0; i<LED_COUNT; i++) {
        pixels_live[i] = pixels[i];
    }
}
