#include "colour.h"

uint16_colour add(uint16_colour a, uint16_colour b) {
  uint16_colour c;
  c.red = a.red + b.red;
  c.green = a.green + b.green;
  c.blue = a.blue + b.blue;
  return c;
}

uint16_colour subtract(uint16_colour a, uint16_colour b) {
  uint16_colour c;
  if (a.red > b.red) {
    c.red = a.red - b.red;
  } else {
    c.red = 0;
  }

  if (a.green > b.green) {
    c.green = a.green - b.green;
  } else {
    c.green = 0;
  }

  if (a.blue > b.blue) {
    c.blue = a.blue - b.blue;
  } else {
    c.blue = 0;
  }

  return c;
}

uint16_colour divide(uint16_colour a, int divisor) {
  return {
    (uint16_t)(a.red / divisor),
    (uint16_t)(a.green / divisor),
    (uint16_t)(a.blue / divisor)
  };
}

uint8_colour convert_to_uint8(uint16_colour from) {
  return {
    (uint8_t)(from.red >> 8),
    (uint8_t)(from.green >> 8),
    (uint8_t)(from.blue >> 8),
  };
}

uint16_colour convert_to_uint16(uint8_colour from) {
  return {
    (uint16_t)(from.red << 8),
    (uint16_t)(from.green << 8),
    (uint16_t)(from.blue << 8),
  };
}