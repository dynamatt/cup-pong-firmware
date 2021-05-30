#ifndef FLASH_H
#define FLASH_H

#include "cup.h"

typedef struct {
    Colour colour;
    uint16_t ramp_up_time;
    uint16_t on_time;
    uint16_t ramp_off_time;
    uint16_t off_time;
    uint16_t repeat;
} FlashParams;

typedef struct {
    uint16_t count;
} FlashState;

void flash_init();
void flash_refresh();

#endif