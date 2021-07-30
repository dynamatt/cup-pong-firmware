#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>

void AnimationController_initialise();
void AnimationController_setAnimation(uint8_t animation, uint8_t* params, uint8_t length);

#endif