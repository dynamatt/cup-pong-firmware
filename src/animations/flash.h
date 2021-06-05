#ifndef FLASH_H
#define FLASH_H

#include "colour.h"

#pragma pack(push, 1)
typedef struct {
    uint8_colour colour;
    uint16_t ramp_up_time;
    uint16_t on_time;
    uint16_t ramp_down_time;
    uint16_t off_time;
    uint16_t repeat;
} FlashParams;
#pragma pack(pop)

typedef struct {
    uint16_t count;
    uint16_t repeat_count;
    uint16_t turn_on;
    uint16_t ramp_down;
    uint16_t turn_off;
    uint16_t ramp_up;
    uint16_colour current_colour;
    uint16_colour current_diff;
    uint16_colour ramp_up_diff;
    uint16_colour ramp_down_diff;
    uint16_colour (*diff_func)(uint16_colour, uint16_colour);
} FlashState;

void flash_init();
void flash_refresh();

#endif