#include <math.h>
#include "leds.h"
#include "test.h"
#include "../io.h"
#include "../ball.h"

void test_init(TestParams *params, TestState *state)
{
    state->count = params->duration;
    state->color_index = 1;
}

void test_refresh(TestParams *params, TestState *state)
{
    state->count--;
    if (state->count == 0)
    {
        if (state->tx_enabled)
        {
            IO_disableTransmitter();
        }
        else
        {
            IO_enableTransmitter();
        }
        state->tx_enabled = !state->tx_enabled;
        state->count = params->duration;
        // state->color_index = state->color_index << 1;
        // if (state->color_index > 4) {
        //     state->color_index = 1;
        // }
    }

    uint16_t min_adc, max_adc;
    BallDetector_isBallDetected(&min_adc, &max_adc);

    uint16_t value = (uint16_t)(2560*sqrt(max_adc) / 32.0); // 32 = sqrt(1024) [0-2559]

    for (int i=0; i<8; i++)
    {
        uint8_t led_value;
        if (value > 255) {
            led_value = 255;
            value -= 256;
        }
        else
        {
            led_value = (uint8_t)value;
            value = 0;
        }

        uint8_t red_value = (((state->color_index & 0x01)>>0) * 0xFF) & led_value;
        uint8_t green_value = (((state->color_index & 0x02)>>1) * 0xFF) & led_value;
        uint8_t blue_value = (((state->color_index & 0x04)>>2) * 0xFF) & led_value;

        LedController_setColour(i, red_value, green_value, blue_value);
    }

    LedController_refresh();
}