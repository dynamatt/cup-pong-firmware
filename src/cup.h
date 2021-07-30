#ifndef CUP_H
#define CUP_H

#include <stdint.h>
#include <Arduino.h>

#define LED_PIN   PB1
#define RX_PIN    A3  // analog pin for receiver voltage (pin 2)
#define TX_PIN    4   // digital pin for transmitter output

#define I2C_SLAVE_ADDRESS 0x60

// ADC value for the ball to count as being detected
#define BALL_DETECTION_THRESHOLD 10

#define LED_REFRESH_INTERVAL_us 1000

#define PACKET_HEADER 0x12

#pragma pack(push, 1)
typedef struct {
  uint8_t header;
  uint8_t count;
  uint16_t adc;
  uint8_t ballDetected;
} DataPacket;
#pragma pack(pop)

typedef enum {
  SET_ANIMATION =   0x74,
} command_t;

#endif