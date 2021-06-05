#ifndef SPIN_H
#define SPIN_H

#include "colour.h"

#pragma pack(push, 1)
typedef struct {
    uint8_colour colour;
    uint16_t speed;
    uint16_t tail;
} SpinParams;
#pragma pack(pop)

typedef struct {
    uint16_t count;
} SpinState;

void spin_init();
void spin_refresh();

#endif