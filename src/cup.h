#ifndef CUP_H
#define CUP_H

#include <stdint.h>
#include <Arduino.h>

#define LED_PIN   PB1
#define RX_PIN    A3  // analog pin for receiver voltage (pin 2)
#define TX_PIN    4   // digital pin for transmitter output

// ADC value for the ball to count as being detected
#define BALL_DETECTION_THRESHOLD 10

#define LED_REFRESH_INTERVAL_us 10000

#pragma pack(push, 1)
typedef struct {
  uint8_t header;
  uint8_t count;
  uint16_t min_adc;
  uint16_t max_adc;
} DataPacket;
#pragma pack(pop)

typedef enum {
  SET_ANIMATION = 0x74,
  SET_BALL_DETECTION_THRESHOLD = 0x75,
} command_t;

typedef enum {
  ADDR_BALL_DETECTION_THRESHOLD = 0x00,
} eeprom_address_t;

#endif