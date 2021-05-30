#include <stdint.h>
#include "animation.h"
#include "cup.h"
#include "leds.h"
#include "timer.h"
#include "animations/spin.h"
#include "animations/flash.h"

typedef struct {
    void (*init_func)();    // this function is called when an animation is initialised
    void (*refresh_func)(); // this function is called periodically to update the animation
} Animation;

Animation animations[] = {
    { spin_init, spin_refresh },    // 0x00 - spin
    { flash_init, flash_refresh }   // 0x01 - flash
};

union Parameters {
    SpinParams spin;
    FlashParams flash;
};

union State {
    SpinState spin;
    FlashState flash;
};

// parameters and state for the current animation
union Parameters parameters;
union State state;

void AnimationController_initialise()
{
    Timer1.initialize(LED_REFRESH_INTERVAL_us);

    // temp
    parameters.spin.speed = 100;
    parameters.spin.colour = { 100, 0, 0};
    spin_init();
    Timer1.attachInterrupt(spin_refresh);

    Timer1.start();
}

void AnimationController_setAnimation(uint8_t* animation)
{

}

/****************
 * Spin Animation
 ****************/
void spin_init()
{
    state.spin.count = 0;
    LedController_setColour(0, parameters.spin.colour);
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

}

void flash_refresh()
{

}