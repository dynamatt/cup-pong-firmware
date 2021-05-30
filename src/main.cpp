#include <Arduino.h>
#include <Wire.h>
#include "cup.h"
#include "animation.h"
#include "ball.h"
#include "leds.h"
#include "utils.h"

DataPacket data;

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
            case SET_COLOUR:
              //setColour();
              break;
            case SET_COLOUR_MASK:
              //setColourMask();
              break;
        }
    }
}

void setup() 
{
    LedController_initialise();
    BallDetector_initialise();
    AnimationController_initialise();

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
