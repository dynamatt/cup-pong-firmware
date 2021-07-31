#include <stdint.h>
#include "leds.h"
#include "spin.h"

void spin_init(SpinParams* params, SpinState* state)
{
    state->count = 0;

    // check for invalid parameters
    if (params->tail > LED_COUNT || params->tail < 1) return;

    for (int i=0; i<LED_COUNT; i++) {
        LedController_setColour(i, 0, 0, 0);
    }

    for (uint16_t i=0; i<params->tail; i++) {
        LedController_setColour(
            params->tail - i,
            params->colour.red >> i,
            params->colour.green >> i,
            params->colour.blue >> i
        );
    }
}

void spin_refresh(SpinParams* params, SpinState* state)
{
    state->count++;
    
    if (state->count == params->speed) {
        LedController_pushColour();
        LedController_refresh();
        state->count = 0;
    }
}
