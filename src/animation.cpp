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

inline void _fade_init() { fade_init(&parameters.fade, &state.fade); }
inline void _fade_refresh() { fade_refresh(&parameters.fade, &state.fade); }
inline void _flash_init() { flash_init(&parameters.flash, &state.flash); }
inline void _flash_refresh() { flash_refresh(&parameters.flash, &state.flash); }
inline void _spin_init() { spin_init(&parameters.spin, &state.spin); }
inline void _spin_refresh() { spin_refresh(&parameters.spin, &state.spin); }

Animation animations[] = {
    { _spin_init, _spin_refresh },    // 0x00 - spin
    { _flash_init, _flash_refresh },  // 0x01 - flash
    { _fade_init, _fade_refresh }     // 0x02 - fade
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