#include <Arduino.h>
#include <Wire.h>
#include "cup.h"
#include "animation.h"
#include "ball.h"
#include "leds.h"

#define BUFFER_SIZE 100

DataPacket data;
uint8_t buffer[BUFFER_SIZE];

void requestEvent()
{
    data.count++;
    Wire.write((uint8_t*)&data, sizeof(DataPacket));
    data.ballDetected = 0;
}

void receiveEvent(int bytes_received) {
    while (Wire.available()) {
        command_t command = (command_t)Wire.read();
        switch (command) {
            case SET_ANIMATION:
              uint8_t animation = Wire.read();
              uint8_t length = Wire.read();
              for (int i=0; i<length; i++) {
                  buffer[i] = Wire.read();
              }
              AnimationController_setAnimation(animation, buffer, length);
              break;
        }
    }
}

void setup() 
{
    LedController_initialise();
    BallDetector_initialise();
    AnimationController_initialise();

    data.header = PACKET_HEADER;

    Wire.begin(I2C_SLAVE_ADDRESS);
    Wire.onReceive(receiveEvent);
    Wire.onRequest(requestEvent);
}

void loop() 
{
    if (BallDetector_isBallDetected(&data.adc)) 
    {
      data.ballDetected = 1;
    }
}
