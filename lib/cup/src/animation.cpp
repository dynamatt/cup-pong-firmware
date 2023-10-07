#include <stddef.h>
#include <stdint.h>
#include "animation.h"
#include "animations/spin.h"
#include "animations/flash.h"
#include "animations/fade.h"
#include "animations/test.h"
#include "timer.h"

typedef struct {
    void (*init_func)();    // this function is called when an animation is initialised
    void (*refresh_func)(); // this function is called periodically to update the animation
} Animation;

union Parameters {
    SpinParams spin;
    FlashParams flash;
    FadeParams fade;
    TestParams test;
};

union State {
    SpinState spin;
    FlashState flash;
    FadeState fade;
    TestState test;
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
inline void _test_init() { test_init(&parameters.test, &state.test); }
inline void _test_refresh() { test_refresh(&parameters.test, &state.test); }

Animation animations[] = {
    { _spin_init, _spin_refresh },    // 0x00 - spin
    { _flash_init, _flash_refresh },  // 0x01 - flash
    { _fade_init, _fade_refresh },    // 0x02 - fade
    { _test_init, _test_refresh }     // 0x03 - test
};

void (*refresh_func)() = NULL;

void update()
{
    Timer_stop();
    if (refresh_func != NULL)
    {
        refresh_func();
    }

    Timer_start();
}

void AnimationController_initialise(uint64_t period)
{
    Timer_initialize(period);
    Timer_attachInterrupt(update);
}

void AnimationController_setAnimation(uint8_t animation, uint8_t* params, uint8_t length)
{
    Timer_stop();
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
    refresh_func = animations[animation].refresh_func;
    Timer_start();
}