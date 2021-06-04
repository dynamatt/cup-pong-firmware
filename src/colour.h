#ifndef COLOUR_H
#define COLOUR_H

#include <stdio.h>

typedef struct {
  uint8_t red;
  uint8_t green;
  uint8_t blue;
} uint8_colour;

typedef struct {
  uint16_t red;
  uint16_t green;
  uint16_t blue;
} uint16_colour;

uint16_colour convert_to_uint16(uint8_colour from);
uint8_colour convert_to_uint8(uint16_colour from);
uint16_colour add(uint16_colour a, uint16_colour b);
uint16_colour subtract(uint16_colour a, uint16_colour b);
uint16_colour divide(uint16_colour a, int divisor);

#endif