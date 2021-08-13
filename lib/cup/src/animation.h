#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>

void AnimationController_initialise(uint64_t period);
void AnimationController_setAnimation(uint8_t animation, uint8_t* params, uint8_t length);

#endif