#include <stdint.h>
#include "leds.h"
#include "fade.h"

#define FADE_BIT_SHIFTS 6

void fade_init(FadeParams* params, FadeState* state)
{
    int16_t r = params->colour.red << FADE_BIT_SHIFTS;
    int16_t g = params->colour.green << FADE_BIT_SHIFTS;
    int16_t b = params->colour.blue << FADE_BIT_SHIFTS;
    for (int i=0; i<LED_COUNT; i++) {
        uint8_colour initial_colour = LedController_getColour(i);
        state->current_colour[i].red = initial_colour.red << FADE_BIT_SHIFTS;
        state->current_colour[i].green = initial_colour.green << FADE_BIT_SHIFTS;
        state->current_colour[i].blue = initial_colour.blue << FADE_BIT_SHIFTS;

        state->diff[i].red = (state->current_colour[i].red - r) / params->duration;
        state->diff[i].green = (state->current_colour[i].green - g) / params->duration;
        state->diff[i].blue = (state->current_colour[i].blue - b) / params->duration;
    }
    
    state->count = params->duration;
}

void fade_refresh(FadeParams* params, FadeState* state)
{
    if (state->count > 0)
    {
        for (int i=0; i<LED_COUNT; i++) 
        {
            state->current_colour[i].red = state->current_colour[i].red - state->diff[i].red;
            state->current_colour[i].green = state->current_colour[i].green - state->diff[i].green;
            state->current_colour[i].blue = state->current_colour[i].blue - state->diff[i].blue;
            LedController_setColour(i, 
                (state->current_colour[i].red >> FADE_BIT_SHIFTS),
                (state->current_colour[i].green >> FADE_BIT_SHIFTS),
                (state->current_colour[i].blue >> FADE_BIT_SHIFTS));
        }

        state->count--;

        // in case the rounding isn't exactly right
        if (state->count == 0)
        {
            for (int i=0; i<LED_COUNT; i++)
            {
                //LedController_setColour(i, params->colour);
            }
        }

        LedController_refresh();
    }
}