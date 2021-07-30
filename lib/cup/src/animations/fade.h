#ifndef FADE_H
#define FADE_H

#include "colour.h"
#include "leds.h"

#pragma pack(push, 1)
typedef struct {
    uint8_colour colour;
    uint16_t duration;
} FadeParams;
#pragma pack(pop)

typedef struct {
    uint16_t count;
    int16_colour current_colour[LED_COUNT];
    int16_colour diff[LED_COUNT];
} FadeState;

void fade_init(FadeParams* params, FadeState* state);
void fade_refresh(FadeParams* params, FadeState* state);

#endif