#ifndef SPIN_H
#define SPIN_H

#include "cup.h"

typedef struct {
    Colour colour;
    uint16_t speed;
} SpinParams;

typedef struct {
    uint16_t count;
} SpinState;

void spin_init();
void spin_refresh();

#endif