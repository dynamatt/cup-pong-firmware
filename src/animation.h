#ifndef ANIMATION_H
#define ANIMATION_H

#include <stdint.h>

void AnimationController_initialise();
void AnimationController_setAnimation(int animation, uint8_t* params, int length);

#endif