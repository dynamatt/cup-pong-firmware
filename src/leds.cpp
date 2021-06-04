#include <Arduino.h>
#include <tinyNeoPixel_Static.h> 
#include "leds.h"
#include "colour.h"
#include "cup.h"

uint8_t pixels[LED_COUNT*3];
tinyNeoPixel leds = tinyNeoPixel(LED_COUNT, LED_PIN, NEO_GRB, pixels);

void LedController_initialise()
{
    pinMode(LED_PIN, OUTPUT); 
    for (int i=0; i<LED_COUNT; i++)
    {
        leds.setPixelColor(i, 0, 0, 0);
    }
    leds.show();
}

void LedController_setColour(uint8_t index, uint8_colour colour)
{
    leds.setPixelColor(index, colour.red, colour.green, colour.blue);
}

void LedController_setColour(uint8_t index, uint8_t red, uint8_t green, uint8_t blue)
{
    leds.setPixelColor(index, red, green, blue);
}

void LedController_pushColour()
{
    uint32_t first_color = leds.getPixelColor(LED_COUNT-1);
    for (int i=LED_COUNT-1; i>0; i--) {
        uint32_t color = leds.getPixelColor(i-1);
        leds.setPixelColor(i, color);
    }
    leds.setPixelColor(0, first_color);
}

void LedController_refresh()
{
    leds.show();
}
