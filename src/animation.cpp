#include <stdint.h>
#include "animation.h"
#include "cup.h"
#include "leds.h"
#include "timer.h"
#include "animations/spin.h"
#include "animations/flash.h"
#include "animations/fade.h"

typedef struct {
    void (*init_func)();    // this function is called when an animation is initialised
    void (*refresh_func)(); // this function is called periodically to update the animation
} Animation;

union Parameters {
    SpinParams spin;
    FlashParams flash;
    FadeParams fade;
};

union State {
    SpinState spin;
    FlashState flash;
    FadeState fade;
};

// parameters and state for the current animation
union Parameters parameters;
union State state;

void fade_init_a() { fade_init(&parameters.fade, &state.fade); };
void fade_refresh_a() { fade_refresh(&parameters.fade, &state.fade); }

Animation animations[] = {
    { spin_init, spin_refresh },    // 0x00 - spin
    { flash_init, flash_refresh },  // 0x01 - flash
    { fade_init_a, fade_refresh_a }     // 0x02 - fade
};

void AnimationController_initialise()
{
    Timer1.initialize(LED_REFRESH_INTERVAL_us);

    // spin
    //SpinParams temp = { {255, 0, 0}, 50, 8 };
    //AnimationController_setAnimation(0, (uint8_t*)&temp, sizeof(SpinParams));

    // flash
    // FlashParams temp = { {255, 0, 255}, 500, 200, 500, 200, 3};
    // AnimationController_setAnimation(1, (uint8_t*)&temp, sizeof(FlashParams));

    //fade
    for (int i=0; i<LED_COUNT; i++) LedController_setColour(i, 255, 0, 0);
    LedController_refresh();
    FadeParams temp = { {0, 255, 255}, 3000 };
    AnimationController_setAnimation(2, (uint8_t*)&temp, sizeof(FadeParams));
}

void AnimationController_setAnimation(uint8_t animation, uint8_t* params, uint8_t length)
{
    Timer1.stop();
    uint8_t *param_buf = (uint8_t*)(&parameters);

    if (animation >= sizeof(animations) / sizeof(Animation)) {
        return;
    }

    if (length > sizeof(Parameters)) {
        return;
    }

    for (int i=0; i<length; i++)
    {
        param_buf[i] = params[i];
    }

    animations[animation].init_func();
    Timer1.attachInterrupt(animations[animation].refresh_func);
    Timer1.start();
}

/****************
 * Spin Animation
 ****************/
void spin_init()
{
    state.spin.count = 0;

    // check for invalid parameters
    if (parameters.spin.tail > LED_COUNT || parameters.spin.tail < 1) return;

    for (int i=0; i<LED_COUNT; i++) {
        LedController_setColour(i, 0, 0, 0);
    }

    for (uint16_t i=0; i<parameters.spin.tail; i++) {
        // uint16_t numerator = parameters.spin.tail - i;
        // LedController_setColour(
        //     numerator, 
        //     numerator * parameters.spin.colour.red / parameters.spin.tail,
        //     numerator * parameters.spin.colour.green / parameters.spin.tail,
        //     numerator * parameters.spin.colour.blue / parameters.spin.tail);

        LedController_setColour(
            parameters.spin.tail - i,
            parameters.spin.colour.red >> i,
            parameters.spin.colour.green >> i,
            parameters.spin.colour.blue >> i
        );
    }
}

void spin_refresh()
{
    state.spin.count++;
    
    if (state.spin.count == parameters.spin.speed) {
        LedController_pushColour();
        LedController_refresh();
        state.spin.count = 0;
    }
}

/*****************
 * Flash Animation
 *****************/
void flash_init()
{
    state.flash.count = 0;
    state.flash.repeat_count = 0;

    state.flash.turn_on = parameters.flash.ramp_up_time;
    state.flash.ramp_down = state.flash.turn_on + parameters.flash.on_time;
    state.flash.turn_off = state.flash.ramp_down + parameters.flash.ramp_down_time;
    state.flash.ramp_up = state.flash.turn_off + parameters.flash.off_time;

    if (parameters.flash.ramp_up_time > 0) {
        state.flash.ramp_up_diff = divide(convert_to_uint16(parameters.flash.colour), parameters.flash.ramp_up_time);
    }

    if (parameters.flash.ramp_down_time > 0) {
        state.flash.ramp_down_diff = divide(convert_to_uint16(parameters.flash.colour), parameters.flash.ramp_down_time);
    }

    // initial state is off, ramping up
    state.flash.current_colour = {0, 0, 0};
    state.flash.current_diff = state.flash.ramp_up_diff;
    state.flash.diff_func = add;
}

void flash_refresh()
{
    if (parameters.flash.repeat > 0 && state.flash.repeat_count >= parameters.flash.repeat)
    {
        return;
    }

    state.flash.count++;

    if (state.flash.count == state.flash.turn_on) {
        // change to on
        state.flash.current_diff = {0, 0, 0};
        state.flash.current_colour = convert_to_uint16(parameters.flash.colour);
    }
    if (state.flash.count == state.flash.ramp_down) {
        // start ramping down
        state.flash.current_diff = state.flash.ramp_down_diff;
        state.flash.diff_func = subtract;
    } 
    if (state.flash.count == state.flash.turn_off) {
        // change to off
        state.flash.current_diff = {0, 0, 0};
        state.flash.current_colour = {0, 0, 0};
    }
    if (state.flash.count == state.flash.ramp_up) {
        // start ramping up
        state.flash.current_diff = state.flash.ramp_up_diff;
        state.flash.diff_func = add;
        state.flash.count = 0;
        state.flash.repeat_count++;
    }

    state.flash.current_colour = state.flash.diff_func(state.flash.current_colour, state.flash.current_diff);

    uint8_colour new_colour = convert_to_uint8(state.flash.current_colour);
    for (int i=0; i<LED_COUNT; i++) {
        LedController_setColour(i, new_colour);
    }
    LedController_refresh();
}
