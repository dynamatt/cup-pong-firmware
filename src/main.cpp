#include <Arduino.h>
#include <Wire.h>
#include "cup.h"
#include "animation.h"
#include "ball.h"
#include "leds.h"

#define BUFFER_SIZE 100

DataPacket data;
uint8_t buffer[BUFFER_SIZE];

void processCommand(command_t command, uint8_t length)
{
    switch (command) {
        case SET_ANIMATION:
            uint8_t animation = buffer[0];
            AnimationController_setAnimation(animation, (uint8_t*)(buffer+1), length-1);
            break;
    }
}

void requestEvent()
{
    data.count++;
    Wire.write((uint8_t*)&data, sizeof(DataPacket));
    data.ballDetected = 0;
}

void receiveEvent(int bytes_received) 
{
    while (Wire.available()) {
        command_t command = (command_t)Wire.read();
        uint8_t length = Wire.read();
        for (int i=0; i<length; i++) {
            buffer[i] = Wire.read();
        }
        processCommand(command, length);
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
