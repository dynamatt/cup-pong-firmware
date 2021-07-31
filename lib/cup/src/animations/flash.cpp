#include <stdint.h>
#include "leds.h"
#include "flash.h"

void flash_init(FlashParams *params, FlashState *state)
{
    state->count = 0;
    state->repeat_count = 0;

    state->turn_on = params->ramp_up_time;
    state->ramp_down = state->turn_on + params->on_time;
    state->turn_off = state->ramp_down + params->ramp_down_time;
    state->ramp_up = state->turn_off + params->off_time;

    if (params->ramp_up_time > 0) {
        state->ramp_up_diff = divide(convert_to_uint16(params->colour), params->ramp_up_time);
    }

    if (params->ramp_down_time > 0) {
        state->ramp_down_diff = divide(convert_to_uint16(params->colour), params->ramp_down_time);
    }

    // initial state is off, ramping up
    state->current_colour = (uint16_colour) {0, 0, 0};
    state->current_diff = state->ramp_up_diff;
    state->diff_func = add;
}

void flash_refresh(FlashParams *params, FlashState *state)
{
    if (params->repeat > 0 && state->repeat_count >= params->repeat)
    {
        return;
    }

    state->count++;

    if (state->count == state->turn_on) {
        // change to on
        state->current_diff = (uint16_colour) {0, 0, 0};
        state->current_colour = convert_to_uint16(params->colour);
    }
    if (state->count == state->ramp_down) {
        // start ramping down
        state->current_diff = state->ramp_down_diff;
        state->diff_func = subtract;
    } 
    if (state->count == state->turn_off) {
        // change to off
        state->current_diff = (uint16_colour) {0, 0, 0};
        state->current_colour = (uint16_colour) {0, 0, 0};
    }
    if (state->count == state->ramp_up) {
        // start ramping up
        state->current_diff = state->ramp_up_diff;
        state->diff_func = add;
        state->count = 0;
        state->repeat_count++;
    }

    state->current_colour = state->diff_func(state->current_colour, state->current_diff);

    uint8_colour new_colour = convert_to_uint8(state->current_colour);
    for (int i=0; i<LED_COUNT; i++) {
        LedController_setColour(i, new_colour);
    }
    LedController_refresh();
}
